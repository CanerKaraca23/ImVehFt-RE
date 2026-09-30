// Read-only inspect Ghidra code units at recorded .text reference source/target addresses.
// Args: <reference.csv> <output.csv>; first two columns must be target_va,source_va.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.CodeUnit;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Listing;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class GhidraInspectReferenceCodeUnits extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) {
            throw new IllegalArgumentException("expected reference.csv and output.csv");
        }
        Path input = Paths.get(args[0]);
        Path output = Paths.get(args[1]);
        if (Files.exists(output)) {
            throw new IllegalArgumentException("refusing to overwrite " + output);
        }
        List<String> inputRows = Files.readAllLines(input, StandardCharsets.UTF_8);
        List<String> outputRows = new ArrayList<>();
        outputRows.add("target_va,target_unit_start,target_unit_length,target_unit_type,target_unit,target_function_va,target_function,source_va,source_unit_start,source_unit_length,source_unit_type,source_unit,source_function_va,source_function");
        Listing listing = currentProgram.getListing();
        long inspected = 0;
        for (int i = 1; i < inputRows.size(); i++) {
            String line = inputRows.get(i).trim();
            if (line.isEmpty()) continue;
            int first = line.indexOf(',');
            int second = line.indexOf(',', first + 1);
            if (first < 0 || second < 0) throw new IllegalArgumentException("bad input row " + (i + 1));
            Address target = toAddr(Long.parseLong(line.substring(0, first).replace("0x", ""), 16));
            Address source = toAddr(Long.parseLong(line.substring(first + 1, second).replace("0x", ""), 16));
            CodeUnit targetUnit = listing.getCodeUnitContaining(target);
            CodeUnit sourceUnit = listing.getCodeUnitContaining(source);
            Function targetFunction = currentProgram.getFunctionManager().getFunctionContaining(target);
            Function sourceFunction = currentProgram.getFunctionManager().getFunctionContaining(source);
            outputRows.add(target + "," + unitStart(targetUnit) + "," + unitLength(targetUnit) + "," +
                unitType(targetUnit) + "," + csv(unitText(targetUnit)) + "," +
                functionAddress(targetFunction) + "," + csv(functionName(targetFunction)) + "," +
                source + "," + unitStart(sourceUnit) + "," + unitLength(sourceUnit) + "," +
                unitType(sourceUnit) + "," + csv(unitText(sourceUnit)) + "," +
                functionAddress(sourceFunction) + "," + csv(functionName(sourceFunction)));
            inspected++;
        }
        Files.write(output, outputRows, StandardCharsets.UTF_8);
        println("inspected_reference_rows=" + inspected + " output=" + output.toAbsolutePath());
    }

    private static String unitStart(CodeUnit unit) {
        return unit == null ? "" : unit.getMinAddress().toString();
    }

    private static String unitLength(CodeUnit unit) {
        return unit == null ? "" : Integer.toString(unit.getLength());
    }

    private static String unitType(CodeUnit unit) {
        return unit == null ? "<none>" : unit.getClass().getSimpleName();
    }

    private static String unitText(CodeUnit unit) {
        if (unit == null) return "<none>";
        String text = unit.toString();
        return text.length() <= 160 ? text : text.substring(0, 160);
    }

    private static String functionAddress(Function function) {
        return function == null ? "" : function.getEntryPoint().toString();
    }

    private static String functionName(Function function) {
        return function == null ? "<none>" : function.getName();
    }

    private static String csv(String text) {
        return "\"" + text.replace("\"", "\"\"") + "\"";
    }
}
