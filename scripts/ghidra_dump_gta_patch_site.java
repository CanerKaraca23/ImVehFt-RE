// Headless Ghidra script: report the original code around a patched GTA address.
// Usage: -postScript ghidra_dump_gta_patch_site.java 0x0053eca1
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.CodeUnit;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.symbol.Reference;

public class ghidra_dump_gta_patch_site extends GhidraScript {
    @Override
    public void run() throws Exception {
        if (getScriptArgs().length == 0) {
            throw new IllegalArgumentException("Supply a VA, e.g. 0x0053eca1");
        }

        Address site = toAddr(Long.decode(getScriptArgs()[0]));
        println("PROGRAM=" + currentProgram.getName());
        println("IMAGE_BASE=" + currentProgram.getImageBase());
        println("SITE=" + site);

        Function function = getFunctionContaining(site);
        if (function == null) {
            println("FUNCTION_CONTAINING=none");
            disassemble(site);
            function = createFunction(site, null);
        }
        if (function != null) {
            println("FUNCTION=" + function.getName() + " ENTRY=" + function.getEntryPoint()
                + " BODY=" + function.getBody());
            int count = 0;
            for (Instruction instruction : currentProgram.getListing()
                    .getInstructions(function.getBody(), true)) {
                println(instruction.getAddress() + "  " + instruction);
                if (++count >= 400) {
                    println("TRUNCATED_AFTER=400 instructions");
                    break;
                }
            }
        }

        println("REFERENCES_TO_SITE:");
        for (Reference reference : getReferencesTo(site)) {
            println(reference.getFromAddress() + " " + reference.getReferenceType());
        }

        Address table = toAddr(0x0053ecdcL);
        println("NEARBY_DISPATCH_TABLE=" + table);
        println("SELECTOR_BYTE_MAP_53ED08:");
        Address selectorMap = toAddr(0x0053ed08L);
        for (int selector = 0; selector <= 0x26; selector++) {
            int mapped = Byte.toUnsignedInt(getByte(selectorMap.add(selector)));
            if (mapped == 2) {
                println("  SELECTOR=" + selector + " (0x" + Integer.toHexString(selector)
                    + ") maps to slot 2 / 0x0053eca1");
            }
        }
        Address dispatcher = toAddr(0x0053ec24L);
        Address indexedThunk = toAddr(0x004018ceL);
        Address indexedFunction = toAddr(0x0053ec10L);
        println("REFERENCES_TO_INDEXED_FUNCTION=" + indexedFunction);
        for (Reference reference : getReferencesTo(indexedFunction)) {
            println("  " + reference.getFromAddress() + " " + reference.getReferenceType());
            Function owner = getFunctionContaining(reference.getFromAddress());
            if (owner != null) {
                println("  OWNER=" + owner.getName() + " ENTRY=" + owner.getEntryPoint()
                    + " BODY=" + owner.getBody());
                for (Instruction instruction : currentProgram.getListing()
                        .getInstructions(owner.getBody(), true)) {
                    println("    " + instruction.getAddress() + "  " + instruction);
                }
            }
        }
        println("REFERENCES_TO_INDEXED_THUNK=" + indexedThunk);
        for (Reference reference : getReferencesTo(indexedThunk)) {
            println("  " + reference.getFromAddress() + " " + reference.getReferenceType());
            Function owner = getFunctionContaining(reference.getFromAddress());
            if (owner != null) {
                println("  OWNER=" + owner.getName() + " ENTRY=" + owner.getEntryPoint()
                    + " BODY=" + owner.getBody());
                for (Instruction instruction : currentProgram.getListing()
                        .getInstructions(owner.getBody(), true)) {
                    println("    " + instruction.getAddress() + "  " + instruction);
                }
            }
        }
        println("REFERENCES_TO_DISPATCHER=" + dispatcher);
        for (Reference reference : getReferencesTo(dispatcher)) {
            println("  " + reference.getFromAddress() + " " + reference.getReferenceType());
            Function owner = getFunctionContaining(reference.getFromAddress());
            if (owner != null && !owner.getEntryPoint().equals(dispatcher)) {
                println("  OWNER=" + owner.getName() + " ENTRY=" + owner.getEntryPoint()
                    + " BODY=" + owner.getBody());
                for (Instruction instruction : currentProgram.getListing()
                        .getInstructions(owner.getBody(), true)) {
                    println("    " + instruction.getAddress() + "  " + instruction);
                }
            }
        }
        println("REFERENCES_TO_TABLE_BASE:");
        for (Reference reference : getReferencesTo(table)) {
            Address from = reference.getFromAddress();
            println("  " + from + " " + reference.getReferenceType());
            Function owner = getFunctionContaining(from);
            if (owner != null) {
                println("  OWNER=" + owner.getName() + " ENTRY=" + owner.getEntryPoint()
                    + " BODY=" + owner.getBody());
                for (Instruction instruction : currentProgram.getListing()
                        .getInstructions(owner.getBody(), true)) {
                    println("    " + instruction.getAddress() + "  " + instruction);
                }
            }
        }
        for (int offset = 0; offset < 24; offset += 4) {
            Address cell = table.add(offset);
            println("TABLE_CELL=" + cell + " DATA_REFS:");
            for (Reference reference : getReferencesTo(cell)) {
                println("  " + reference.getFromAddress() + " " + reference.getReferenceType());
            }
            try {
                Address target = toAddr(Integer.toUnsignedLong(getInt(cell)));
                println("  VALUE=" + target);
                for (Reference reference : getReferencesTo(target)) {
                    println("    TARGET_REF=" + reference.getFromAddress() + " "
                        + reference.getReferenceType());
                }
            }
            catch (Exception exception) {
                println("  VALUE_READ_ERROR=" + exception.getMessage());
            }
        }

        Address begin = site.subtract(0x30);
        Address end = site.add(0x50);
        println("CODE_UNITS_AROUND_SITE=" + begin + ".." + end);
        for (CodeUnit unit : currentProgram.getListing().getCodeUnits(begin, true)) {
            if (unit.getMinAddress().compareTo(end) > 0) {
                break;
            }
            println(unit.getMinAddress() + "  " + unit);
        }
    }
}
