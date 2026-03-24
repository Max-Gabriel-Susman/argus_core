# Argus Core

Argus Core is the shared interface package for the Argus Cybernetics stack.

It exists to centralize common resources that need to be reused across packages, especially shared ROS 2 and micro-ROS interfaces such as message definitions, data layouts, and other core communication contracts. The goal is to make data exchange between embedded and host-side components more consistent, maintainable, and easier to evolve over time.

## Purpose

As the Argus system grows, multiple packages need to agree on how information is represented and exchanged. Rather than duplicating those definitions across packages, Argus Core provides a single place for shared types and interface definitions.

This package is intended to support communication between components such as:

- `argus_neural_interface_bridge`, which publishes neural data and listens for control commands on the bridge topics :contentReference[oaicite:0]{index=0}
- `argus_inference`, which consumes neural features, performs intent decoding, and publishes control output on `/cmd_vel` :contentReference[oaicite:1]{index=1}

## Responsibilities

Argus Core is intended to contain shared resources such as:

- custom ROS 2 message definitions
- common data structures for neural telemetry and replay frames
- shared interface contracts between embedded and host-side nodes
- reusable core types needed by multiple Argus packages

In general, if a type or interface is used by more than one package and represents part of the system’s common contract, it belongs in Argus Core.

## Why this package exists

The Argus project includes both embedded and host-side components. Those components need a reliable, well-defined way to exchange structured data.

For example, the current bridge application publishes neural data on `/argus/neural_interface_bridge/neural_data` and accepts commands on `/argus/neural_interface_bridge/control`, while the inference node builds features from neural input and maps decoded intent into motion commands. Centralizing shared message definitions in Argus Core helps keep those components aligned as the interface becomes more structured and moves beyond ad hoc string payloads. :contentReference[oaicite:2]{index=2} :contentReference[oaicite:3]{index=3}

## Design goals

Argus Core is designed to be:

- **Shared**: used by multiple packages across the Argus stack
- **Stable**: changes should be intentional, since interface changes affect downstream packages
- **Explicit**: message formats and shared types should be clear and semantically meaningful
- **Embedded-aware**: interfaces should be practical for micro-ROS and resource-constrained targets
- **Scalable**: the package should support future movement from simple proof-of-concept messages to richer structured telemetry

## Planned contents

Examples of items that may live in Argus Core include:

- `NeuralFrame`-style messages for structured neural replay data
- shared constants or conventions for channel layout and sample indexing
- future common interfaces used by bridge, inference, telemetry, or control packages

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

Argus Core is being introduced as part of the transition from simple proof-of-concept message passing toward more structured shared interfaces for the Argus Cybernetics system. The current surrounding stack already includes a neural bridge node and an inference node, and this package is intended to become the shared foundation between those components as the architecture matures. :contentReference[oaicite:4]{index=4} :contentReference[oaicite:5]{index=5}