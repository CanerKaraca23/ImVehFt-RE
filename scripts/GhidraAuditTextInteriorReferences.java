// Read-only inventory of references to every byte in a supplied .text VA range.
// Args: <start-va-hex> <end-va-exclusive-hex> <output.csv>
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class GhidraAuditTextInteriorReferences extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 3) {
            throw new IllegalArgumentException("expected start-va end-va-exclusive output.csv");
        }
        Address start = toAddr(Long.parseLong(args[0].replace("0x", ""), 16));
        Address end = toAddr(Long.parseLong(args[1].replace("0x", ""), 16));
        Path output = Paths.get(args[2]);
        if (Files.exists(output)) {
            throw new IllegalArgumentException("refusing to overwrite " + output);
        }

        List<String> rows = new ArrayList<>();
        rows.add("target_va,source_va,source_function_va,source_function,target_function_va,target_function,reference_type");
        long queried = 0;
        long targetsWithReferences = 0;
        long references = 0;
        long functionInteriorReferences = 0;
        long unownedTextReferences = 0;
        Set<String> functionInteriorTargets = new HashSet<>();
        Set<String> unownedTextTargets = new HashSet<>();
        for (Address target = start; target.compareTo(end) < 0; target = target.add(1)) {
            queried++;
            Function targetFunction = currentProgram.getFunctionManager().getFunctionContaining(target);
            ReferenceIterator iterator = currentProgram.getReferenceManager().getReferencesTo(target);
            boolean hadReferences = false;
            while (iterator.hasNext()) {
                Reference reference = iterator.next();
                hadReferences = true;
                references++;
                Function sourceFunction = currentProgram.getFunctionManager()
                    .getFunctionContaining(reference.getFromAddress());
                if ((targetFunction != null && target.equals(targetFunction.getEntryPoint())) ||
                    (sourceFunction != null && sourceFunction.getEntryPoint()
                        .equals(targetFunction == null ? null : targetFunction.getEntryPoint()))) {
                    continue;
                }
                if (targetFunction == null) {
                    unownedTextReferences++;
                    unownedTextTargets.add(target.toString());
                }
                else {
                    functionInteriorReferences++;
                    functionInteriorTargets.add(target.toString());
                }
                rows.add(target + "," + reference.getFromAddress() + "," +
                    (sourceFunction == null ? "" : sourceFunction.getEntryPoint()) + "," +
                    csv(sourceFunction == null ? "<no-containing-function>" : sourceFunction.getName()) + "," +
                    (targetFunction == null ? "" : targetFunction.getEntryPoint()) + "," +
                    csv(targetFunction == null ? "<no-containing-function>" : targetFunction.getName()) + "," +
                    reference.getReferenceType());
            }
            if (hadReferences) targetsWithReferences++;
            if ((queried % 8192) == 0) {
                monitor.setMessage("Queried " + queried + " / " + end.subtract(start) + " .text bytes");
            }
        }
        Files.write(output, rows, StandardCharsets.UTF_8);
        println("queried_bytes=" + queried + " targets_with_references=" + targetsWithReferences +
            " all_incoming_references=" + references +
            " references_to_function_interiors=" + functionInteriorReferences +
            " unique_function_interior_targets=" + functionInteriorTargets.size() +
            " references_to_unowned_text=" + unownedTextReferences +
            " unique_unowned_text_targets=" + unownedTextTargets.size());
        println("output=" + output.toAbsolutePath());
    }

    private static String csv(String text) {
        return "\"" + text.replace("\"", "\"\"") + "\"";
    }
}
