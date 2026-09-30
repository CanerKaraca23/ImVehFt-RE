// Whole-listing syntactic stores to one or more base-register field offsets.
// Args: <output.csv> <offset> [<offset> ...]. Read-only; no provenance inference.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Locale;
import java.util.Set;
import java.util.regex.Pattern;

public class GhidraFindFieldStores extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) throw new IllegalArgumentException("expected output.csv and one or more offsets");
        Set<String> patterns = new LinkedHashSet<>();
        for (int i = 1; i < args.length; i++) {
            String value = args[i].trim().toLowerCase(Locale.ROOT);
            if (value.startsWith("0x")) value = value.substring(2);
            if (value.endsWith("h")) value = value.substring(0, value.length() - 1);
            patterns.add(".*\\+\\s*(?:0x)?" + Pattern.quote(value) + "h?\\s*\\].*");
        }
        List<Pattern> offsets = new ArrayList<>();
        for (String pattern : patterns) offsets.add(Pattern.compile(pattern));

        List<String> rows = new ArrayList<>();
        rows.add("address,function_entry,mnemonic,bytes,destination,full_instruction");
        long visited = 0, hits = 0;
        InstructionIterator iterator = currentProgram.getListing().getInstructions(true);
        while (iterator.hasNext() && !monitor.isCancelled()) {
            Instruction instruction = iterator.next();
            visited++;
            String mnemonic = instruction.getMnemonicString().toUpperCase(Locale.ROOT);
            if (!(mnemonic.startsWith("MOV") || mnemonic.equals("XCHG")
                    || mnemonic.equals("INC") || mnemonic.equals("DEC")
                    || mnemonic.equals("ADD") || mnemonic.equals("SUB")
                    || mnemonic.equals("AND") || mnemonic.equals("OR"))) continue;
            String destination = instruction.getDefaultOperandRepresentation(0);
            if (destination == null || !destination.contains("[")) continue;
            boolean matches = false;
            for (Pattern pattern : offsets) if (pattern.matcher(destination.toLowerCase(Locale.ROOT)).matches()) {
                matches = true; break;
            }
            if (!matches) continue;
            Address at = instruction.getAddress();
            Function function = currentProgram.getFunctionManager().getFunctionContaining(at);
            StringBuilder bytes = new StringBuilder();
            for (byte value : instruction.getBytes()) bytes.append(String.format(Locale.ROOT, "%02X", value & 0xff));
            rows.add(String.format(Locale.ROOT, "0x%08X,%s,%s,%s,\"%s\",\"%s\"",
                at.getOffset(), function == null ? "" : function.getEntryPoint(), csv(mnemonic),
                bytes, csv(destination), csv(instruction.toString())));
            hits++;
        }
        Files.write(Paths.get(args[0]), rows, StandardCharsets.UTF_8);
        println("instructions_visited=" + visited + " syntactic_store_candidates=" + hits);
        println("output=" + Paths.get(args[0]).toAbsolutePath());
        println("NOTE: base-register provenance and function-boundary validity are not inferred.");
    }

    private String csv(String value) { return value.replace("\"", "\"\""); }
}
