// Inspect containing functions and incoming references after full Ghidra analysis.
// Args: <summary.csv> <decomp.c> <address> [<address>...]
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

public class GhidraInspectFunctionAddresses extends GhidraScript {
    @Override protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 3) throw new IllegalArgumentException("expected csv, decomp, and addresses");
        List<String> rows = new ArrayList<>();
        rows.add("address,function_entry,function_name,body_min,body_max,incoming_ref_from,ref_type");
        StringBuilder code = new StringBuilder("/* Full-analysis function mapping; decompilation is not original source. */\n");
        Map<String, Function> functions = new LinkedHashMap<>();
        for (int i = 2; i < args.length; i++) {
            Address address = toAddr(Long.decode(args[i].trim()));
            Function f = currentProgram.getFunctionManager().getFunctionContaining(address);
            if (f == null) f = currentProgram.getFunctionManager().getFunctionAt(address);
            ReferenceIterator refs = currentProgram.getReferenceManager().getReferencesTo(address);
            boolean hadRef = false;
            while (refs.hasNext()) {
                Reference ref = refs.next();
                hadRef = true;
                rows.add(String.format("%s,%s,%s,%s,%s,%s,%s", address,
                    f == null ? "" : f.getEntryPoint(), f == null ? "" : "\"" + f.getName().replace("\"", "\"\"") + "\"",
                    f == null ? "" : f.getBody().getMinAddress(), f == null ? "" : f.getBody().getMaxAddress(),
                    ref.getFromAddress(), ref.getReferenceType()));
            }
            if (!hadRef) rows.add(String.format("%s,%s,%s,%s,%s,,NO_INCOMING_REFERENCE", address,
                f == null ? "" : f.getEntryPoint(), f == null ? "" : "\"" + f.getName().replace("\"", "\"\"") + "\"",
                f == null ? "" : f.getBody().getMinAddress(), f == null ? "" : f.getBody().getMaxAddress()));
            if (f != null) functions.putIfAbsent(f.getEntryPoint().toString(), f);
        }
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        for (Function f : functions.values()) {
            DecompileResults result = decompiler.decompileFunction(f, 60, monitor);
            if (result != null && result.decompileCompleted() && result.getDecompiledFunction() != null) {
                code.append("\n/* function ").append(f.getEntryPoint()).append(" ").append(f.getName()).append(" */\n")
                    .append(result.getDecompiledFunction().getC()).append("\n");
            }
        }
        Files.write(Paths.get(args[0]), rows, StandardCharsets.UTF_8);
        Files.writeString(Paths.get(args[1]), code.toString(), StandardCharsets.UTF_8);
        println("addresses=" + (args.length - 2) + " containing_functions=" + functions.size());
        println("summary=" + Paths.get(args[0]).toAbsolutePath());
        println("decomp=" + Paths.get(args[1]).toAbsolutePath());
        decompiler.dispose();
    }
}
