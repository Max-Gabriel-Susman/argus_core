/* argus_core installs argus_wire.h but never compiles it. The safety
 * controller consumesit as C, so a C++ only test would miss C regressions
 * (static_assert is an assert.h macro pre-C23 and needs C11 minimum). */
 #include "argus_core/argus_wire.h"

const size_t argus_wire_c_check_frame_size = sizeof(argus_frame_packet_t);
