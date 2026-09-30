// Trace incoming call/jump ancestors for non-stack-looking +0x5c stores and
// report the nearest ancestor functions with a direct RwGlobals-root xref.
// This does not prove the root pointer is passed along the path.
// Args: <stores.csv> <ebp-frames.csv> <root-address> <output.csv> <max-depth>
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class GhidraTraceFieldStoreAncestors extends GhidraScript {
    private static class Node {
        Address function;
        String chain;
        Node(Address function, String chain) { this.function = function; this.chain = chain; }
    }

    private Address root;
    private final Map<Address, Integer> rootCounts = new HashMap<>();
    private final Map<Address, List<Address>> callers = new HashMap<>();

    @Override protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 5) throw new IllegalArgumentException("expected stores.csv ebp-frames.csv root output.csv max-depth");
        root = toAddr(Long.decode(args[2]));
        int maxDepth = Integer.parseInt(args[4]);
        Map<String, Boolean> stackEbp = new HashMap<>();
        for (String line : Files.readAllLines(Paths.get(args[1]), StandardCharsets.UTF_8)) {
            String[] f = line.split(",", 6);
            if (f.length >= 4 && !f[0].equalsIgnoreCase("function_entry"))
                stackEbp.put(f[0].replace("\"", ""), f[3].replace("\"", "").equalsIgnoreCase("true"));
        }
        Map<Address, List<String>> candidates = new LinkedHashMap<>();
        List<String> stores = Files.readAllLines(Paths.get(args[0]), StandardCharsets.UTF_8);
        for (int i = 1; i < stores.size(); i++) {
            String[] f = stores.get(i).split(",", 6);
            if (f.length < 6 || f[1].trim().isEmpty()) continue;
            String dest = f[4].toUpperCase();
            if (dest.contains("ESP")) continue;
            String ownerText = f[1].replace("\"", "").trim();
            if (dest.contains("EBP") && stackEbp.getOrDefault(ownerText, false)) continue;
            Address owner = toAddr(Long.decode("0x" + ownerText.replace("0x", "")));
            candidates.computeIfAbsent(owner, k -> new ArrayList<>()).add(f[0].replace("\"", "").trim());
        }

        List<String> rows = new ArrayList<>();
        rows.add("candidate_owner,candidate_store_count,nearest_root_ancestor_depth,root_ancestor,root_xref_count,call_chain,note");
        int reached = 0, capped = 0;
        for (Map.Entry<Address, List<String>> candidate : candidates.entrySet()) {
            Address start = candidate.getKey();
            Function startFunction = currentProgram.getFunctionManager().getFunctionAt(start);
            if (startFunction == null) continue;
            int direct = rootCount(startFunction);
            if (direct > 0) {
                rows.add(row(start, candidate.getValue().size(), 0, start, direct, start.toString(), "candidate function directly references root"));
                reached++;
                continue;
            }
            List<Node> frontier = new ArrayList<>();
            frontier.add(new Node(start, start.toString()));
            Set<Address> seen = new HashSet<>();
            seen.add(start);
            boolean found = false;
            for (int depth = 1; depth <= maxDepth && !frontier.isEmpty(); depth++) {
                List<Node> next = new ArrayList<>();
                List<String> hits = new ArrayList<>();
                for (Node node : frontier) {
                    for (Address parent : getCallers(node.function)) {
                        if (!seen.add(parent)) continue;
                        String chain = node.chain + " <- " + parent;
                        Function parentFunction = currentProgram.getFunctionManager().getFunctionAt(parent);
                        if (parentFunction == null) continue;
                        int refs = rootCount(parentFunction);
                        if (refs > 0) hits.add(parent + "|" + refs + "|" + chain);
                        else next.add(new Node(parent, chain));
                        if (seen.size() >= 2000) { capped++; break; }
                    }
                    if (seen.size() >= 2000) break;
                }
                if (!hits.isEmpty()) {
                    for (String hit : hits) {
                        String[] h = hit.split("\\|", 3);
                        rows.add(row(start, candidate.getValue().size(), depth, toAddr(Long.decode("0x" + h[0])),
                            Integer.parseInt(h[1]), h[2], "ancestor has a direct root xref; pointer flow not proven"));
                    }
                    reached++;
                    found = true;
                    break;
                }
                frontier = next;
                if (seen.size() >= 2000) break;
            }
            if (!found) rows.add(row(start, candidate.getValue().size(), -1, null, 0, "", seen.size() >= 2000
                ? "search capped at 2000 unique functions" : "no root-xref ancestor found within depth limit"));
        }
        Files.write(Paths.get(args[3]), rows, StandardCharsets.UTF_8);
        println("candidate_owners=" + candidates.size() + " owners_with_root_ancestor=" + reached
            + " capped_searches=" + capped + " output=" + Paths.get(args[3]).toAbsolutePath());
    }

    private int rootCount(Function function) {
        Address entry = function.getEntryPoint();
        Integer cached = rootCounts.get(entry);
        if (cached != null) return cached;
        int count = 0;
        InstructionIterator it = currentProgram.getListing().getInstructions(function.getBody(), true);
        while (it.hasNext()) {
            Instruction ins = it.next();
            for (Reference ref : currentProgram.getReferenceManager().getReferencesFrom(ins.getAddress()))
                if (ref.getToAddress().equals(root)) count++;
        }
        rootCounts.put(entry, count);
        return count;
    }

    private List<Address> getCallers(Address target) {
        List<Address> cached = callers.get(target);
        if (cached != null) return cached;
        List<Address> result = new ArrayList<>();
        ReferenceIterator it = currentProgram.getReferenceManager().getReferencesTo(target);
        while (it.hasNext()) {
            Reference ref = it.next();
            if (!ref.getReferenceType().isCall() && !ref.getReferenceType().isJump()) continue;
            Function caller = currentProgram.getFunctionManager().getFunctionContaining(ref.getFromAddress());
            if (caller != null && !caller.getEntryPoint().equals(target) && !result.contains(caller.getEntryPoint()))
                result.add(caller.getEntryPoint());
        }
        callers.put(target, result);
        return result;
    }

    private String row(Address candidate, int count, int depth, Address ancestor, int refs, String chain, String note) {
        return candidate + "," + count + "," + depth + "," + (ancestor == null ? "" : ancestor.toString())
            + "," + refs + ",\"" + chain.replace("\"", "'") + "\",\"" + note.replace("\"", "'") + "\"";
    }
}
