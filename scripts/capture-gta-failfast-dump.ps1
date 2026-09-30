param(
    [Parameter(Mandatory = $true)]
    [string] $Executable,

    [Parameter(Mandatory = $true)]
    [string] $WorkingDirectory,

    [Parameter(Mandatory = $true)]
    [string] $OutputDirectory,

    [uint32] $ExceptionCode = 3221225620,

    [ValidateRange(10, 600)]
    [int] $TimeoutSeconds = 90
)

$ErrorActionPreference = 'Stop'
$resolvedExe = (Resolve-Path -LiteralPath $Executable).Path
$resolvedWorkingDirectory = (Resolve-Path -LiteralPath $WorkingDirectory).Path
if (-not (Test-Path -LiteralPath $OutputDirectory -PathType Container)) {
    throw "Output directory must already exist: $OutputDirectory"
}
$resolvedOutputDirectory = (Resolve-Path -LiteralPath $OutputDirectory).Path

if (Get-Process -Name 'gta_sa' -ErrorAction SilentlyContinue) {
    throw 'A gta_sa.exe process is already running; refusing to launch a second test instance.'
}

$nativeSource = @'
using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using Microsoft.Win32.SafeHandles;

public static class ImVehFtDebugCapture
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct STARTUPINFO
    {
        public uint cb;
        public string lpReserved;
        public string lpDesktop;
        public string lpTitle;
        public uint dwX;
        public uint dwY;
        public uint dwXSize;
        public uint dwYSize;
        public uint dwXCountChars;
        public uint dwYCountChars;
        public uint dwFillAttribute;
        public uint dwFlags;
        public ushort wShowWindow;
        public ushort cbReserved2;
        public IntPtr lpReserved2;
        public IntPtr hStdInput;
        public IntPtr hStdOutput;
        public IntPtr hStdError;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct PROCESS_INFORMATION
    {
        public IntPtr hProcess;
        public IntPtr hThread;
        public uint dwProcessId;
        public uint dwThreadId;
    }

    [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool CreateProcessW(
        string lpApplicationName,
        StringBuilder lpCommandLine,
        IntPtr lpProcessAttributes,
        IntPtr lpThreadAttributes,
        [MarshalAs(UnmanagedType.Bool)] bool bInheritHandles,
        uint dwCreationFlags,
        IntPtr lpEnvironment,
        string lpCurrentDirectory,
        ref STARTUPINFO lpStartupInfo,
        out PROCESS_INFORMATION lpProcessInformation);

    [DllImport("kernel32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool WaitForDebugEvent(IntPtr lpDebugEvent, uint dwMilliseconds);

    [DllImport("kernel32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool ContinueDebugEvent(uint dwProcessId, uint dwThreadId, uint dwContinueStatus);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr OpenProcess(uint dwDesiredAccess, bool bInheritHandle, uint dwProcessId);

    [DllImport("kernel32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool CloseHandle(IntPtr hObject);

    [DllImport("kernel32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool TerminateProcess(IntPtr hProcess, uint uExitCode);

    [DllImport("dbghelp.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool MiniDumpWriteDump(
        IntPtr hProcess,
        uint ProcessId,
        IntPtr hFile,
        uint DumpType,
        IntPtr ExceptionParam,
        IntPtr UserStreamParam,
        IntPtr CallbackParam);

    const uint DEBUG_ONLY_THIS_PROCESS = 0x00000002;
    const uint DBG_CONTINUE = 0x00010002;
    const uint DBG_EXCEPTION_NOT_HANDLED = 0x80010001;
    const uint EXCEPTION_DEBUG_EVENT = 1;
    const uint EXIT_PROCESS_DEBUG_EVENT = 5;
    const uint EXCEPTION_BREAKPOINT = 0x80000003;
    const uint PROCESS_QUERY_INFORMATION = 0x0400;
    const uint PROCESS_VM_READ = 0x0010;
    const uint PROCESS_DUP_HANDLE = 0x0040;

    // MiniDumpWithDataSegs | MiniDumpWithHandleData | MiniDumpWithUnloadedModules |
    // MiniDumpWithIndirectlyReferencedMemory | MiniDumpWithPrivateReadWriteMemory |
    // MiniDumpWithFullMemoryInfo | MiniDumpWithThreadInfo.
    const uint DIAGNOSTIC_DUMP_TYPE = 0x00001A65;

    public static int Run(string executable, string workingDirectory,
                          string outputDirectory, uint targetExceptionCode,
                          int timeoutSeconds)
    {
        STARTUPINFO startup = new STARTUPINFO();
        startup.cb = (uint)Marshal.SizeOf(typeof(STARTUPINFO));
        startup.dwFlags = 1; // STARTF_USESHOWWINDOW
        startup.wShowWindow = 1; // SW_SHOWNORMAL: expose the isolated test window
        PROCESS_INFORMATION process;
        StringBuilder commandLine = new StringBuilder("\"" + executable + "\"");

        if (!CreateProcessW(executable, commandLine, IntPtr.Zero, IntPtr.Zero,
                            false, DEBUG_ONLY_THIS_PROCESS, IntPtr.Zero,
                            workingDirectory, ref startup, out process))
        {
            throw new System.ComponentModel.Win32Exception(Marshal.GetLastWin32Error());
        }

        Console.WriteLine("DEBUG_PROCESS_STARTED pid={0} tid={1} exe={2}",
                          process.dwProcessId, process.dwThreadId, executable);

        IntPtr debugEvent = Marshal.AllocHGlobal(176);
        Stopwatch watch = Stopwatch.StartNew();
        bool exited = false;
        bool dumpedFirstChance = false;
        int exceptionCount = 0;
        try
        {
            while (!exited)
            {
                if (watch.Elapsed.TotalSeconds >= timeoutSeconds)
                {
                    Console.WriteLine("TIMEOUT seconds={0}; terminating isolated test process",
                                      timeoutSeconds);
                    TerminateProcess(process.hProcess, 0xE001);
                }

                if (!WaitForDebugEvent(debugEvent, 1000))
                {
                    int error = Marshal.GetLastWin32Error();
                    if (error == 121) // WAIT_TIMEOUT
                        continue;
                    throw new System.ComponentModel.Win32Exception(error);
                }

                uint eventCode = (uint)Marshal.ReadInt32(debugEvent, 0);
                uint eventPid = (uint)Marshal.ReadInt32(debugEvent, 4);
                uint eventTid = (uint)Marshal.ReadInt32(debugEvent, 8);
                uint continueStatus = DBG_CONTINUE;

                if (eventCode == EXCEPTION_DEBUG_EVENT)
                {
                    uint code = (uint)Marshal.ReadInt32(debugEvent, 16);
                    ulong address = (ulong)Marshal.ReadInt64(debugEvent, 32);
                    uint address32 = (uint)Marshal.ReadInt32(debugEvent, 28);
                    uint firstChance = (uint)Marshal.ReadInt32(debugEvent, 168);
                    byte[] rawEvent = new byte[176];
                    Marshal.Copy(debugEvent, rawEvent, 0, rawEvent.Length);
                    exceptionCount++;
                    Console.WriteLine("DEBUG_EXCEPTION code=0x{0:X8} flags=0x{1:X8} address64=0x{2:X} address32=0x{3:X8} firstChance64={4} firstChance32at96=0x{5:X8} tid={6}",
                                      code, (uint)Marshal.ReadInt32(debugEvent, 20), address,
                                      address32, firstChance, (uint)Marshal.ReadInt32(debugEvent, 96),
                                      eventTid);
                    Console.WriteLine("DEBUG_EVENT_BYTES={0}", BitConverter.ToString(rawEvent));

                    if (code == targetExceptionCode && (!dumpedFirstChance || firstChance == 0))
                    {
                        string chance = firstChance != 0 ? "first" : "second";
                        string dumpPath = Path.Combine(outputDirectory,
                            "gta_sa-0x" + code.ToString("X8") + "-" + chance + "chance.dmp");
                        IntPtr dumpProcess = OpenProcess(
                            PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_DUP_HANDLE,
                            false, eventPid);
                        if (dumpProcess == IntPtr.Zero)
                        {
                            Console.WriteLine("DUMP_OPEN_PROCESS_FAILED win32={0}",
                                              Marshal.GetLastWin32Error());
                        }
                        else
                        {
                            try
                            {
                                using (FileStream file = new FileStream(
                                    dumpPath, FileMode.CreateNew, FileAccess.ReadWrite, FileShare.None))
                                {
                                    bool ok = MiniDumpWriteDump(
                                        dumpProcess, eventPid, file.SafeFileHandle.DangerousGetHandle(),
                                        DIAGNOSTIC_DUMP_TYPE, IntPtr.Zero, IntPtr.Zero, IntPtr.Zero);
                                    file.Flush();
                                    Console.WriteLine("DUMP_{0} path={1} win32={2}",
                                        ok ? "WRITTEN" : "FAILED", dumpPath,
                                        ok ? 0 : Marshal.GetLastWin32Error());
                                    if (!ok)
                                        File.Delete(dumpPath);
                                }
                            }
                            finally
                            {
                                CloseHandle(dumpProcess);
                            }
                        }
                        if (firstChance != 0)
                            dumpedFirstChance = true;
                    }

                    // Let ordinary first-chance exceptions reach the target's
                    // handlers. Breakpoints are debugger events and are consumed.
                    continueStatus = code == EXCEPTION_BREAKPOINT
                        ? DBG_CONTINUE
                        : DBG_EXCEPTION_NOT_HANDLED;
                }
                else if (eventCode == EXIT_PROCESS_DEBUG_EVENT)
                {
                    uint exitCode = (uint)Marshal.ReadInt32(debugEvent, 16);
                    Console.WriteLine("DEBUG_PROCESS_EXIT code=0x{0:X8} exceptions={1}",
                                      exitCode, exceptionCount);
                    exited = true;
                }

                if (!ContinueDebugEvent(eventPid, eventTid, continueStatus))
                    throw new System.ComponentModel.Win32Exception(Marshal.GetLastWin32Error());
            }
        }
        finally
        {
            Marshal.FreeHGlobal(debugEvent);
            CloseHandle(process.hThread);
            CloseHandle(process.hProcess);
        }
        return 0;
    }
}
'@

Add-Type -TypeDefinition $nativeSource -Language CSharp
[ImVehFtDebugCapture]::Run(
    $resolvedExe,
    $resolvedWorkingDirectory,
    $resolvedOutputDirectory,
    $ExceptionCode,
    $TimeoutSeconds
)
