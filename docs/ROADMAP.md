# VOLTRA Arcade: development roadmap

Status at documentation preparation, 16 October 2026. Future items are not completed features, deadlines or a claim that a hardware campaign is underway.

## Completed and inspectable

- Real prototype photographs and explicit evidence boundaries.
- New reference firmware, portable core tests, hardware-disabled defaults and compiler evidence.
- Source-grounded explanations and a genuine-media/evidence record.

## Prepared for review

The VOLTRA Engineering Standard documentation, local checks and proposed CI configuration are prepared together. No semantic tag, GitHub Release or passing Actions run is implied. See [release management](RELEASING.md).

## Next, in dependency order

1. Identify TFT driver and exact board revision; trace power/signals.
2. Record raw joystick ADC endpoints and neutral-position values.
3. Film actual restart, collisions, misses and game-over on the verified assembly.
4. Measure input-to-display latency and redraw flicker before optimization.

## Acceptance gates

Hardware milestones need identified parts, a recorded revision, traced wiring, raw observations with units and genuine footage. Report failures alongside successes. Accuracy, power, latency and endurance stay unmeasured until supported by a real record.

No physical joystick response, TFT commissioning, measured FPS, two-axis input or wireless gameplay was demonstrated.

[Validation](VALIDATION.md) · [Changelog](../CHANGELOG.md)
