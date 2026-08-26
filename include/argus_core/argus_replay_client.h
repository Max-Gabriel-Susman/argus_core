/*
 * Transport-agnostic client for the Argus replay protocol.
 *
 * One implementation, two transports. The host test client wraps this in BSD
 * Socket; the Zynq PS wraps it in lwIP raw callbacks. Neither owns the protocol
 * logic, so a fix lands once.
 */

#ifndef ARGUS_REPLAY_CLIENT_H
    #define ARGUS_REPLAY_CLIENT_H

    #include <stdint.h>
    #include <stddef.h>
    #include <string.h>

    #include "argus_wire.h"

    /* Needs Impl */

#endif /* ARGUS_REPLAY_CLIENT_H */
