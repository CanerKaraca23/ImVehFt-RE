// Targeted CFG/direct-call survey. Run on gta_sa.exe with -noanalysis.
// Args: <output.csv> <comma-separated-entry-addresses> <instruction-cap>.
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.mem.MemoryBlock;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

public class GhidraBoundedDirectCallAudit extends GhidraScript {
    private static class Task {
        Address root;
        Address entry;
        int depth;
        Task(Address root, Address entry, int depth) { this.root = root; this.entry = entry; this.depth = depth; }
    }

    @Override protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 3) throw new IllegalArgumentException("expected output.csv, one or more entries, and cap");
        int cap = Integer.parseInt(args[args.length - 1]);
        List<String> rows = new ArrayList<>();
        rows.add("root,entry,depth,instruction_address,instruction,call_kind,call_target,context");
        Set<String> scheduled = new HashSet<>();
        ArrayDeque<Task> tasks = new ArrayDeque<>();
        for (int i = 1; i < args.length - 1; i++) {
            Address entry = toAddr(Long.decode(args[i].trim()));
            tasks.add(new Task(entry, entry, 0));
            scheduled.add(entry.toString() + "|" + entry.toString());
        }
        int functions = 0, visitedCount = 0, indirectCalls = 0, directEdges = 0;
        while (!tasks.isEmpty()) {
            Task task = tasks.removeFirst();
            MemoryBlock block = currentProgram.getMemory().getBlock(task.entry);
            if (block == null || !block.isExecute()) {
                        rows.add(String.format("%s,%s,%d,,,,NON_EXECUTABLE", task.root, task.entry, task.depth));
                continue;
            }
            new DisassembleCommand(task.entry, null, false).applyTo(currentProgram, monitor);
            ArrayDeque<Address> queue = new ArrayDeque<>();
            Set<Address> visited = new LinkedHashSet<>();
            queue.add(task.entry);
            while (!queue.isEmpty() && visited.size() < cap) {
                Address at = queue.removeFirst();
                if (!visited.add(at)) continue;
                Instruction ins = currentProgram.getListing().getInstructionAt(at);
                if (ins == null) continue;
                if (ins.getFlowType().isCall()) {
                    Address[] flows = ins.getFlows();
                    if (flows.length == 0) {
                        indirectCalls++;
                        rows.add(String.format("%s,%s,%d,%s,\"%s\",INDIRECT,,\"%s\"", task.root, task.entry,
                            task.depth, at, ins.toString().replace("\"", "\"\""), contextAround(ins)));
                    } else {
                        for (Address target : flows) {
                            directEdges++;
                            rows.add(String.format("%s,%s,%d,%s,\"%s\",DIRECT,%s,", task.root, task.entry,
                                task.depth, at, ins.toString().replace("\"", "\"\""), target));
                            MemoryBlock targetBlock = currentProgram.getMemory().getBlock(target);
                            String key = task.root + "|" + target;
                            // Follow at most two direct-call layers from each root; never follow indirect calls.
                            if (targetBlock != null && targetBlock.isExecute() && !scheduled.contains(key)) {
                                scheduled.add(key);
                                if (task.depth < 2) tasks.addLast(new Task(task.root, target, task.depth + 1));
                            }
                        }
                    }
                    if (ins.getFallThrough() != null && block.contains(ins.getFallThrough())) queue.addLast(ins.getFallThrough());
                } else if (ins.getFlowType().isJump()) {
                    for (Address target : ins.getFlows()) if (target != null && block.contains(target)) queue.addLast(target);
                    if (ins.getFlowType().isConditional() && ins.getFallThrough() != null && block.contains(ins.getFallThrough())) queue.addLast(ins.getFallThrough());
                } else if (!ins.getFlowType().isTerminal() && ins.getFallThrough() != null && block.contains(ins.getFallThrough())) {
                    queue.addLast(ins.getFallThrough());
                }
            }
            if (!queue.isEmpty()) rows.add(String.format("%s,%s,%d,,,,,CAP_REACHED_%d", task.root, task.entry, task.depth, cap));
            functions++;
            visitedCount += visited.size();
        }
        Files.write(Paths.get(args[0]), rows, StandardCharsets.UTF_8);
        println("bounded_entries=" + functions + " instructions=" + visitedCount + " direct_call_edges=" + directEdges + " indirect_call_sites=" + indirectCalls);
        println("csv=" + Paths.get(args[0]).toAbsolutePath());
        println("NOTE: direct-call depth capped at two; indirect targets and dynamic behavior remain unresolved.");
    }

    private String contextAround(Instruction ins) {
        List<String> before = new ArrayList<>();
        Instruction cursor = ins;
        for (int i = 0; i < 4; i++) {
            cursor = currentProgram.getListing().getInstructionBefore(cursor.getAddress());
            if (cursor == null) break;
            before.add(0, cursor.getAddress() + " " + cursor.toString());
        }
        List<String> after = new ArrayList<>();
        cursor = ins;
        for (int i = 0; i < 4; i++) {
            cursor = currentProgram.getListing().getInstructionAfter(cursor.getAddress());
            if (cursor == null) break;
            after.add(cursor.getAddress() + " " + cursor.toString());
        }
        List<String> all = new ArrayList<>(before);
        all.add(ins.getAddress() + " " + ins.toString());
        all.addAll(after);
        return String.join(" | ", all).replace("\"", "\"\"");
    }
}
