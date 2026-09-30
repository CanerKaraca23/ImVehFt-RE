// Create temporary function bodies and decompile supplied CRT entry targets.
// Use only in a disposable Ghidra project imported with -noanalysis.
// Args: output.csv and one or more entry VAs.
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Function;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class GhidraDecompileBoundedTargets extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) throw new IllegalArgumentException("expected output.csv and target VAs");
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        List<String> rows = new ArrayList<>();
        rows.add("entry_va,function_entry,function_name,body_min,body_max,signature,decompile_status,pseudocode");
        for (int i = 1; i < args.length; i++) {
            Address entry = toAddr(Long.decode(args[i]));
            AddressSet set = new AddressSet(entry, entry.add(0x3ff));
            new DisassembleCommand(entry, set, false).applyTo(currentProgram, monitor);
            Function function = currentProgram.getFunctionManager().getFunctionAt(entry);
            boolean created = false;
            if (function == null) {
                function = createFunction(entry, "TEMP_CRT_" + entry.toString());
                created = function != null;
            }
            if (function == null) {
                rows.add(entry + ",,,,,,no-function-created,");
                continue;
            }
            DecompileResults result = decompiler.decompileFunction(function, 60, monitor);
            String code = result.decompileCompleted() && result.getDecompiledFunction() != null
                ? result.getDecompiledFunction().getC() : "";
            rows.add(entry + "," + function.getEntryPoint() + ",\"" + csv(function.getName())
                + "\"," + function.getBody().getMinAddress() + "," + function.getBody().getMaxAddress()
                + ",\"" + csv(function.getSignature().getPrototypeString()) + "\","
                + (result.decompileCompleted() ? (created ? "created-and-decompiled" : "decompiled")
                    : "decompile-failed")
                + ",\"" + csv(code) + "\"");
        }
        Files.write(Paths.get(args[0]), rows, StandardCharsets.UTF_8);
        decompiler.dispose();
        println("Wrote temporary target decompilations: " + args[0] + " (" + (rows.size() - 1) + " entries)");
    }

    private String csv(String value) {
        return value.replace("\"", "\"\"").replace("\r", " ").replace("\n", " ");
    }
}
