// Read-only mapping from relocation target VAs to analyzed function bodies.
// Args: output.csv and one or more addresses; comma-separated arguments work.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.CodeUnit;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolTable;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class GhidraRelocationTargetFunctionOwners extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) {
            throw new IllegalArgumentException("expected output.csv and target addresses or an address CSV");
        }
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
        List<String> rows = new ArrayList<>();
        rows.add("address,block,exact_function_entry,containing_function_entry,containing_function_name,body_min,body_max,offset_from_entry,symbols,code_unit_kind,code_unit_min,code_unit_max,instruction_text");
        SymbolTable table = currentProgram.getSymbolTable();
        for (String token : addresses) {
            String addressText = token.startsWith("0x") || token.startsWith("0X")
                ? token : "0x" + token;
            Address address = toAddr(Long.decode(addressText));
            Function exact = currentProgram.getFunctionManager().getFunctionAt(address);
            Function containing = currentProgram.getFunctionManager().getFunctionContaining(address);
            Function owner = exact != null ? exact : containing;
            String symbols = "";
            for (Symbol symbol : table.getSymbols(address)) {
                if (!symbols.isEmpty()) symbols += "|";
                symbols += symbol.getName().replace("|", "_");
            }
            String entry = owner == null ? "" : owner.getEntryPoint().toString();
            String name = owner == null ? "" : owner.getName().replace("|", "_");
            String min = owner == null ? "" : owner.getBody().getMinAddress().toString();
            String max = owner == null ? "" : owner.getBody().getMaxAddress().toString();
            String delta = owner == null ? "" : Long.toHexString(address.subtract(owner.getEntryPoint()));
            String block = currentProgram.getMemory().getBlock(address) == null
                ? "" : currentProgram.getMemory().getBlock(address).getName();
            CodeUnit unit = currentProgram.getListing().getCodeUnitContaining(address);
            String unitKind = unit == null ? "undefined" : unit.getClass().getSimpleName();
            String unitMin = unit == null ? "" : unit.getMinAddress().toString();
            String unitMax = unit == null ? "" : unit.getMaxAddress().toString();
            String instructionText = "";
            Instruction instruction = currentProgram.getListing().getInstructionContaining(address);
            if (instruction != null) {
                StringBuilder text = new StringBuilder(instruction.getMnemonicString());
                for (int i = 0; i < instruction.getNumOperands(); i++) {
                    text.append(i == 0 ? " " : ", ")
                        .append(instruction.getDefaultOperandRepresentation(i));
                }
                instructionText = text.toString();
            }
            rows.add(address + "," + csv(block) + "," +
                (exact == null ? "" : exact.getEntryPoint().toString()) + "," +
                entry + "," + csv(name) + "," + min + "," + max + "," + delta + "," +
                csv(symbols) + "," + csv(unitKind) + "," + unitMin + "," + unitMax + "," +
                csv(instructionText));
        }
        Files.write(Paths.get(args[0]), rows, StandardCharsets.UTF_8);
        println("Wrote relocation target function-owner inventory: " + args[0]
            + " (" + addresses.size() + " addresses)");
    }

    private String csv(String value) {
        return value.replace("\"", "\"\"");
    }
}
