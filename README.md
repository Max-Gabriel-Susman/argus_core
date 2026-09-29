# Argus Core

Argus Core is the shared interface package for the Argus Cybernetics stack.

The whole stack, and the one command that runs it on the board, is described in
[argus_bringup/README.md](https://github.com/Max-Gabriel-Susman/argus_bringup/blob/main/README.md).
Build and test this package from `~/Documents/argus_ws` with
`colcon build --packages-select argus_core && colcon test --packages-select argus_core`.
It changes the wire, so after a change rebuild every package that depends on it.

It exists to centralize common resources that need to be reused across packages, especially shared ROS 2 and micro-ROS interfaces such as message definitions, data layouts, and other core communication contracts. The goal is to make data exchange between embedded and host-side components more consistent, maintainable, and easier to evolve over time.

## Purpose

As the Argus system grows, multiple packages need to agree on how information is represented and exchanged. Rather than duplicating those definitions across packages, Argus Core provides a single place for shared types and interface definitions.

This package is intended to support communication between components such as:

- the Cortex-A9 firmware in `argus_safety_controller`, which sends feature frames over UDP (it vendors `argus_wire.h` byte-identical)
- `argus_sensors`' `neural_udp_receiver`, which parses those frames into `NeuralFrame` on `/argus/neural_interface_bridge/neural_data`
- `argus_sim`'s `dataset_relay_node`, which serves replay chunks to the firmware (the replay half of `argus_wire.h`)
- `argus_inference`, which consumes neural features, performs intent decoding, and publishes control output on `/cmd_vel`

## Responsibilities

Argus Core is intended to contain shared resources such as:

- custom ROS 2 message definitions
- common data structures for neural telemetry and replay frames
- shared interface contracts between embedded and host-side nodes
- reusable core types needed by multiple Argus packages

In general, if a type or interface is used by more than one package and represents part of the system’s common contract, it belongs in Argus Core.

## Why this package exists

The Argus project includes both embedded and host-side components. Those components need a reliable, well-defined way to exchange structured data.

For example, `neural_udp_receiver` publishes `NeuralFrame` on `/argus/neural_interface_bridge/neural_data`, and the inference node builds features from each frame and maps decoded intent into motion commands. Centralizing the wire format and the message in Argus Core keeps those components aligned.

## Design goals

Argus Core is designed to be:

- **Shared**: used by multiple packages across the Argus stack
- **Stable**: changes should be intentional, since interface changes affect downstream packages
- **Explicit**: message formats and shared types should be clear and semantically meaningful
- **Embedded-aware**: interfaces should be practical for micro-ROS and resource-constrained targets
- **Scalable**: the package should support future movement from simple proof-of-concept messages to richer structured telemetry

## Contents

- `msg/NeuralFrame.msg`: `sample`, `t`, `channel_count`, `uint16[96] channels`
  (threshold crossings per 50 ms bin) and `uint32[96] power` (spike-band
  mean-square per bin)
- `include/argus_core/argus_wire.h`: the UDP telemetry frame at
  `ARGUS_FRAME_VERSION 3` (594 bytes, magic `ARGS`, table-driven CRC-16/CCITT),
  and the replay request/chunk protocol on port 5010
- `include/argus_core/argus_replay_client.h`: the transport-agnostic replay client, shared by the firmware and the host test client

## Scope

Argus Core should contain **shared definitions**, not package-specific application logic.

Good fits for this package:
- message definitions
- shared interface contracts
- common core types

Poor fits for this package:
- node-specific runtime logic
- hardware-specific drivers
- model training code
- package-specific control flow

## Relationship to the rest of Argus

Argus Core sits at the boundary between packages that need to communicate with one another. It helps define the “language” spoken between embedded producers, inference components, and downstream consumers.

By keeping those shared definitions in one place, Argus Core reduces duplication and makes it easier to update the system architecture over time without scattering interface changes across the repository.

## Status

Argus Core is the shared foundation of the running stack. Frame version 3 (counts and power) is what the firmware sends on the board as of 2026-09-28.