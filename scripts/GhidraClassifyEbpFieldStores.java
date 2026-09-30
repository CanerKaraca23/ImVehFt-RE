// Check whether EBP-relative +0x5c store candidates occur in standard EBP
// stack-frame functions. This is evidence classification, not pointer analysis.
// Args: <candidate.csv> <output.csv>
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public class GhidraClassifyEbpFieldStores extends GhidraScript {
    @Override protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) throw new IllegalArgumentException("expected candidate.csv output.csv");
        Map<String, List<String>> candidates = new LinkedHashMap<>();
        List<String> lines = Files.readAllLines(Paths.get(args[0]), StandardCharsets.UTF_8);
        for (int i = 1; i < lines.size(); i++) {
            String[] f = lines.get(i).split(",", 6);
            if (f.length < 6 || !f[4].toUpperCase().contains("EBP") || f[1].trim().isEmpty()) continue;
            candidates.computeIfAbsent(f[1].trim(), k -> new ArrayList<>()).add(f[0].trim());
        }
        List<String> rows = new ArrayList<>();
        rows.add("function_entry,function_name,candidate_count,standard_ebp_frame,entry_instructions,candidate_sites");
        int frames = 0;
        for (Map.Entry<String, List<String>> item : candidates.entrySet()) {
            Address entry = toAddr(Long.decode("0x" + item.getKey().replace("0x", "")));
            Function function = currentProgram.getFunctionManager().getFunctionAt(entry);
            if (function == null) continue;
            List<String> first = new ArrayList<>();
            InstructionIterator it = currentProgram.getListing().getInstructions(function.getBody(), true);
            while (it.hasNext() && first.size() < 8) first.add(it.next().toString());
            boolean stackEbp = false;
            for (String ins : first) {
                String upper = ins.toUpperCase();
                if (upper.startsWith("MOV EBP,ESP")
                        || upper.startsWith("LEA EBP,[ESP + -")) {
                    stackEbp = true;
                    break;
                }
            }
            if (stackEbp) frames++;
            rows.add(entry + ",\"" + function.getName().replace("\"", "'") + "\"," + item.getValue().size()
                + "," + stackEbp + ",\"" + String.join(" | ", first).replace("\"", "'")
                + "\",\"" + String.join("|", item.getValue()) + "\"");
        }
        Files.write(Paths.get(args[1]), rows, StandardCharsets.UTF_8);
        println("EBP_candidate_owners=" + candidates.size() + " standard_EBP_frame_owners=" + frames
            + " output=" + Paths.get(args[1]).toAbsolutePath());
    }
}
