// Map callers of functions containing syntactic allocator-slot writes.
// Args: <candidate.csv> <rwglobals-root-address> <output.csv>.
// Read-only cross-reference and listing evidence; does not infer argument semantics.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Set;

public class GhidraCandidateStoreCallers extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 3) throw new IllegalArgumentException("expected candidate.csv rwglobals-root output.csv");
        Address root = toAddr(Long.decode(args[1]));
        Map<Address, Set<String>> candidatesByOwner = new LinkedHashMap<>();
        List<String> input = Files.readAllLines(Paths.get(args[0]), StandardCharsets.UTF_8);
        for (int i = 1; i < input.size(); i++) {
            String[] columns = input.get(i).split(",", 3);
            if (columns.length < 2 || columns[1].trim().isEmpty()) continue;
            Address owner = toAddr(parseHexAddr(columns[1].trim()));
            candidatesByOwner.computeIfAbsent(owner, key -> new LinkedHashSet<>()).add(columns[0].trim());
        }

        Listing listing = currentProgram.getListing();
        List<String> rows = new ArrayList<>();
        rows.add("candidate_owner,candidate_addresses,candidate_owner_has_root_xref,callsite,reference_type,caller_owner,caller_has_root_xref,caller_root_xref_count,callsite_context");
        int mappedRefs = 0;
        int rootUsingCallers = 0;
        for (Map.Entry<Address, Set<String>> entry : candidatesByOwner.entrySet()) {
            Address ownerAddress = entry.getKey();
            Function target = currentProgram.getFunctionManager().getFunctionAt(ownerAddress);
            if (target == null) continue;
            List<Reference> incoming = new ArrayList<>();
            ReferenceIterator iterator = currentProgram.getReferenceManager().getReferencesTo(ownerAddress);
            while (iterator.hasNext()) incoming.add(iterator.next());
            int targetRootRefs = countRootRefs(target, root);
            if (incoming.isEmpty()) {
                rows.add(row(ownerAddress, entry.getValue(), targetRootRefs, null, null, 0, ""));
                continue;
            }
            for (Reference ref : incoming) {
                Function caller = currentProgram.getFunctionManager().getFunctionContaining(ref.getFromAddress());
                int callerRootRefs = caller == null ? 0 : countRootRefs(caller, root);
                if (callerRootRefs > 0) rootUsingCallers++;
                rows.add(row(ownerAddress, entry.getValue(), targetRootRefs, ref,
                    caller, callerRootRefs, listingContext(listing, ref.getFromAddress(), 6)));
                mappedRefs++;
            }
        }
        Files.write(Paths.get(args[2]), rows, StandardCharsets.UTF_8);
        println("candidate_functions=" + candidatesByOwner.size() + " incoming_refs=" + mappedRefs
            + " references_from_callers_with_direct_root_xref=" + rootUsingCallers);
        println("output=" + Paths.get(args[2]).toAbsolutePath());
        println("NOTE: caller-level root references do not prove that the root pointer is passed as an argument.");
    }

    private int countRootRefs(Function function, Address root) {
        int count = 0;
        ReferenceIterator refs = currentProgram.getReferenceManager().getReferencesTo(root);
        while (refs.hasNext()) {
            Address from = refs.next().getFromAddress();
            if (function.getBody().contains(from)) count++;
        }
        return count;
    }

    private long parseHexAddr(String text) {
        String value = text.trim();
        if (value.startsWith("0x") || value.startsWith("0X")) value = value.substring(2);
        return Long.parseUnsignedLong(value, 16);
    }

    private String listingContext(Listing listing, Address site, int radius) {
        Instruction at = listing.getInstructionAt(site);
        if (at == null) return "";
        List<String> before = new ArrayList<>();
        Instruction cursor = at;
        for (int i = 0; i < radius; i++) {
            cursor = listing.getInstructionBefore(cursor.getAddress());
            if (cursor == null) break;
            before.add(0, cursor.toString());
        }
        before.add(at.toString());
        return String.join(" | ", before);
    }

    private String row(Address target, Set<String> candidates, int targetRootRefs, Reference ref,
                       Function caller, int callerRootRefs, String context) {
        return String.join(",", csv(target.toString()), csv(String.join("|", candidates)),
            Integer.toString(targetRootRefs), csv(ref == null ? "" : ref.getFromAddress().toString()),
            csv(ref == null ? "NO_INCOMING_REFERENCE" : ref.getReferenceType().toString()),
            csv(caller == null ? "" : caller.getEntryPoint().toString()),
            Boolean.toString(callerRootRefs > 0), Integer.toString(callerRootRefs), csv(context));
    }

    private String csv(String value) { return "\"" + value.replace("\"", "\"\"") + "\""; }
}
