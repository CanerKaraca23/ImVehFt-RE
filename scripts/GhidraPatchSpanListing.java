// Ghidra headless script for bounded disassembly around FUN_10002210 writes.
// Run after importing gta_sa.exe with -noanalysis.
// Args: <candidate-source.cpp> <output.csv>
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class GhidraPatchSpanListing extends GhidraScript {
    private static final Pattern SPAN = Pattern.compile(
        "VP\\(\\s*(0x[0-9A-Fa-f]+)\\s*,\\s*([^,]+?)\\s*,\\s*0x40\\s*,"
    );

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) {
            throw new IllegalArgumentException("expected source.cpp and output.csv arguments");
        }

        String source = Files.readString(Paths.get(args[0]), StandardCharsets.UTF_8);
        Matcher matcher = SPAN.matcher(source);
        TreeMap<Long, Integer> spans = new TreeMap<>();
        while (matcher.find()) {
            long address = Long.decode(matcher.group(1));
            int size = Integer.decode(matcher.group(2).trim());
            Integer prior = spans.putIfAbsent(address, size);
            if (prior != null && prior.intValue() != size) {
                throw new IllegalArgumentException("conflicting sizes at " + matcher.group(1));
            }
        }

        // These isolated source spans modify an instruction operand, not an opcode.
        Map<Long, Integer> operandBack = Map.of(
            0x004C8415L, 1,
            0x004C9148L, 1,
            0x006E1D4FL, 1,
            0x006FDF47L, 3
        );

        List<long[]> groups = new ArrayList<>();
        Map<Long, long[]> spanGroups = new HashMap<>();
        for (Map.Entry<Long, Integer> span : spans.entrySet()) {
            long address = span.getKey();
            long end = address + span.getValue();
            long[] group;
            if (groups.isEmpty() || address > groups.get(groups.size() - 1)[1]) {
                group = new long[] { address, end };
                groups.add(group);
            } else {
                group = groups.get(groups.size() - 1);
                group[1] = Math.max(group[1], end);
            }
            spanGroups.put(address, group);
        }

        List<Address> seeds = new ArrayList<>();
        for (long[] group : groups) seeds.add(toAddr(group[0]));

        // Do not treat the one read-only-data callback slot as code.
        seeds.removeIf(seed -> seed.getOffset() == 0x0085C5F4L);
        for (int i = 0; i < seeds.size(); i++) {
            Address seed = seeds.get(i);
            Integer back = operandBack.get(seed.getOffset());
            if (back != null) seeds.set(i, seed.subtract(back));
        }

        int commands = 0;
        int commandFailures = 0;
        for (Address seed : seeds) {
            DisassembleCommand command = new DisassembleCommand(seed, null, false);
            if (command.applyTo(currentProgram, monitor)) {
                commands++;
            } else {
                commandFailures++;
                println("DISASSEMBLY_WARNING " + seed + " " + command.getStatusMsg());
            }
        }

        List<String> rows = new ArrayList<>();
        rows.add("address,size,bytes_hex,classification,instruction_address,instruction_length,instruction,covered_instructions,write_group_start,write_group_size,group_end_on_instruction_boundary");
        int instructionStarts = 0;
        int instructionInteriors = 0;
        int noInstruction = 0;
        for (Map.Entry<Long, Integer> span : spans.entrySet()) {
            Address address = toAddr(span.getKey());
            byte[] bytes = new byte[span.getValue()];
            StringBuilder hex = new StringBuilder();
            try {
                currentProgram.getMemory().getBytes(address, bytes);
                for (byte value : bytes) {
                    if (hex.length() > 0) hex.append(' ');
                    hex.append(String.format("%02X", value & 0xff));
                }
            } catch (Exception e) {
                hex.append("UNREADABLE");
            }

            Instruction instruction = currentProgram.getListing().getInstructionContaining(address);
            String classification;
            String instructionAddress = "";
            String instructionLength = "";
            String instructionText = "";
            StringBuilder coveredInstructions = new StringBuilder();
            try {
                Address lastByte = address.add(span.getValue() - 1);
                AddressSet spanSet = new AddressSet(address, lastByte);
                InstructionIterator covered = currentProgram.getListing()
                    .getInstructions(spanSet, true);
                while (covered.hasNext()) {
                    Instruction item = covered.next();
                    if (coveredInstructions.length() > 0) coveredInstructions.append(" | ");
                    coveredInstructions.append(item.getAddress())
                        .append("+").append(item.getLength()).append(": ").append(item);
                }
            } catch (Exception e) {
                coveredInstructions.append("UNAVAILABLE");
            }
            if (instruction == null) {
                classification = "NO_INSTRUCTION";
                noInstruction++;
            } else {
                instructionAddress = instruction.getAddress().toString();
                instructionLength = Integer.toString(instruction.getLength());
                instructionText = instruction.toString();
                if (instruction.getAddress().equals(address)) {
                    classification = "INSTRUCTION_START";
                    instructionStarts++;
                } else {
                    classification = "INSIDE_INSTRUCTION";
                    instructionInteriors++;
                }
            }

            if (coveredInstructions.length() == 0 && instruction != null) {
                coveredInstructions.append(instruction.getAddress())
                    .append("+").append(instruction.getLength()).append(": ").append(instruction);
            }
            long[] writeGroup = spanGroups.get(span.getKey());
            String groupEndBoundary = "NON_CODE";
            if (writeGroup != null && writeGroup[1] > writeGroup[0]) {
                Address groupLastByte = toAddr(writeGroup[1] - 1);
                Instruction groupLastInstruction = currentProgram.getListing()
                    .getInstructionContaining(groupLastByte);
                if (groupLastInstruction != null) {
                    groupEndBoundary = groupLastInstruction.getAddress()
                        .add(groupLastInstruction.getLength()).equals(toAddr(writeGroup[1]))
                        ? "YES" : "NO";
                }
            }
            rows.add(String.format(
                "0x%08X,%d,\"%s\",%s,%s,%s,\"%s\",\"%s\",0x%08X,%d,%s",
                span.getKey(), span.getValue(), hex, classification,
                instructionAddress, instructionLength,
                instructionText.replace("\"", "\"\""),
                coveredInstructions.toString().replace("\"", "\"\""),
                writeGroup[0], writeGroup[1] - writeGroup[0], groupEndBoundary
            ));
        }

        Files.write(Paths.get(args[1]), rows, StandardCharsets.UTF_8);
        println("program=" + currentProgram.getName());
        println("bounded_disassembly_seeds=" + seeds.size());
        println("disassembly_commands_succeeded=" + commands);
        println("disassembly_commands_failed=" + commandFailures);
        println("spans=" + spans.size());
        println("contiguous_write_groups=" + groups.size());
        println("instruction_starts=" + instructionStarts);
        println("instruction_interiors=" + instructionInteriors);
        println("no_instruction=" + noInstruction);
        println("csv=" + Paths.get(args[1]).toAbsolutePath());
        println("NOTE: bounded disassembly classification is not semantic or runtime validation.");
    }
}
