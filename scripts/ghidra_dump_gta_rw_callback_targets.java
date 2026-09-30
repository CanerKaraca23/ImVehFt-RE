// Read-only Ghidra query for GTA's RenderWare texture/raster callback chain.
// Usage: -postScript ghidra_dump_gta_rw_callback_targets.java
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.symbol.Reference;
import java.io.FileWriter;
import java.io.PrintWriter;

public class ghidra_dump_gta_rw_callback_targets extends GhidraScript {
    private DecompInterface decompiler;
    private PrintWriter report;

    private void out(String text) {
        println(text);
        report.println(text);
    }

    private void dumpFunction(long value, int maxInstructions) throws Exception {
        Address address = toAddr(value);
        Function function = getFunctionAt(address);
        if (function == null) {
            function = getFunctionContaining(address);
        }
        out("\nTARGET=" + address + " FUNCTION="
            + (function == null ? "none" : function.getName() + " ENTRY=" + function.getEntryPoint()));
        if (function != null) {
            int count = 0;
            for (Instruction instruction : currentProgram.getListing()
                    .getInstructions(function.getBody(), true)) {
                if (instruction.getAddress().compareTo(address) >= 0) {
                    out(instruction.getAddress() + "  " + instruction);
                    if (++count >= maxInstructions) {
                        out("TRUNCATED_AFTER=" + maxInstructions);
                        break;
                    }
                }
            }
            DecompileResults result = decompiler.decompileFunction(function, 30, monitor);
            if (result.decompileCompleted() && result.getDecompiledFunction() != null) {
                out("DECOMPILE_BEGIN\n" + result.getDecompiledFunction().getC());
                out("DECOMPILE_END");
            } else {
                out("DECOMPILE_ERROR=" + result.getErrorMessage());
            }
        } else {
            Address cursor = address;
            int count = 0;
            while (count < maxInstructions) {
                Instruction instruction = currentProgram.getListing().getInstructionAt(cursor);
                if (instruction == null) {
                    if (!disassemble(cursor)) {
                        out("UNDECODED_AT=" + cursor);
                        break;
                    }
                    instruction = currentProgram.getListing().getInstructionAt(cursor);
                }
                if (instruction == null) break;
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
            : "C:/Users/caner/OneDrive/Documents/ImVehFt/_repo_update/ImVehFt-RE-publish2/audit/gta-rw-target-trace-2026-09-29.log";
        report = new PrintWriter(new FileWriter(output, false));
        decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        out("PROGRAM=" + currentProgram.getName() + " IMAGE_BASE=" + currentProgram.getImageBase());
        dumpFunction(0x00748f70L, 120); // registration + callback cluster
        dumpFunction(0x00749020L, 40);  // texture ctor
        dumpFunction(0x00749030L, 40);  // texture dtor
        dumpFunction(0x00749040L, 80);  // texture copy
        dumpFunction(0x007f3820L, 80);  // texture destruction dispatcher
        dumpFunction(0x007f37c0L, 100); // texture creation/registered plugin callbacks
        dumpFunction(0x008086e0L, 80);  // plugin constructor-list walker
        dumpFunction(0x007fb230L, 100); // raster creation
        dumpFunction(0x007fb020L, 50);  // raster destruction dispatcher
        dumpFunction(0x00808740L, 60);  // plugin callback-list walker
        dumpFunction(0x004c9a80L, 60);  // D3D raster plugin dtor
        decompiler.dispose();
        report.close();
    }
}
