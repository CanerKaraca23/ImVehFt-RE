// Bounded, in-memory decode of supplied code addresses; does not run auto-analysis.
// Args: output.csv, maxInstructions, and one or more target VAs.
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class GhidraDumpBoundedCodeTargets extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 3) {
            throw new IllegalArgumentException("expected output.csv, maxInstructions, and target VAs");
        }
        int maxInstructions = Integer.parseInt(args[1]);
        if (maxInstructions < 1 || maxInstructions > 256) {
            throw new IllegalArgumentException("maxInstructions must be between 1 and 256");
        }
        List<String> rows = new ArrayList<>();
        rows.add("target_va,instruction_va,instruction_bytes,instruction,function_owner,decode_status");
        Listing listing = currentProgram.getListing();
        for (int targetIndex = 2; targetIndex < args.length; targetIndex++) {
            Address target = toAddr(Long.decode(args[targetIndex]));
            Address cursor = target;
            Address windowEnd = target.add(0x3ff);
            for (int count = 0; count < maxInstructions; count++) {
                Instruction instruction = listing.getInstructionAt(cursor);
                String decodeStatus = "existing-instruction";
                if (instruction == null && cursor.compareTo(windowEnd) <= 0) {
                    DisassembleCommand command = new DisassembleCommand(
                        cursor, new AddressSet(target, windowEnd), false);
                    command.applyTo(currentProgram, monitor);
                    instruction = listing.getInstructionAt(cursor);
                    decodeStatus = "disassembled-in-memory";
                }
                if (instruction == null) break;
                Function function = currentProgram.getFunctionManager()
                    .getFunctionContaining(instruction.getAddress());
                byte[] bytes = new byte[instruction.getLength()];
                currentProgram.getMemory().getBytes(instruction.getAddress(), bytes);
                StringBuilder hex = new StringBuilder();
                for (byte value : bytes) {
                    if (hex.length() > 0) hex.append(' ');
                    hex.append(String.format("%02X", value & 0xff));
                }
                rows.add(target + "," + instruction.getAddress() + ",\"" + csv(hex.toString())
                    + "\",\"" + csv(instruction.toString()) + "\",\""
                    + csv(function == null ? "" : function.getEntryPoint() + "/" + function.getName())
                    + "\"," + decodeStatus);
                String mnemonic = instruction.getMnemonicString();
                if (mnemonic.equals("RET") || mnemonic.equals("RETF") ||
                    mnemonic.equals("IRET") || mnemonic.equals("JMP")) break;
                cursor = instruction.getMaxAddress().next();
                if (cursor.compareTo(windowEnd) > 0) break;
            }
        }
        Files.write(Paths.get(args[0]), rows, StandardCharsets.UTF_8);
        println("Wrote bounded in-memory target listing: " + args[0]
            + " (" + (rows.size() - 1) + " instructions)");
    }

    private String csv(String value) {
        return value.replace("\"", "\"\"");
    }
}
