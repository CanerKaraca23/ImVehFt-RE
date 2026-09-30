// Bounded CFG recovery for patch destinations absent from the 705 TU map.
// Run on ImVehFt.asi with -noanalysis. Args: <flow.csv> <max-instructions>.
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.mem.MemoryBlock;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class GhidraHookTargetFlow extends GhidraScript {
    private static final long[] SEEDS = {
        0x10004B10L, 0x10008780L, 0x10008830L, 0x10008940L,
        0x10007F90L, 0x10007F50L, 0x10007F70L, 0x10003E40L,
        0x10003030L, 0x10003060L, 0x10003080L, 0x100031E0L
    };

    @Override protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) throw new IllegalArgumentException("expected output.csv and max-instructions");
        int limit = Integer.parseInt(args[1]);
        List<String> rows = new ArrayList<>();
        rows.add("target,instruction_address,mnemonic,bytes_hex,flow_type,successors,classification");
        int decoded = 0, unresolved = 0, capped = 0;
        for (long seedValue : SEEDS) {
            Address seed = toAddr(seedValue);
            MemoryBlock seedBlock = currentProgram.getMemory().getBlock(seed);
            if (seedBlock == null || !seedBlock.isExecute()) {
                rows.add(String.format("0x%08X,,,,,,NON_EXECUTABLE_OR_UNMAPPED", seedValue));
                unresolved++;
                continue;
            }
            new DisassembleCommand(seed, null, false).applyTo(currentProgram, monitor);
            ArrayDeque<Address> queue = new ArrayDeque<>();
            Set<Address> visited = new HashSet<>();
            queue.add(seed);
            while (!queue.isEmpty() && visited.size() < limit) {
                Address at = queue.removeFirst();
                if (!visited.add(at)) continue;
                Instruction ins = currentProgram.getListing().getInstructionAt(at);
                if (ins == null) {
                    new DisassembleCommand(at, null, false).applyTo(currentProgram, monitor);
                    ins = currentProgram.getListing().getInstructionAt(at);
                }
                if (ins == null) {
                    rows.add(String.format("0x%08X,0x%08X,,,,,UNDECODED", seedValue, at.getOffset()));
                    unresolved++;
                    continue;
                }
                decoded++;
                StringBuilder hex = new StringBuilder();
                byte[] raw = new byte[ins.getLength()];
                currentProgram.getMemory().getBytes(at, raw);
                for (byte b : raw) { if (hex.length() > 0) hex.append(' '); hex.append(String.format("%02X", b & 255)); }
                List<Address> next = new ArrayList<>();
                if (ins.getFlowType().isJump()) {
                    for (Address flow : ins.getFlows()) if (flow != null && seedBlock.contains(flow)) next.add(flow);
                    if (ins.getFlowType().isConditional() && ins.getFallThrough() != null && seedBlock.contains(ins.getFallThrough())) next.add(ins.getFallThrough());
                } else if (!ins.getFlowType().isTerminal() && ins.getFallThrough() != null && seedBlock.contains(ins.getFallThrough())) {
                    // Calls are deliberately followed only through their fallthrough; callees are not attributed to this stub.
                    next.add(ins.getFallThrough());
                }
                StringBuilder succ = new StringBuilder();
                for (Address n : next) {
                    if (succ.length() > 0) succ.append('|');
                    succ.append(String.format("0x%08X", n.getOffset()));
                    if (!visited.contains(n)) queue.addLast(n);
                }
                String classification = ins.getFlowType().isTerminal() ? "TERMINAL_OR_INDIRECT_EXIT" : next.isEmpty() ? "NO_INTRA_BLOCK_SUCCESSOR" : "FOLLOWED";
                rows.add(String.format("0x%08X,0x%08X,\"%s\",\"%s\",\"%s\",\"%s\",%s",
                    seedValue, at.getOffset(), ins.toString().replace("\"", "\"\""), hex,
                    ins.getFlowType().toString(), succ, classification));
            }
            if (!queue.isEmpty()) capped++;
        }
        Files.write(Paths.get(args[0]), rows, StandardCharsets.UTF_8);
        println("targets=" + SEEDS.length + " decoded_instructions=" + decoded + " unresolved=" + unresolved + " capped_targets=" + capped);
        println("csv=" + Paths.get(args[0]).toAbsolutePath());
        println("NOTE: bounded CFG listing only; indirect destinations and runtime behavior remain unresolved.");
    }
}
