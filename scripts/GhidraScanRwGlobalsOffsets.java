// Scan bounded CFGs for functions referencing RwEngineInstance for selected
// RwGlobals field displacements. Args: <xref.csv> <output.csv> <instruction-cap> [comma-separated offsets].
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.mem.MemoryBlock;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Locale;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class GhidraScanRwGlobalsOffsets extends GhidraScript {
    private static final Pattern OWNER = Pattern.compile("@([0-9a-fA-F]{8}):[^|]+") ;

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 3) {
            throw new IllegalArgumentException("expected xref.csv output.csv instruction-cap [offsets]");
        }
        int cap = Integer.parseInt(args[2]);
        List<String> trackedOffsetList = new ArrayList<>();
        if (args.length == 3) {
            trackedOffsetList.add("0x5c");
            trackedOffsetList.add("0x148");
        } else {
            for (int i = 3; i < args.length; i++) {
                for (String value : args[i].split(",")) trackedOffsetList.add(value);
            }
        }
        Set<Long> seeds = new LinkedHashSet<>();
        for (String line : Files.readAllLines(Paths.get(args[0]), StandardCharsets.UTF_8)) {
            Matcher matcher = OWNER.matcher(line);
            while (matcher.find()) seeds.add(Long.parseUnsignedLong(matcher.group(1), 16));
        }

        List<String> rows = new ArrayList<>();
        rows.add("owner,instruction_address,mnemonic,bytes,field_offsets,instruction_text");
        long visitedTotal = 0;
        int badSeeds = 0;
        for (long value : seeds) {
            Address seed = toAddr(value);
            MemoryBlock block = currentProgram.getMemory().getBlock(seed);
            if (block == null || !block.isExecute()) {
                badSeeds++;
                continue;
            }
            ArrayDeque<Address> queue = new ArrayDeque<>();
            Set<Address> visited = new HashSet<>();
            queue.add(seed);
            while (!queue.isEmpty() && visited.size() < cap) {
                Address at = queue.removeFirst();
                if (!visited.add(at)) continue;
                Instruction instruction = currentProgram.getListing().getInstructionAt(at);
                if (instruction == null) {
                    new DisassembleCommand(at, null, false).applyTo(currentProgram, monitor);
                    instruction = currentProgram.getListing().getInstructionAt(at);
                }
                if (instruction == null) continue;
                String text = instruction.toString();
                String normalized = text.toLowerCase(Locale.ROOT).replace(" ", "");
                List<String> offsets = new ArrayList<>();
                for (String rawOffset : trackedOffsetList) {
                    String offset = rawOffset.trim().toLowerCase(Locale.ROOT);
                    if (!offset.startsWith("0x")) offset = "0x" + offset;
                    String hex = offset.substring(2);
                    if (normalized.contains("+" + offset) || normalized.contains("+" + hex + "h")) {
                        offsets.add(offset);
                    }
                }
                if (!offsets.isEmpty()) {
                    rows.add(String.format(Locale.ROOT, "0x%08X,0x%08X,%s,%s,\"%s\",\"%s\"",
                        value, instruction.getAddress().getOffset(),
                        csv(instruction.getMnemonicString()),
                        bytes(instruction.getBytes()), String.join("|", offsets), csv(text)));
                }

                if (instruction.getFlowType().isJump()) {
                    for (Address dest : instruction.getFlows()) {
                        if (dest != null && block.contains(dest)) queue.addLast(dest);
                    }
                    if (instruction.getFlowType().isConditional()
                            && instruction.getFallThrough() != null
                            && block.contains(instruction.getFallThrough())) {
                        queue.addLast(instruction.getFallThrough());
                    }
                } else if (!instruction.getFlowType().isTerminal()
                        && instruction.getFallThrough() != null
                        && block.contains(instruction.getFallThrough())) {
                    queue.addLast(instruction.getFallThrough());
                }
            }
            visitedTotal += visited.size();
        }
        Files.write(Paths.get(args[1]), rows, StandardCharsets.UTF_8);
        println("owner_seeds=" + seeds.size() + " invalid_seeds=" + badSeeds
            + " bounded_instructions=" + visitedTotal + " field_hits=" + (rows.size() - 1));
        println("output=" + Paths.get(args[1]).toAbsolutePath());
        println("NOTE: bounded disassembly scan only; indirect dataflow and runtime callback values are not resolved.");
    }

    private String bytes(byte[] value) {
        StringBuilder output = new StringBuilder();
        for (byte b : value) output.append(String.format(Locale.ROOT, "%02X", b & 0xff));
        return output.toString();
    }

    private String csv(String value) {
        return value.replace("\"", "\"\"");
    }
}
