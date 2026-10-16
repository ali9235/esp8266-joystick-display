# VOLTRA Arcade: engineering decisions

These explain the **current inspectable design/documentation**, not why the owner originally bought components. Original selection history and personal debugging experiences have not been supplied.

| Decision | Current-file rationale | Alternative / trade-off | Constraint |
| --- | --- | --- | --- |
| Portable game core | Exercise state and collision rules without ADC/display hardware. | An all-in-one sketch is simpler to start but harder to isolate. | Logical checks do not measure responsiveness. |
| One analog axis | Use the single external ESP8266 ADC path for a paddle. | Two-axis control needs another input strategy/external ADC. | Confirm the exact board's A0 limits. |
| Bounded update scheduling | Avoid a burst of catch-up work after a stall. | Time-integrated simulation needs different collision tests. | Frame time, flicker and latency remain unmeasured. |

## Challenges: distinguish observed from suggested

The tests and configuration guards establish specific reference-software behavior, not proof that those failures occurred on the owner's prototype. The original matching sketch was not recovered.

No physical joystick response, TFT commissioning, measured FPS, two-axis input or wireless gameplay was demonstrated.

Troubleshooting suggestions are hypotheses, not incidents already solved. Add a case study only with the observed symptom, reproducible conditions, evidence for the cause, exact change, before/after test and remaining uncertainty. Do not turn design intentions into measured improvements.

[Architecture](ARCHITECTURE.md) · [Validation record](VALIDATION.md)
