// Ghidra headless script: decode the destinations installed by FUN_10002210.
// Run on ImVehFt.asi with -noanalysis.
// Args: <candidate-source.cpp> <output.csv>
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.mem.MemoryBlock;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class GhidraModHookTargets extends GhidraScript {
    private static final Pattern OPCODE = Pattern.compile(
        "local_8\\s*=\\s*(0xE8|0xE9)", Pattern.CASE_INSENSITIVE
    );
    private static final Pattern SITE = Pattern.compile(
        "VP\\(\\s*(0x[0-9A-Fa-f]+)\\s*,\\s*1\\s*,\\s*0x40\\s*,"
    );
    private static final Pattern DISPLACEMENT = Pattern.compile(
        "reinterpret_cast<volatile std::uint32_t\\*>\\("
        + "(0x[0-9A-Fa-f]+)\\)\\s*=\\s*(0x[0-9A-Fa-f]+)"
    );

    private static class Hook {
        long site;
        long target;
        String opcode;
        Hook(long site, long target, String opcode) {
            this.site = site;
            this.target = target;
            this.opcode = opcode;
        }
    }

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) {
            throw new IllegalArgumentException("expected source.cpp and output.csv arguments");
        }
        String source = Files.readString(Paths.get(args[0]), StandardCharsets.UTF_8);
        Matcher opMatcher = OPCODE.matcher(source);
        List<Hook> hooks = new ArrayList<>();
        List<int[]> ranges = new ArrayList<>();
        while (opMatcher.find()) ranges.add(new int[] { opMatcher.start(), opMatcher.end() });
        for (int i = 0; i < ranges.size(); i++) {
            int start = ranges.get(i)[0];
            int end = i + 1 < ranges.size() ? ranges.get(i + 1)[0] : source.length();
            String block = source.substring(start, end);
            Matcher op = OPCODE.matcher(block);
            Matcher siteMatcher = SITE.matcher(block);
            Matcher dispMatcher = DISPLACEMENT.matcher(block);
            if (!op.find() || !siteMatcher.find() || !dispMatcher.find()) continue;
            long site = Long.decode(siteMatcher.group(1));
            long dispAddress = Long.decode(dispMatcher.group(1));
            if (dispAddress != site + 1) continue;
            long displacement = Long.decode(dispMatcher.group(2));
            long target = (site + 5 + displacement) & 0xffffffffL;
            hooks.add(new Hook(site, target, op.group(1).toUpperCase()));
        }

        Map<Long, List<Hook>> byTarget = new LinkedHashMap<>();
        for (Hook hook : hooks) byTarget.computeIfAbsent(hook.target, k -> new ArrayList<>()).add(hook);

        int succeeded = 0;
        int failed = 0;
        for (long target : byTarget.keySet()) {
            Address address = toAddr(target);
            DisassembleCommand command = new DisassembleCommand(address, null, false);
            if (command.applyTo(currentProgram, monitor)) succeeded++;
            else {
                failed++;
                println("DISASSEMBLY_WARNING " + address + " " + command.getStatusMsg());
            }
        }

        List<String> rows = new ArrayList<>();
        rows.add("hook_site,opcode,target,target_block,instruction_address,instruction,bytes_hex");
        int targetsWithInstruction = 0;
        for (Map.Entry<Long, List<Hook>> entry : byTarget.entrySet()) {
            Address target = toAddr(entry.getKey());
            MemoryBlock block = currentProgram.getMemory().getBlock(target);
            String blockName = block == null ? "NO_MEMORY_BLOCK" : block.getName();
            Address rangeEnd = target.add(0x7f);
            InstructionIterator instructions = currentProgram.getListing()
                .getInstructions(new AddressSet(target, rangeEnd), true);
            int count = 0;
            while (instructions.hasNext() && count < 24) {
                Instruction instruction = instructions.next();
                if (count == 0 && instruction.getAddress().equals(target)) {
                    targetsWithInstruction++;
                }
                byte[] raw = new byte[instruction.getLength()];
                currentProgram.getMemory().getBytes(instruction.getAddress(), raw);
                StringBuilder hex = new StringBuilder();
                for (byte value : raw) {
                    if (hex.length() > 0) hex.append(' ');
                    hex.append(String.format("%02X", value & 0xff));
                }
                for (Hook hook : entry.getValue()) {
                    rows.add(String.format(
                        "0x%08X,%s,0x%08X,\"%s\",0x%08X,\"%s\",\"%s\"",
                        hook.site, hook.opcode, hook.target,
                        blockName.replace("\"", "\"\""), instruction.getAddress().getOffset(),
                        instruction.toString().replace("\"", "\"\""), hex
                    ));
                }
                count++;
            }
            if (count == 0) {
                for (Hook hook : entry.getValue()) {
                    rows.add(String.format(
                        "0x%08X,%s,0x%08X,\"%s\",,\"NO_INSTRUCTION_AT_TARGET\",\"\"",
                        hook.site, hook.opcode, hook.target, blockName
                    ));
                }
            }
        }
        Files.write(Paths.get(args[1]), rows, StandardCharsets.UTF_8);
        println("program=" + currentProgram.getName());
        println("hook_branches=" + hooks.size());
        println("unique_destinations=" + byTarget.size());
        println("disassembly_commands_succeeded=" + succeeded);
        println("disassembly_commands_failed=" + failed);
        println("destinations_with_instruction_at_entry=" + targetsWithInstruction);
        println("csv=" + Paths.get(args[1]).toAbsolutePath());
        println("NOTE: direct target decoding is not semantic or runtime validation.");
    }
}
