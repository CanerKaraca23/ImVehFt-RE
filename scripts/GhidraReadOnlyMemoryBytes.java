// Read-only byte/value probe for addresses in the currently open Ghidra program.
// Args: output.csv and one or more addresses.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class GhidraReadOnlyMemoryBytes extends GhidraScript {
    @Override protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) throw new IllegalArgumentException("expected output.csv and addresses");
        List<String> rows = new ArrayList<>();
        rows.add("address,bytes_16,little_endian_u32,defined_data");
        for (int i = 1; i < args.length; i++) {
            Address address = toAddr(Long.decode(args[i]));
            byte[] bytes = new byte[16];
            int count = currentProgram.getMemory().getBytes(address, bytes);
            StringBuilder hex = new StringBuilder();
            for (int j = 0; j < count; j++) {
                if (j > 0) hex.append(' ');
                hex.append(String.format("%02X", bytes[j] & 0xff));
            }
            String value = count >= 4 ? String.format("0x%08X",
                Integer.toUnsignedLong(currentProgram.getMemory().getInt(address))) : "";
            String data = "";
            ghidra.program.model.listing.Data unit = currentProgram.getListing().getDataAt(address);
            if (unit != null) data = unit.getDataType().getName() + ":" + unit.toString();
            rows.add(address + ",\"" + hex + "\"," + value + ",\""
                + data.replace("\"", "'") + "\"");
        }
        Files.write(Paths.get(args[0]), rows, StandardCharsets.UTF_8);
        println("Wrote read-only memory bytes: " + args[0] + " (" + (rows.size() - 1) + " addresses)");
    }
}
