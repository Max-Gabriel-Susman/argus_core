#include <cstddef>
#include <tuple>
#include <gtest/gtest.h>

#include "argus_core/argus_wire.h"
#include "argus_core/msg/neural_frame.hpp"

/* Nothing enforces that NeuralFrame.msg and argus_wire.h describe the same
 * payload. This is the check that fires when ARGUS_MAX_CHANNELS moves. */
static_assert(
  std::tuple_size<decltype(argus_core::msg::NeuralFrame::channels)>::value ==
  ARGUS_MAX_CHANNELS, "NeuralFrame.msg channel array disagrees with ARGUS_MAX_CHANNELS"
);

TEST(WireContract, FrameFieldOffsets)
{
  EXPECT_EQ(offsetof(argus_frame_packet_t, magic), 0u);
  EXPECT_EQ(offsetof(argus_frame_packet_t, sample), 4u);
  EXPECT_EQ(offsetof(argus_frame_packet_t, t), 8u);
  EXPECT_EQ(offsetof(argus_frame_packet_t, version), 12u);
  EXPECT_EQ(offsetof(argus_frame_packet_t, channel_count), 14u);
  EXPECT_EQ(offsetof(argus_frame_packet_t, channels), 16u);
  EXPECT_EQ(offsetof(argus_frame_packet_t, crc), 208u);
}

TEST(WireContract, Crc16CcittFalse)
{
  const uint8_t check[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
  EXPECT_EQ(crc16_ccitt(check, sizeof(check)), 0x29B1u);
}

TEST(WireContract, IncrementalCrcMatchesOneShot)
{
  /* The replay path CRCs a header and a non-contiguous payload.
   * If these two ever diverge the PS silently drops every chunk. */
  const uint8_t check[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
  uint16_t crc = 0xFFFF;
  crc = crc16_ccitt_update(crc, check, 4);
  crc = crc16_ccitt_update(crc, check + 4, 5);
  EXPECT_EQ(crc, crc16_ccitt(check, sizeof(check)));
}

TEST(WireContract, ReplayChunkFitsInOneDatagram)
{
  const size_t payload = ARGUS_REPLAY_SAMPLES_PER_CHUNK * ARGUS_MAX_CHANNELS * sizeof(uint16_t);
  EXPECT_LE(payload, static_cast<size_t>(ARGUS_REPLAY_MAX_PAYLOAD));
  EXPECT_LE(sizeof(argus_replay_chunk_hdr_t) + payload, 1472u);   /* 1500-20-8 */
}
