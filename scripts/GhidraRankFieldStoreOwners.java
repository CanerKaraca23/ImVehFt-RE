// Rank syntactic field-store candidates by direct references from their owner
// functions to a supplied global. Read-only; does not infer register provenance.
// Args: <candidate.csv> <summary.csv> <global-address>
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.symbol.Reference;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public class GhidraRankFieldStoreOwners extends GhidraScript {
    @Override protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 3) throw new IllegalArgumentException("expected candidate.csv, output.csv, global address");
        Address target = toAddr(Long.decode(args[2]));
        Map<String, List<String>> candidates = new LinkedHashMap<>();
        List<String> lines = Files.readAllLines(Paths.get(args[0]), StandardCharsets.UTF_8);
        for (int i = 1; i < lines.size(); i++) {
            String[] fields = lines.get(i).split(",", 3);
            if (fields.length < 2 || fields[1].trim().isEmpty()) continue;
            String owner = fields[1].trim();
            candidates.computeIfAbsent(owner, k -> new ArrayList<>()).add(fields[0].trim());
        }
        List<String> rows = new ArrayList<>();
        rows.add("function_entry,function_name,candidate_store_count,direct_global_xref_count,global_xref_sites,candidate_store_sites");
        for (Map.Entry<String, List<String>> item : candidates.entrySet()) {
            Address entry = toAddr(Long.decode("0x" + item.getKey().replace("0x", "")));
            Function function = currentProgram.getFunctionManager().getFunctionAt(entry);
            if (function == null) {
                rows.add(entry + ",, " + item.getValue().size() + ",0,,\"" + String.join("|", item.getValue()) + "\"");
                continue;
            }
            int count = 0;
            StringBuilder refs = new StringBuilder();
            InstructionIterator iterator = currentProgram.getListing().getInstructions(function.getBody(), true);
            while (iterator.hasNext()) {
                Instruction instruction = iterator.next();
                for (Reference reference : currentProgram.getReferenceManager()
                        .getReferencesFrom(instruction.getAddress())) {
                    if (reference.getToAddress().equals(target)) {
                        if (refs.length() > 0) refs.append('|');
                        refs.append(instruction.getAddress()).append(':').append(instruction.toString());
                        count++;
                    }
                }
            }
            rows.add(entry + ",\"" + function.getName().replace("\"", "'") + "\"," + item.getValue().size()
                + "," + count + ",\"" + refs.toString().replace("\"", "'") + "\",\""
                + String.join("|", item.getValue()) + "\"");
        }
        Files.write(Paths.get(args[1]), rows, StandardCharsets.UTF_8);
        println("owners=" + candidates.size() + " output=" + Paths.get(args[1]).toAbsolutePath());
    }
}
