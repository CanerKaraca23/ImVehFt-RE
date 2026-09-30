// Search the existing Ghidra listing for stores to RwGlobals allocator slots.
// Args: <output.csv>. This is a syntactic candidate scan, not register provenance.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.regex.Pattern;

public class GhidraFindRwMemorySlotStores extends GhidraScript {
    private static final Pattern SLOT = Pattern.compile(".*\\+\\s*(?:0x)?(?:144|148)h?\\s*\\].*");

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 1) throw new IllegalArgumentException("expected output.csv");
        List<String> rows = new ArrayList<>();
        rows.add("address,function_entry,mnemonic,bytes,destination,full_instruction");
        long visited = 0;
        long hits = 0;
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
            if (destination == null || !destination.contains("[") || !SLOT.matcher(destination).matches()) continue;
            Address address = instruction.getAddress();
            Function function = currentProgram.getFunctionManager().getFunctionContaining(address);
            rows.add(String.format(Locale.ROOT, "0x%08X,%s,%s,%s,\"%s\",\"%s\"",
                address.getOffset(), function == null ? "" : function.getEntryPoint(),
                csv(mnemonic), bytes(instruction.getBytes()), csv(destination), csv(instruction.toString())));
            hits++;
        }
        Files.write(Paths.get(args[0]), rows, StandardCharsets.UTF_8);
        println("instructions_visited=" + visited + " syntactic_store_candidates=" + hits);
        println("output=" + Paths.get(args[0]).toAbsolutePath());
        println("NOTE: matches are syntactic only; base-register provenance must be verified separately.");
    }

    private String bytes(byte[] values) {
        StringBuilder output = new StringBuilder();
        for (byte value : values) output.append(String.format(Locale.ROOT, "%02X", value & 0xff));
        return output.toString();
    }

    private String csv(String value) {
        return value.replace("\"", "\"\"");
    }
}
