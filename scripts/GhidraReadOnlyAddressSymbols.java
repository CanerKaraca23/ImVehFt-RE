// Read-only lookup of labels, data units, and references at supplied addresses.
// Args: output.csv and one or more addresses; comma-separated arguments also work.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.CodeUnit;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.mem.MemoryBlock;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class GhidraReadOnlyAddressSymbols extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) {
            throw new IllegalArgumentException("expected output.csv and one or more addresses or an address CSV");
        }
        List<String> rows = new ArrayList<>();
        rows.add("address,memory_block,symbols,data_or_code_unit,incoming_references");
        List<String> addresses = new ArrayList<>();
        if (args.length == 2 && args[1].toLowerCase().endsWith(".csv")) {
            for (String line : Files.readAllLines(Paths.get(args[1]), StandardCharsets.UTF_8)) {
                String normalized = line.replace("\uFEFF", "").trim();
                if (normalized.isBlank() || normalized.toLowerCase().startsWith("address")) continue;
                int comma = line.indexOf(',');
                addresses.add((comma < 0 ? normalized : line.substring(0, comma)).replace("\"", "").trim());
            }
        } else {
            for (int i = 1; i < args.length; i++) {
                for (String token : args[i].split(",")) addresses.add(token.trim());
            }
        }
        for (String token : addresses) {
            String addressText = token.trim();
            if (!addressText.startsWith("0x") && !addressText.startsWith("0X")) {
                addressText = "0x" + addressText;
            }
            Address address = toAddr(Long.decode(addressText));
            StringBuilder symbols = new StringBuilder();
            Symbol[] addressSymbols = currentProgram.getSymbolTable().getSymbols(address);
            for (Symbol symbol : addressSymbols) {
                if (symbols.length() > 0) symbols.append('|');
                symbols.append(symbol.getName().replace("|", "_"))
                    .append('[').append(symbol.getSymbolType())
                    .append(',').append(symbol.getSource())
                    .append(symbol.isPrimary() ? ",primary" : "")
                    .append(']');
            }
            CodeUnit unit = currentProgram.getListing().getCodeUnitContaining(address);
            String unitText = "";
            if (unit != null) {
                unitText = unit.getAddress() + ":" + unit.toString().replace(",", ";");
                if (unit instanceof Data) {
                    unitText += ":type=" + ((Data) unit).getDataType().getName();
                }
            }
            StringBuilder refs = new StringBuilder();
            ReferenceIterator references = currentProgram.getReferenceManager().getReferencesTo(address);
            while (references.hasNext()) {
                Reference reference = references.next();
                if (refs.length() > 0) refs.append('|');
                refs.append(reference.getFromAddress()).append(':').append(reference.getReferenceType());
                Function fromFunction = currentProgram.getFunctionManager()
                    .getFunctionContaining(reference.getFromAddress());
                if (fromFunction != null) {
                    refs.append('@').append(fromFunction.getEntryPoint())
                        .append(':').append(fromFunction.getName().replace('|', '_'));
                }
            }
            MemoryBlock block = currentProgram.getMemory().getBlock(address);
            rows.add(address + ",\"" + csv(block == null ? "" : block.getName()) + "\",\""
                + csv(symbols.toString()) + "\",\"" + csv(unitText) + "\",\""
                + csv(refs.toString()) + "\"");
        }
        Files.write(Paths.get(args[0]), rows, StandardCharsets.UTF_8);
        println("Wrote read-only Ghidra symbol/xref inventory: " + args[0]
            + " (" + (rows.size() - 1) + " addresses)");
    }

    private String csv(String value) {
        return value.replace("\"", "\"\"");
    }
}
