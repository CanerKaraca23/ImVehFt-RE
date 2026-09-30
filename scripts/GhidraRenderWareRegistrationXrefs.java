// Full-analysis xref/decompile inventory for RenderWare registration wrappers.
// Args: <summary.csv> <callers.c> <target-address> [<target-address>...]
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public class GhidraRenderWareRegistrationXrefs extends GhidraScript {
    @Override protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 3) throw new IllegalArgumentException("expected csv, decomp, and target addresses");
        List<String> rows = new ArrayList<>();
        rows.add("target,reference_from,reference_type,caller_entry,caller_name,decompile_status");
        StringBuilder pseudocode = new StringBuilder("/* Ghidra full-analysis xref callers; not original source. */\n");
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        Map<String, Function> callers = new LinkedHashMap<>();
        for (int i = 2; i < args.length; i++) {
            Address target = toAddr(Long.decode(args[i].trim()));
            ReferenceIterator refs = currentProgram.getReferenceManager().getReferencesTo(target);
            while (refs.hasNext()) {
                Reference ref = refs.next();
                Function caller = currentProgram.getFunctionManager().getFunctionContaining(ref.getFromAddress());
                if (caller == null) {
                    rows.add(String.format("%s,%s,%s,,,no_containing_function", target, ref.getFromAddress(), ref.getReferenceType()));
                    continue;
                }
                String key = caller.getEntryPoint().toString();
                if (!callers.containsKey(key)) callers.put(key, caller);
                rows.add(String.format("%s,%s,%s,%s,\"%s\",queued", target, ref.getFromAddress(), ref.getReferenceType(),
                    caller.getEntryPoint(), caller.getName().replace("\"", "\"\"")));
            }
        }
        for (Function caller : callers.values()) {
            DecompileResults result = decompiler.decompileFunction(caller, 60, monitor);
            boolean ok = result != null && result.decompileCompleted() && result.getDecompiledFunction() != null;
            if (ok) {
                pseudocode.append("\n/* caller ").append(caller.getEntryPoint()).append(" ")
                    .append(caller.getName()).append(" */\n")
                    .append(result.getDecompiledFunction().getC()).append("\n");
            }
            for (int row = 1; row < rows.size(); row++) {
                String prefix = caller.getEntryPoint().toString() + ",";
                if (rows.get(row).contains(prefix)) {
                    rows.set(row, rows.get(row).replace(",queued", ok ? ",decompiled" : ",decompile_failed"));
                }
            }
        }
        Files.write(Paths.get(args[0]), rows, StandardCharsets.UTF_8);
        Files.writeString(Paths.get(args[1]), pseudocode.toString(), StandardCharsets.UTF_8);
        println("registration_targets=" + (args.length - 2) + " callers=" + callers.size());
        println("summary=" + Paths.get(args[0]).toAbsolutePath());
        println("decomp=" + Paths.get(args[1]).toAbsolutePath());
        decompiler.dispose();
    }
}
