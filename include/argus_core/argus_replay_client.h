/*
 * Transport-agnostic client for the Argus replay protocol.
 *
 * One implementation, two transports. The host test client wraps this in BSD
 * Socket; the Zynq PS wraps it in lwIP raw callbacks. Neither owns the protocol
 * logic, so a fix lands once.
 *
 * Constraints, driven by the bare-metal side:
 *  - C99, no allocation, no stdio, no threads, no exceptions.
 *  - Caller owns every buffer. This struct stores pointers, never memory.
 *  - Transport is injected as a send callback plus a receive entry point,
 *    so it works with a blocking read loop or an interrupt callback.
 *  - Time is supplied by the caller, so it works off a systick or a clock_gettime.
 *
 */

#ifndef ARGUS_REPLAY_CLIENT_H
    #define ARGUS_REPLAY_CLIENT_H

    #include <stdint.h>
    #include <stddef.h>
    #include <string.h>

    #include "argus_wire.h"

    /* A burst is bounded by SAMPLES_PER_HALF divided by the smallest chunk that
     * fits an MTU. At 124 channels that is 5 samples per chunk, so 30 chunks. 32
     * gives headroom and lets the arrivval set be one uint32_t. */
    #define ARGUS_REPLAY_MAX_CHUNKS 32u

    /* Needs Impl */

#endif /* ARGUS_REPLAY_CLIENT_H */
