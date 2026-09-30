// Read-only instruction windows for a supplied list of relocation target VAs.
// Args: output.csv and target addresses; comma-separated arguments work.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class GhidraDumpTargetInstructionWindows extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) throw new IllegalArgumentException("expected output.csv and addresses");
        List<String> targets = new ArrayList<>();
        for (int i = 1; i < args.length; i++) {
            for (String token : args[i].split(",")) targets.add(token.trim());
        }
        List<String> rows = new ArrayList<>();
        rows.add("target_va,instruction_va,instruction_bytes,instruction,function_owner,terminated,decode_status");
        Listing listing = currentProgram.getListing();
        for (String token : targets) {
            Address target = toAddr(Long.decode(token));
            Address cursor = target;
            Address windowEnd = target.add(0x3F);
            int firstTargetRow = rows.size();
            boolean terminated = false;
            for (int count = 0; count < 16; count++) {
                Instruction instruction = listing.getInstructionAt(cursor);
                String decodeStatus = "existing-instruction";
                if (instruction == null && cursor.compareTo(windowEnd) <= 0) {
                    DisassembleCommand disassemble = new DisassembleCommand(
                        cursor, new AddressSet(target, windowEnd), false);
                    disassemble.applyTo(currentProgram, monitor);
                    instruction = listing.getInstructionAt(cursor);
                    decodeStatus = "disassembled-in-memory";
                }
                if (instruction == null) break;
                Function function = currentProgram.getFunctionManager()
                    .getFunctionContaining(instruction.getAddress());
                StringBuilder bytes = new StringBuilder();
                byte[] raw = new byte[instruction.getLength()];
                currentProgram.getMemory().getBytes(instruction.getAddress(), raw);
                for (byte value : raw) {
                    if (bytes.length() > 0) bytes.append(' ');
                    bytes.append(String.format("%02X", value & 0xff));
                }
                rows.add(target + "," + instruction.getAddress() + "," +
                    csv(bytes.toString()) + "," + csv(instruction.toString()) + "," +
                    csv(function == null ? "" : function.getEntryPoint() + "/" + function.getName()) + ",false," + decodeStatus);
                String mnemonic = instruction.getMnemonicString();
                if (mnemonic.equals("RET") || mnemonic.equals("RETF") ||
                    mnemonic.equals("IRET") || mnemonic.equals("JMP")) {
                    terminated = true;
                    break;
                }
                cursor = instruction.getMaxAddress().next();
                if (cursor.compareTo(windowEnd) > 0) break;
            }
            if (rows.size() == firstTargetRow) {
                rows.add(target + ",,,,,false,no-instruction-at-target");
            } else if (terminated) {
                int last = rows.size() - 1;
                rows.set(last, rows.get(last).replace(",false", ",true"));
            }
        }
        Files.write(Paths.get(args[0]), rows, StandardCharsets.UTF_8);
        println("Wrote target instruction windows: " + args[0] + " (" + targets.size() + " targets)");
    }

    private String csv(String value) {
        return "\"" + value.replace("\"", "\"\"") + "\"";
    }
}
