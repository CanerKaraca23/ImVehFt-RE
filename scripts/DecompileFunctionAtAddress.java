// Ghidra headless helper: decompile one function and print its listing.
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class DecompileFunctionAtAddress extends GhidraScript {
    @Override
    protected void run() throws Exception {
        if (getScriptArgs().length < 1 || getScriptArgs().length > 2) {
            throw new IllegalArgumentException(
                "Usage: DecompileFunctionAtAddress.java <address> [output-file]");
        }

        Address address = toAddr(getScriptArgs()[0]);
        Function function = currentProgram.getFunctionManager().getFunctionAt(address);
        if (function == null) {
            function = currentProgram.getFunctionManager().getFunctionContaining(address);
        }
        if (function == null) {
            throw new IllegalStateException("No function at " + address);
        }

        StringBuilder evidence = new StringBuilder();
        evidence.append("FUNCTION ").append(function.getName()).append(" @ ")
            .append(function.getEntryPoint()).append('\n');
        for (Instruction instruction : currentProgram.getListing().getInstructions(function.getBody(), true)) {
            evidence.append(instruction.getAddress()).append("  ")
                .append(instruction).append('\n');
        }

        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        DecompileResults result = decompiler.decompileFunction(function, 120, monitor);
        if (!result.decompileCompleted() || result.getDecompiledFunction() == null) {
            throw new IllegalStateException("Decompile failed: " + result.getErrorMessage());
        }
        evidence.append("\nDECOMPILED SOURCE\n")
            .append(result.getDecompiledFunction().getC()).append('\n');
        println(evidence.toString());
        if (getScriptArgs().length == 2) {
            Path output = Paths.get(getScriptArgs()[1]);
            Files.writeString(output, evidence.toString(), StandardCharsets.UTF_8);
        }
        decompiler.dispose();
    }
}
