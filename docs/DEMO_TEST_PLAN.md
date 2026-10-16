# Arcade: prove input-to-display behavior

**Status: planned, not performed.** Existing animation is an illustration, not this test.

## Before powering or flashing

Identify the board revision, joystick interface and TFT controller. Trace actual power, analog, SPI, control and reset connections using [WIRING_AND_SOURCE.md](../WIRING_AND_SOURCE.md). Verify voltage limits from the exact hardware documentation. Do not infer pins from wire colors or copy compiler fixtures. Change wiring only with power disconnected.

Default reference adapters remain disabled. Compiling does not authorize flashing or establish electrical compatibility.

## Record 45–75 seconds

1. Show the real assembly, board/display markings and code revision.
2. Keep hand movement and screen visible together. Move left, center and right, then release. State whether control is physical joystick or serial simulation.
3. Demonstrate one genuine game event and restart, using only controls actually implemented by the program being shown.
4. Explain one known limit: one-axis reference, unimplemented button handling, or redraw behavior. Do not present a simulated paddle as tested joystick control.

## Repeatable bench cases

| ID | Condition | Record | Acceptance basis |
| --- | --- | --- | --- |
| A1 | Left/center/right | Actual raw input, mapped paddle value and visible response | Compare against measured endpoints and documented mapping |
| A2 | Repeated movement | Several matching input/output observations | No inferred input latency from ordinary video; define a measurement method first |
| A3 | Game events | Collision, missed ball, life count and restart | Match the exact code revision, not another photographed game |
| A4 | Stable display run | Duration, supply, visible redraw faults and resets | Choose duration/acceptable faults before testing; no universal frame-rate claim |

Record results in [hardware-observations.csv](../tests/hardware-observations.csv). Rows are `not_run` until actual observations exist. Include failures and the reference/configuration used.

## Questions to answer without memorizing a script

Why one analog axis? What does the clamp prevent? Where does a life decrement? What makes a frame due? Why can a correctly compiled driver still fail on the wrong TFT? An honest explanation should point to source functions and the actual circuit, not the appearance of the README.
