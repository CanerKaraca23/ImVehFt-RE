// Read-only Ghidra query for ImVehFt's MEXT callback and owned-texture lifecycle.
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.symbol.Reference;
import java.io.FileWriter;
import java.io.PrintWriter;

public class ghidra_dump_mext_owned_texture_lifecycle extends GhidraScript {
    private DecompInterface decompiler;
    private PrintWriter report;

    private void out(String text) {
        println(text);
        report.println(text);
    }

    private void dump(long value, int instructionLimit) throws Exception {
        Address address = toAddr(value);
        Function function = getFunctionAt(address);
        if (function == null) function = getFunctionContaining(address);
        out("\nTARGET=" + address + " FUNCTION="
            + (function == null ? "none" : function.getName() + " ENTRY=" + function.getEntryPoint()));

        if (function != null) {
            int count = 0;
            for (Instruction instruction : currentProgram.getListing()
                    .getInstructions(function.getBody(), true)) {
                out(instruction.getAddress() + "  " + instruction);
                if (++count >= instructionLimit) {
                    out("TRUNCATED_AFTER=" + instructionLimit);
                    break;
                }
            }
            DecompileResults result = decompiler.decompileFunction(function, 30, monitor);
            if (result.decompileCompleted() && result.getDecompiledFunction() != null) {
                out("DECOMPILE_BEGIN\n" + result.getDecompiledFunction().getC());
                out("DECOMPILE_END");
            } else out("DECOMPILE_ERROR=" + result.getErrorMessage());
        } else {
            Address cursor = address;
            int count = 0;
            while (count < instructionLimit) {
                Instruction instruction = currentProgram.getListing().getInstructionAt(cursor);
                if (instruction == null && disassemble(cursor)) {
                    instruction = currentProgram.getListing().getInstructionAt(cursor);
                }
                if (instruction == null) {
                    out("UNDECODED_AT=" + cursor);
                    break;
                }
                out(instruction.getAddress() + "  " + instruction);
                cursor = instruction.getMaxAddress().next();
                count++;
            }
        }
        out("REFERENCES_TO_TARGET:");
        for (Reference reference : getReferencesTo(address)) {
            out("  " + reference.getFromAddress() + " " + reference.getReferenceType());
        }
    }

    @Override
    public void run() throws Exception {
        String output = getScriptArgs().length > 0 ? getScriptArgs()[0]
            : "C:/Users/caner/OneDrive/Documents/ImVehFt/_repo_update/ImVehFt-RE-publish2/audit/mext-owned-texture-lifecycle-2026-09-29.log";
        report = new PrintWriter(new FileWriter(output, false));
        decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        out("PROGRAM=" + currentProgram.getName() + " IMAGE_BASE=" + currentProgram.getImageBase());
        dump(0x10001850L, 100); // MEXT registration
        dump(0x100018a0L, 120); // texture-dictionary callback registration
        dump(0x10001980L, 180); // creates and assigns MEXT-owned texture
        dump(0x10001ad0L, 40);  // MEXT plugin constructor
        dump(0x10001b00L, 60);  // MEXT plugin destructor
        dump(0x10001b30L, 100); // MEXT plugin copy callback
        decompiler.dispose();
        report.close();
    }
}
