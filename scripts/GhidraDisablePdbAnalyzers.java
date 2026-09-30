// Pre-script for binary-only audits. Explicitly disable Ghidra's PDB analyzers.
import ghidra.app.script.GhidraScript;
import ghidra.framework.options.Options;
import ghidra.program.model.listing.Program;

public class GhidraDisablePdbAnalyzers extends GhidraScript {
    @Override
    protected void run() throws Exception {
        Options analysisOptions = currentProgram.getOptions(Program.ANALYSIS_PROPERTIES);
        analysisOptions.setBoolean("PDB Universal", false);
        analysisOptions.setBoolean("PDB MSDIA", false);
        println("PDB analysis disabled; continuing with binary-only analysis.");
    }
}
