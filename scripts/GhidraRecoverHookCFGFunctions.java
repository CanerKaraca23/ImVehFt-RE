// Build temporary Ghidra functions from bounded direct CFGs, then decompile.
// ImVehFt.asi only; run with -noanalysis. Args: <summary.csv> <decomp.c> <limit>.
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

public class GhidraRecoverHookCFGFunctions extends GhidraScript {
    private static final long[] SEEDS = {
        0x10004B10L, 0x10008780L, 0x10008830L, 0x10008940L,
        0x10007F90L, 0x10007F50L, 0x10007F70L, 0x10003E40L,
        0x10003030L, 0x10003060L, 0x10003080L, 0x100031E0L
    };

    @Override protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 3) throw new IllegalArgumentException("expected summary.csv, decomp.c, limit");
        int limit = Integer.parseInt(args[2]);
        List<String> rows = new ArrayList<>();
        rows.add("target,cfg_instruction_count,body_min,body_max,body_byte_count,decompile_completed,status");
        StringBuilder c = new StringBuilder("/* Temporary Ghidra CFG-bounded decompilation; not original source. */\n");
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        int completed = 0;
        for (long seedValue : SEEDS) {
            Address seed = toAddr(seedValue);
            MemoryBlock block = currentProgram.getMemory().getBlock(seed);
            if (block == null || !block.isExecute()) {
                rows.add(String.format("0x%08X,0,,,,,not_executable", seedValue));
                continue;
            }
            new DisassembleCommand(seed, null, false).applyTo(currentProgram, monitor);
            ArrayDeque<Address> queue = new ArrayDeque<>();
            Set<Address> visited = new HashSet<>();
            AddressSet body = new AddressSet();
            queue.add(seed);
            while (!queue.isEmpty() && visited.size() < limit) {
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
                    for (Address flow : ins.getFlows()) if (flow != null && block.contains(flow)) queue.addLast(flow);
                    if (ins.getFlowType().isConditional() && ins.getFallThrough() != null && block.contains(ins.getFallThrough())) queue.addLast(ins.getFallThrough());
                } else if (!ins.getFlowType().isTerminal() && ins.getFallThrough() != null && block.contains(ins.getFallThrough())) {
                    queue.addLast(ins.getFallThrough());
                }
            }
            Function function = currentProgram.getFunctionManager().getFunctionAt(seed);
            String status = "";
            if (function == null) {
                function = currentProgram.getFunctionManager().createFunction(
                    "HOOK_CFG_" + String.format("%08X", seedValue), seed, body, SourceType.ANALYSIS);
            }
            if (function == null) {
                status = "function_creation_failed_or_overlap";
                rows.add(String.format("0x%08X,%d,,,,no,%s", seedValue, visited.size(), status));
                continue;
            }
            DecompileResults result = decompiler.decompileFunction(function, 45, monitor);
            boolean ok = result != null && result.decompileCompleted() && result.getDecompiledFunction() != null;
            if (ok) {
                completed++;
                c.append("\n/* target 0x").append(String.format("%08X", seedValue))
                    .append("; bounded CFG instructions=").append(visited.size())
                    .append("; body bytes ").append(function.getBody().getNumAddresses()).append(" */\n")
                    .append(result.getDecompiledFunction().getC()).append("\n");
                status = "decompiled_bounded_body";
            } else {
                status = result == null ? "no_result" : result.getErrorMessage();
            }
            rows.add(String.format("0x%08X,%d,%s,%s,%d,%s,\"%s\"", seedValue, visited.size(),
                function.getBody().getMinAddress(), function.getBody().getMaxAddress(),
                function.getBody().getNumAddresses(), ok ? "yes" : "no", status.replace("\"", "\"\"")));
        }
        Files.write(Paths.get(args[0]), rows, StandardCharsets.UTF_8);
        Files.writeString(Paths.get(args[1]), c.toString(), StandardCharsets.UTF_8);
        println("bounded_cfg_functions=" + SEEDS.length + " decompiled=" + completed);
        println("summary=" + Paths.get(args[0]).toAbsolutePath());
        println("pseudocode=" + Paths.get(args[1]).toAbsolutePath());
        println("NOTE: synthesized bounded function bodies for analysis only; not source recovery or runtime validation.");
        decompiler.dispose();
    }
}
