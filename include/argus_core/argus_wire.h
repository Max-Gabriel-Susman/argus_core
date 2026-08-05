#include "lwip/udp.h"
#include "lwip/init.h"
#include "netif/xadapter.h"

static struct udp_pcb *g_pcb;
static ip_addr_t g_dest;

// cyclic redundancy check
static uint16_t crc16_ccitt()
{
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < n; i++) {
        crc ^= (uint16_t)d[i] << 8;
        for (int b = 0; b < 8; b++) {
            crc = (crc & 0x8000) ? (crc << 1) ^ 0x1021 : (crc << 1);
        }
    }
    return crc;
}

int argus_net_init(void)
{
    // Create a protocol control block; a handle for a udp endpoint.
    g_pcb = udp_new(); 
    if (!g_pcb) {
        return -1;
    }
    IP4_ADDR(&g_dest, 192, 168, 1, 20); /* Orin */
    return 0;
}

int argus_send_frame(uint32_t sample, float t, const uint16_t *ch)
{
    argus_frame_packet_t pkt = {0};
    pkt.magic = ARGUS_FRAME_MAGIC;
    pkt.sample = sample;
    pkt.t = t;
    pkt.version = ARGUS_FRAME_VERSION;
    pkt.channel_count = ARGUS_MAX_CHANNELS;
    memcpy(pkt.channels, ch, sizeof(pkt.channels));
    pkt.crc = crc16_ccitt((const uint8_t *)&pkt, offsetof(argus_frame_packet_t, crc));
    // not finished yet.
}