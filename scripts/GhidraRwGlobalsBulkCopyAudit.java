// Find string/bulk memory instructions in functions tied to RwGlobals roots.
// Args: <output.csv>. Read-only triage; this does not infer destination provenance.
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
import java.util.HashSet;
import java.util.Locale;
import java.util.Set;

public class GhidraRwGlobalsBulkCopyAudit extends GhidraScript {
    private static final long[] ROOTS = {0x00c97b24L, 0x00c979c8L, 0x00c97a24L};

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 1) throw new IllegalArgumentException("expected output.csv");

        Set<Function> rootedFunctions = new HashSet<>();
        for (long root : ROOTS) {
            ReferenceIterator refs = currentProgram.getReferenceManager()
                .getReferencesTo(toAddr(root));
            while (refs.hasNext()) {
                Reference ref = refs.next();
                Function function = currentProgram.getFunctionManager()
                    .getFunctionContaining(ref.getFromAddress());
                if (function != null) rootedFunctions.add(function);
            }
        }

        StringBuilder csv = new StringBuilder(
            "address,function_entry,has_rwglobals_root_ref,mnemonic,bytes,instruction\n");
        long visited = 0, stringCount = 0, rootedStringCount = 0;
        InstructionIterator instructions = currentProgram.getListing().getInstructions(true);
        while (instructions.hasNext() && !monitor.isCancelled()) {
            Instruction instruction = instructions.next();
            visited++;
            String mnemonic = instruction.getMnemonicString().toUpperCase(Locale.ROOT);
            int suffix = mnemonic.indexOf('.');
            String baseMnemonic = suffix < 0 ? mnemonic : mnemonic.substring(0, suffix);
            if (!(baseMnemonic.equals("MOVSB") || baseMnemonic.equals("MOVSW")
                    || baseMnemonic.equals("MOVSD") || baseMnemonic.equals("MOVSQ")
                    || baseMnemonic.equals("STOSB") || baseMnemonic.equals("STOSW")
                    || baseMnemonic.equals("STOSD") || baseMnemonic.equals("STOSQ"))) continue;
            String fullInstruction = instruction.toString();
            String upperInstruction = fullInstruction.toUpperCase(Locale.ROOT);
            // Exclude scalar SSE MOVSD and similarly named non-string operations.
            if (!(upperInstruction.contains("ES:EDI") || upperInstruction.contains("ES:RDI"))) continue;
            stringCount++;
            Function function = currentProgram.getFunctionManager()
                .getFunctionContaining(instruction.getAddress());
            if (function == null || !rootedFunctions.contains(function)) continue;
            rootedStringCount++;
            StringBuilder bytes = new StringBuilder();
            for (byte value : instruction.getBytes())
                bytes.append(String.format(Locale.ROOT, "%02X", value & 0xff));
            csv.append(String.format(Locale.ROOT, "0x%08X,%s,true,%s,%s,\"%s\"%n",
                instruction.getAddress().getOffset(), function.getEntryPoint(), mnemonic,
                bytes, fullInstruction.replace("\"", "\"\"")));
        }
        Files.writeString(Paths.get(args[0]), csv.toString(), StandardCharsets.UTF_8);
        println("instructions_visited=" + visited + " confirmed_string_memory_ops=" + stringCount
            + " string_ops_in_rwglobals_rooted_functions=" + rootedStringCount
            + " rooted_functions=" + rootedFunctions.size());
        println("output=" + Paths.get(args[0]).toAbsolutePath());
        println("NOTE: exact string mnemonics and index-register operands are required; this does not infer register provenance.");
    }
}
