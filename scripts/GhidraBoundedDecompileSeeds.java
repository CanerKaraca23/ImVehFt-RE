// Decompile selected game-executable functions using temporary CFG-bounded bodies.
// Run with -noanalysis. Args: <summary.csv> <decomp.c> <cap> <entry> [<entry>...].
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.SourceType;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class GhidraBoundedDecompileSeeds extends GhidraScript {
    @Override protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 4) throw new IllegalArgumentException("expected summary, decomp, cap, and entry addresses");
        int cap = Integer.parseInt(args[2]);
        List<String> rows = new ArrayList<>();
        rows.add("entry,cfg_instruction_count,body_min,body_max,body_byte_count,decompile_completed,status");
        StringBuilder output = new StringBuilder("/* Temporary bounded Ghidra decompilation; not original source. */\n");
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        int complete = 0;
        for (int i = 3; i < args.length; i++) {
            long value = Long.decode(args[i].trim());
            Address seed = toAddr(value);
            MemoryBlock block = currentProgram.getMemory().getBlock(seed);
            if (block == null || !block.isExecute()) {
                rows.add(String.format("0x%08X,0,,,,no,not_executable", value));
                continue;
            }
            new DisassembleCommand(seed, null, false).applyTo(currentProgram, monitor);
            Instruction entryInstruction = currentProgram.getListing().getInstructionAt(seed);
            if (entryInstruction == null || !entryInstruction.getMinAddress().equals(seed)) {
                rows.add(String.format("0x%08X,0,,,,no,seed_is_not_an_instruction_start", value));
                continue;
            }
            ArrayDeque<Address> queue = new ArrayDeque<>();
            Set<Address> visited = new HashSet<>();
            AddressSet body = new AddressSet();
            queue.add(seed);
            while (!queue.isEmpty() && visited.size() < cap) {
                Address at = queue.removeFirst();
                if (!visited.add(at)) continue;
                Instruction ins = currentProgram.getListing().getInstructionAt(at);
                if (ins == null) {
                    new DisassembleCommand(at, null, false).applyTo(currentProgram, monitor);
                    ins = currentProgram.getListing().getInstructionAt(at);
                }
                if (ins == null) continue;
                body.add(ins.getMinAddress(), ins.getMaxAddress());
                if (ins.getFlowType().isJump()) {
                    for (Address dest : ins.getFlows()) if (dest != null && block.contains(dest)) queue.addLast(dest);
                    if (ins.getFlowType().isConditional() && ins.getFallThrough() != null && block.contains(ins.getFallThrough())) queue.addLast(ins.getFallThrough());
                } else if (!ins.getFlowType().isTerminal() && ins.getFallThrough() != null && block.contains(ins.getFallThrough())) {
                    // Record calls and follow only their return-site fallthrough; never chase callees here.
                    queue.addLast(ins.getFallThrough());
                }
            }
            if (!body.contains(seed)) {
                rows.add(String.format("0x%08X,%d,,,,no,bounded_cfg_did_not_retain_entrypoint", value, visited.size()));
                continue;
            }
            Function function = currentProgram.getFunctionManager().getFunctionAt(seed);
            if (function == null) function = currentProgram.getFunctionManager().createFunction(
                "BOUNDED_" + String.format("%08X", value), seed, body, SourceType.ANALYSIS);
            if (function == null) {
                rows.add(String.format("0x%08X,%d,,,,no,function_creation_failed_or_overlap", value, visited.size()));
                continue;
            }
            DecompileResults result = decompiler.decompileFunction(function, 45, monitor);
            boolean ok = result != null && result.decompileCompleted() && result.getDecompiledFunction() != null;
            String status = ok ? "bounded_cfg_decompilation" : result == null ? "no_result" : result.getErrorMessage();
            if (ok) {
                complete++;
                output.append("\n/* entry 0x").append(String.format("%08X", value))
                    .append("; bounded CFG instructions=").append(visited.size())
                    .append("; body bytes=").append(function.getBody().getNumAddresses()).append(" */\n")
                    .append(result.getDecompiledFunction().getC()).append("\n");
            }
            rows.add(String.format("0x%08X,%d,%s,%s,%d,%s,\"%s\"", value, visited.size(),
                function.getBody().getMinAddress(), function.getBody().getMaxAddress(),
                function.getBody().getNumAddresses(), ok ? "yes" : "no", status.replace("\"", "\"\"")));
        }
        Files.write(Paths.get(args[0]), rows, StandardCharsets.UTF_8);
        Files.writeString(Paths.get(args[1]), output.toString(), StandardCharsets.UTF_8);
        println("seeds=" + (args.length - 3) + " bounded_functions_decompiled=" + complete);
        println("summary=" + Paths.get(args[0]).toAbsolutePath());
        println("decomp=" + Paths.get(args[1]).toAbsolutePath());
        println("NOTE: synthetic bounded function bodies only; not source recovery or runtime proof.");
        decompiler.dispose();
    }
}
