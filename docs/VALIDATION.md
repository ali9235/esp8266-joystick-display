# VOLTRA Arcade: testing and validation

## Scope and actual results

[Machine-readable software-check record](../tests/evidence/2026-10-16-software-checks.json) · This record contains actual software checks and explicit exclusions, not fabricated sensor data.

13 historical C++ checks cover input bounds, collisions, score/lives, game-over and restart. Two ESP8266 compiler configurations are separate from physical operation.

Default and private adapter-only sketches compiled successfully again on 16 October 2026. Fixture pins are compiler inputs, **not wiring recommendations**. Native C++ tests were not rerun in this documentation update; application-control restrictions were respected. Historical results remain in [BUILD_STATUS.md](../BUILD_STATUS.md).

## Reproduce software checks

```powershell
python tools/check_docs.py
arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 firmware/joystick_display
# With an approved native compiler/runtime:
g++ -std=c++17 -Wall -Wextra -Werror tests/test_core.cpp -o test_core.exe
.\test_core.exe
```

The documentation check needs only Python's standard library. Install dependencies from [FIRMWARE.md](../FIRMWARE.md). Compiling does not flash. If the OS blocks a native executable, record the blocker; do not rename, rebuild or move it to bypass policy.

## Error behavior to inspect

Test clamped input, collisions, life loss, stopped/game-over state and restart separately from physical display/input behavior.

## Hardware acceptance

No physical joystick response, TFT commissioning, measured FPS, two-axis input or wireless gameplay was demonstrated.

The [demo plan](DEMO_TEST_PLAN.md) defines proposed observations. [hardware-observations.csv](../tests/hardware-observations.csv) contains **not_run** rows, not measurements. Add raw values and genuine evidence only after testing.

## Continuous integration

The proposed workflow runs documentation checks and the portable C++ core on Ubuntu. It does not flash hardware or compile Arduino adapter branches, assess photo truth or establish safety. A workflow file is not a passing run; inspect Actions after an authorized push. No success badge is prefilled.

[Security](../SECURITY.md) · [Roadmap](ROADMAP.md)
