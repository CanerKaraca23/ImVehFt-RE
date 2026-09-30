// Read-only neighboring listing/xrefs for instruction starts from a one-column CSV.
// Args: <input-addresses.csv> <output.csv>; emits existing decoded instructions +/- 0x20 bytes.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class GhidraDumpRelocationInstructionWindows extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) throw new IllegalArgumentException("expected input CSV and output CSV");
        List<String> input = Files.readAllLines(Paths.get(args[0]), StandardCharsets.UTF_8);
        AddressSet windows = new AddressSet();
        int seeds = 0;
        for (String line : input) {
            String value = line.replace("\uFEFF", "").trim();
            String header = value.replace("\"", "").toLowerCase();
            if (value.isBlank() || header.startsWith("address") || header.startsWith("instruction_va")) continue;
            int comma = value.indexOf(',');
            if (comma >= 0) value = value.substring(0, comma);
            value = value.replace("\"", "").trim();
            if (!value.startsWith("0x") && !value.startsWith("0X")) value = "0x" + value;
            Address seed = toAddr(Long.decode(value));
            Address start = seed.subtract(Math.min(0x20, seed.getOffset()));
            Address end = seed.add(0x20);
            windows.add(start, end);
            seeds++;
        }
        List<String> rows = new ArrayList<>();
        rows.add("instruction_va,bytes,assembly,function_entry,function_name,incoming_xrefs");
        InstructionIterator instructions = currentProgram.getListing().getInstructions(windows, true);
        while (instructions.hasNext()) {
            Instruction instruction = instructions.next();
            byte[] raw = new byte[instruction.getLength()];
            currentProgram.getMemory().getBytes(instruction.getAddress(), raw);
            StringBuilder bytes = new StringBuilder();
            for (byte b : raw) {
                if (bytes.length() > 0) bytes.append(' ');
                bytes.append(String.format("%02X", b & 0xff));
            }
            Function function = currentProgram.getFunctionManager().getFunctionContaining(instruction.getAddress());
            StringBuilder refs = new StringBuilder();
            ReferenceIterator iterator = currentProgram.getReferenceManager().getReferencesTo(instruction.getAddress());
            while (iterator.hasNext()) {
                Reference ref = iterator.next();
                if (refs.length() > 0) refs.append('|');
                refs.append(ref.getFromAddress()).append(':').append(ref.getReferenceType());
            }
            rows.add(instruction.getAddress() + "," + csv(bytes.toString()) + "," +
                csv(instruction.toString()) + "," +
                (function == null ? "" : function.getEntryPoint().toString()) + "," +
                csv(function == null ? "" : function.getName()) + "," + csv(refs.toString()));
        }
        Files.write(Paths.get(args[1]), rows, StandardCharsets.UTF_8);
        println("Read-only windows for " + seeds + " seed addresses; wrote " + (rows.size() - 1) + " instructions");
    }

    private String csv(String value) {
        return "\"" + value.replace("\"", "\"\"") + "\"";
    }
}
