/*
 * Linker-only probe: test whether fixed-size original-image reservations can
 * retain legacy section RVAs while candidate code is emitted in a later custom
 * executable section. This is not an ImVehFt build or loadable ASI.
 */
#if defined(PROBE_ORIGINAL_DATA)
#pragma section(".data$A", read, write)
extern "C" {
__declspec(allocate(".data$A")) extern unsigned char
    ivf_original_data_reservation[0x1455C] = {0x22};
}
#else
#pragma section(".xcode", execute, read)
#pragma code_seg(".xcode")
extern "C" int ivf_layout_probe_candidate(void) {
    return 0x705;
}
#endif
