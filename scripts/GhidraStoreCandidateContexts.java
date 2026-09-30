// Emit exact listing windows around syntactic memory-slot write candidates.
// Args: <candidate.csv> <context.csv> [window-radius]. Read-only evidence only.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class GhidraStoreCandidateContexts extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2 || args.length > 3) {
            throw new IllegalArgumentException("expected candidate.csv context.csv [window-radius]");
        }
        int radius = args.length == 3 ? Integer.parseInt(args[2]) : 5;
        if (radius < 1 || radius > 32) throw new IllegalArgumentException("window-radius must be 1..32");

        List<String> rows = new ArrayList<>();
        rows.add("candidate,owner,block,relation,instruction_address,mnemonic,bytes,instruction_text,incoming_refs,function_incoming_refs");
        Listing listing = currentProgram.getListing();
        List<String> lines = Files.readAllLines(Paths.get(args[0]), StandardCharsets.UTF_8);
        int candidates = 0;
        for (int lineNo = 1; lineNo < lines.size(); lineNo++) {
            String line = lines.get(lineNo).trim();
            if (line.isEmpty()) continue;
            String first = line.split(",", 2)[0].trim();
            if (first.startsWith("\"")) first = first.substring(1, first.length() - 1);
            Address candidate;
            try { candidate = toAddr(Long.decode(first)); }
            catch (Exception ex) { println("skip malformed candidate line " + (lineNo + 1) + ": " + first); continue; }
            Instruction hit = listing.getInstructionAt(candidate);
            if (hit == null) {
                rows.add(csv(candidate.toString()) + ",,,,,,,NO_INSTRUCTION_AT_ADDRESS,");
                continue;
            }
            candidates++;
            Function function = currentProgram.getFunctionManager().getFunctionContaining(candidate);
            MemoryBlock block = currentProgram.getMemory().getBlock(candidate);
            String owner = function == null ? "" : function.getEntryPoint().toString();
            String blockName = block == null ? "" : block.getName();
            String refs = incoming(candidate);
            String functionRefs = function == null ? "" : incoming(function.getEntryPoint());

            List<Instruction> before = new ArrayList<>();
            Instruction cursor = hit;
            for (int n = 0; n < radius; n++) {
                cursor = listing.getInstructionBefore(cursor.getAddress());
                if (cursor == null || (block != null && !block.contains(cursor.getAddress()))) break;
                before.add(0, cursor);
            }
            for (Instruction instruction : before) append(rows, candidate, owner, blockName, "before", instruction, "", "");
            append(rows, candidate, owner, blockName, "candidate", hit, refs, functionRefs);
            cursor = hit;
            for (int n = 0; n < radius; n++) {
                cursor = listing.getInstructionAfter(cursor.getAddress());
                if (cursor == null || (block != null && !block.contains(cursor.getAddress()))) break;
                append(rows, candidate, owner, blockName, "after", cursor, "", "");
            }
        }
        Files.write(Paths.get(args[1]), rows, StandardCharsets.UTF_8);
        println("candidates_with_listing=" + candidates + " output_rows=" + (rows.size() - 1));
        println("output=" + Paths.get(args[1]).toAbsolutePath());
        println("NOTE: listing windows do not infer register provenance or function boundaries.");
    }

    private void append(List<String> rows, Address candidate, String owner, String block,
                        String relation, Instruction instruction, String refs, String functionRefs) throws Exception {
        StringBuilder bytes = new StringBuilder();
        for (byte value : instruction.getBytes()) bytes.append(String.format(Locale.ROOT, "%02X", value & 0xff));
        rows.add(String.join(",", csv(candidate.toString()), csv(owner), csv(block), csv(relation),
            csv(instruction.getAddress().toString()), csv(instruction.getMnemonicString()),
            csv(bytes.toString()), csv(instruction.toString()), csv(refs), csv(functionRefs)));
    }

    private String incoming(Address address) {
        List<String> from = new ArrayList<>();
        ReferenceIterator refs = currentProgram.getReferenceManager().getReferencesTo(address);
        while (refs.hasNext()) {
            Reference ref = refs.next();
            from.add(ref.getFromAddress() + ":" + ref.getReferenceType());
        }
        return String.join("|", from);
    }

    private String csv(String value) { return "\"" + value.replace("\"", "\"\"") + "\""; }
}
