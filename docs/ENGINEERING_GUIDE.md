# Arcade: understand the interface

The photograph shows a real powered prototype. The included paddle game is **new reference software**, not recovered code for the photographed graphics. Dynamic joystick-to-display operation has not been demonstrated.

## Explain the hardware honestly

| Element | Typical purpose | Evidence boundary |
| --- | --- | --- |
| LoLin ESP8266 board | Execute application logic and connect peripherals | Exact board revision and real pin map unconfirmed |
| Joystick | Provide position signals and a switch | The reference reads one analog axis only; no button adapter |
| 128×160-labelled TFT | Display graphics | Actual driver IC remains unverified |
| Breadboard/wires | Prototype connections | Wire colors are not a verified schematic |
| White enclosure/module | Visible part of the assembly | Function unknown; do not call it a battery by appearance |

A historical component-selection reason is not documented. The new reference uses an ESP8266 software target and Arduino APIs; it does **not** use Wi-Fi. Do not claim networking simply because the board supports it.

## Follow the actual source

| Source | Read these names | What to explain |
| --- | --- | --- |
| [config.h](../firmware/joystick_display/config.h) | `ENABLE_JOYSTICK_INPUT`, `ENABLE_TFT` | Why both physical adapters remain disabled |
| [game.h](../firmware/joystick_display/game.h) | `Game::input` | Clamp input to 0–1023, map it to a 0–100 paddle position |
| [game.h](../firmware/joystick_display/game.h) | `step`, `restart`, `resetBall` | Ball movement, boundary/paddle collision, score and lives |
| [joystick_display.ino](../firmware/joystick_display/joystick_display.ino) | `loop`, `lastStep`, `lastReport` | Bounded serial processing, nominal 20 ms steps and 500 ms reports |
| [test_core.cpp](../tests/test_core.cpp) | `CHECK` | Software bounds/collision/life/restart checks, not input-latency measurements |

## How one frame happens

Serial `a`/`d` changes a simulated input while the joystick adapter is disabled. `Game::input` sets paddle position. A due logic step moves the ball, checks collisions and updates score/lives. With a verified optional TFT adapter, the sketch redraws the screen. Space restarts the software game.

The one-axis choice avoids pretending the reference already reads both axes. Actual A0 limits and the development board's analog-input circuitry must be established before connecting hardware. The optional ST7735 black-tab renderer is a reference driver choice, not identification of the pictured screen.

## Build, do not confuse with a demo

```powershell
arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 firmware/joystick_display
```

Use the versions in [FIRMWARE.md](../FIRMWARE.md). Default and private adapter-only builds passed again on 16 October 2026. No board was flashed, no GPIO exercised and no display frame rate measured. Original standalone results are retained in [BUILD_STATUS.md](../BUILD_STATUS.md), not relabelled as a new execution.

## Practice before presenting

- Explain why a 28-pixel paddle on a 128-pixel screen has a maximum left position of 100, not 128.
- Trace the collision test at the paddle. Explain how the previous ball position helps detect a crossing.
- In a separate software-only branch, add an edge-collision test or change paddle width and update the expected mapping. Predict the result before running tests. Leave peripherals disabled.
- Explain why a nominal 20 ms step is not evidence of 50 measured display frames per second; redraw and stalls consume time.

Do not bypass an OS execution restriction. A compiled test and an executed test are different results.

## Diagnose instead of guessing

| Symptom | First investigation |
| --- | --- |
| Paddle does not follow physical stick | Default input is simulated; verify the actual board/input interface before enabling |
| Mirrored or limited motion | Log actual ADC endpoints and mapping; do not guess calibration |
| Blank or corrupted display | Confirm driver/profile, power/logic levels and traced SPI/reset connections |
| Flicker | Full-screen redraw is simple and unoptimized; measure behavior before proposing changes |
| Original screen differs from this game | Expected: the original matching sketch was not located |

Use the [real demonstration plan](DEMO_TEST_PLAN.md) to produce evidence of physical input and visible response. Be clear about which code you can explain and which implementation was newly assisted reference work.
