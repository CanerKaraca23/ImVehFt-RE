/* Forced-include experiment only: place subsequent compiled functions in a
 * separate executable section so fixed-address entry stubs can stay in .text.
 */
#pragma code_seg(".xcode")
