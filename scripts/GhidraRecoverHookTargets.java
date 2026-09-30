// Create and decompile only patch destinations not listed as one of the 705
// candidate function entries. Run on ImVehFt.asi with -noanalysis.
// Args: <candidate-source.cpp> <function-name-map.csv> <summary.csv> <decomp.txt>
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.mem.MemoryBlock;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class GhidraRecoverHookTargets extends GhidraScript {
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
        if (args.length != 4) {
            throw new IllegalArgumentException("expected source, function-map, summary.csv, and decomp.txt");
        }
        String source = Files.readString(Paths.get(args[0]), StandardCharsets.UTF_8);
        Set<Long> knownEntries = new LinkedHashSet<>();
        for (String line : Files.readAllLines(Paths.get(args[1]), StandardCharsets.UTF_8)) {
            String first = line.split(",", 2)[0].replace("\"", "").trim();
            if (first.matches("[0-9A-Fa-f]{8}")) knownEntries.add(Long.parseLong(first, 16));
        }

        Matcher opMatcher = OPCODE.matcher(source);
        List<int[]> ranges = new ArrayList<>();
        while (opMatcher.find()) ranges.add(new int[] { opMatcher.start(), opMatcher.end() });
        Map<Long, List<Hook>> hooksByTarget = new LinkedHashMap<>();
        for (int i = 0; i < ranges.size(); i++) {
            int start = ranges.get(i)[0];
            int end = i + 1 < ranges.size() ? ranges.get(i + 1)[0] : source.length();
            String block = source.substring(start, end);
            Matcher op = OPCODE.matcher(block);
            Matcher siteMatcher = SITE.matcher(block);
            Matcher dispMatcher = DISPLACEMENT.matcher(block);
            if (!op.find() || !siteMatcher.find() || !dispMatcher.find()) continue;
            long site = Long.decode(siteMatcher.group(1));
            if (Long.decode(dispMatcher.group(1)) != site + 1) continue;
            long displacement = Long.decode(dispMatcher.group(2));
            long target = (site + 5 + displacement) & 0xffffffffL;
            hooksByTarget.computeIfAbsent(target, k -> new ArrayList<>())
                .add(new Hook(site, target, op.group(1).toUpperCase()));
        }

        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        List<String> summary = new ArrayList<>();
        StringBuilder pseudocode = new StringBuilder();
        summary.add("target,hook_count,hook_sites,block,function_created,body_min,body_max,decompile_completed,error");
        int attempted = 0;
        int created = 0;
        int decompiled = 0;
        for (Map.Entry<Long, List<Hook>> entry : hooksByTarget.entrySet()) {
            long targetValue = entry.getKey();
            if (knownEntries.contains(targetValue)) continue;
            attempted++;
            Address target = toAddr(targetValue);
            MemoryBlock block = currentProgram.getMemory().getBlock(target);
            String blockName = block == null ? "NO_MEMORY_BLOCK" : block.getName();
            String hookSites = entry.getValue().stream()
                .map(h -> String.format("%s:%s", String.format("0x%08X", h.site), h.opcode))
                .reduce((a, b) -> a + " | " + b).orElse("");
            String status = "";
            Function function = currentProgram.getFunctionManager().getFunctionAt(target);
            try {
                if (function == null) function = createFunction(target, "HOOK_DEST_" + String.format("%08X", targetValue));
                if (function == null) throw new IllegalStateException("Ghidra did not create a function");
                created++;
                DecompileResults result = decompiler.decompileFunction(function, 30, monitor);
                boolean complete = result != null && result.decompileCompleted()
                    && result.getDecompiledFunction() != null;
                if (complete) {
                    decompiled++;
                    pseudocode.append("\n/* target ")
                        .append(String.format("0x%08X", targetValue))
                        .append("; hook sites ").append(hookSites).append(" */\n")
                        .append(result.getDecompiledFunction().getC()).append("\n");
                }
                status = complete ? "decompiled" : result == null ? "no result" : result.getErrorMessage();
                summary.add(String.format(
                    "0x%08X,%d,\"%s\",\"%s\",yes,%s,%s,%s,\"%s\"",
                    targetValue, entry.getValue().size(), hookSites.replace("\"", "\"\""),
                    blockName, function.getBody().getMinAddress(), function.getBody().getMaxAddress(),
                    complete ? "yes" : "no", status.replace("\"", "\"\"")
                ));
            } catch (Exception e) {
                status = e.toString();
                summary.add(String.format(
                    "0x%08X,%d,\"%s\",\"%s\",no,,,,\"%s\"",
                    targetValue, entry.getValue().size(), hookSites.replace("\"", "\"\""),
                    blockName, status.replace("\"", "\"\"")
                ));
            }
        }

        Files.write(Paths.get(args[2]), summary, StandardCharsets.UTF_8);
        Files.writeString(Paths.get(args[3]), pseudocode.toString(), StandardCharsets.UTF_8);
        println("hook_branches=" + hooksByTarget.values().stream().mapToInt(List::size).sum());
        println("unique_destinations=" + hooksByTarget.size());
        println("known_705_function_entries=" + knownEntries.size());
        println("unmapped_hook_destinations_attempted=" + attempted);
        println("functions_created=" + created);
        println("decompiled=" + decompiled);
        println("summary=" + Paths.get(args[2]).toAbsolutePath());
        println("pseudocode=" + Paths.get(args[3]).toAbsolutePath());
        println("NOTE: temporary function recovery is analysis evidence, not source recovery or runtime validation.");
        decompiler.dispose();
    }
}
