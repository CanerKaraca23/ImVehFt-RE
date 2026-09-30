// Read-only Ghidra listing and incoming-reference dump for a bounded address range.
// Args: <start> <end> <output-file>
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

public class GhidraDumpListingRange extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 3) {
            throw new IllegalArgumentException("expected start, end, and output-file arguments");
        }
        Address start = toAddr(Long.decode(args[0]));
        Address end = toAddr(Long.decode(args[1]));
        AddressSet range = new AddressSet(start, end);
        List<String> rows = new ArrayList<>();
        rows.add("READ-ONLY Ghidra listing: " + start + ".." + end);
        InstructionIterator instructions = currentProgram.getListing().getInstructions(range, true);
        while (instructions.hasNext()) {
            Instruction instruction = instructions.next();
            Function function = currentProgram.getFunctionManager()
                .getFunctionContaining(instruction.getAddress());
            StringBuilder row = new StringBuilder(instruction.getAddress().toString())
                .append("  ").append(instruction)
                .append("  FUNCTION=")
                .append(function == null ? "<none>" : function.getEntryPoint() + "/" + function.getName());
            ReferenceIterator refs = currentProgram.getReferenceManager()
                .getReferencesTo(instruction.getAddress());
            while (refs.hasNext()) {
                Reference ref = refs.next();
                row.append("  XREF=").append(ref.getFromAddress())
                    .append(':').append(ref.getReferenceType());
            }
            rows.add(row.toString());
        }
        Files.write(Paths.get(args[2]), rows, StandardCharsets.UTF_8);
        println("Wrote " + (rows.size() - 1) + " read-only listing rows to " + args[2]);
    }
}
