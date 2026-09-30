// Inventory Ghidra xrefs landing in the first five bytes of each mapped entry.
// Args: <function-name-map.csv> <output.csv>
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
import java.util.List;

public class GhidraEntryThunkSlotReferences extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) {
            throw new IllegalArgumentException("expected function-name-map.csv and output.csv");
        }
        Path mapPath = Paths.get(args[0]);
        Path outputPath = Paths.get(args[1]);
        if (Files.exists(outputPath)) {
            throw new IllegalArgumentException("refusing to overwrite " + outputPath);
        }

        List<String> lines = Files.readAllLines(mapPath, StandardCharsets.UTF_8);
        List<String> rows = new ArrayList<>();
        rows.add("entry_va,entry_offset,target_va,source_va,source_function,source_function_name,reference_type");
        int entries = 0;
        int queriedTargets = 0;
        int targetsWithReferences = 0;
        int references = 0;
        for (int lineNumber = 1; lineNumber < lines.size(); lineNumber++) {
            String line = lines.get(lineNumber).trim();
            if (line.isEmpty()) continue;
            int comma = line.indexOf(',');
            String addressText = comma < 0 ? line : line.substring(0, comma);
            addressText = addressText.replace("\"", "").replace("0x", "").replace("0X", "");
            Address entry = toAddr(Long.parseLong(addressText, 16));
            entries++;
            for (int displacement = 0; displacement < 5; displacement++) {
                Address target = entry.add(displacement);
                queriedTargets++;
                ReferenceIterator iterator = currentProgram.getReferenceManager().getReferencesTo(target);
                boolean hadReferences = false;
                while (iterator.hasNext()) {
                    Reference reference = iterator.next();
                    hadReferences = true;
                    references++;
                    Function function = currentProgram.getFunctionManager()
                        .getFunctionContaining(reference.getFromAddress());
                    String name = function == null ? "" : csv(function.getName());
                    String functionAddress = function == null ? "" : function.getEntryPoint().toString();
                    rows.add(entry + "," + displacement + "," + target + "," +
                        reference.getFromAddress() + "," + functionAddress + "," + name + "," +
                        reference.getReferenceType());
                }
                if (hadReferences) targetsWithReferences++;
            }
        }
        if (entries != 705 || queriedTargets != 3525) {
            throw new IllegalStateException("expected 705 entries/3525 byte targets; got " +
                entries + "/" + queriedTargets);
        }
        Files.write(outputPath, rows, StandardCharsets.UTF_8);
        println("entries=" + entries + " queried_targets=" + queriedTargets +
            " targets_with_refs=" + targetsWithReferences + " references=" + references);
        println("output=" + outputPath.toAbsolutePath());
    }

    private static String csv(String text) {
        return "\"" + text.replace("\"", "\"\"") + "\"";
    }
}
