# New reference paddle-game firmware

A small playable **software reference implementation**, not the recovered game visible in the owner's photograph. It includes paddle movement, a bouncing ball, paddle collisions, score, three lives, game-over and restart. No physical display/input test is claimed.

[Arduino adapter](firmware/joystick_display/joystick_display.ino) · [Game core](firmware/joystick_display/game.h) · [Configuration](firmware/joystick_display/config.h) · [Core tests](tests/test_core.cpp)

## Build

Reference target: NodeMCU 1.0 / ESP8266, Arduino core **3.1.2**. This is a compiler target, not confirmation of the exact board revision in the photo.

```powershell
arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 firmware/joystick_display
```

Default mode enables no joystick GPIO or TFT. If flashed to a verified board later, use Serial Monitor at 115200 baud: `a`/`d` move a simulated paddle and space restarts. Serial output reports score/lives/paddle position. Game logic steps nominally every 20 ms without unbounded catch-up after a stall; this is not a measured display frame rate.

## Input and display choices

The **new reference uses one analog joystick axis**, not both axes. The ESP8266 has a single external ADC input; the bare-chip input range and a development board's A0 divider must not be confused. Identify the actual board's input limits before connecting a joystick. See the official [ESP8266 analog-input reference](https://arduino-esp8266.readthedocs.io/en/3.1.1/reference.html#analog-input).

The optional renderer targets an **ST7735 black-tab 128×160 reference module**, which is not confirmed as the controller in the photo. Dependencies for this adapter: Adafruit ST7735/ST7789 1.11.0, GFX 1.12.6 and BusIO 1.17.4. Driver selection, SPI/control/reset wiring, power levels and boot-pin constraints require verification. Full-screen redraw can flicker; no flicker-free or low-latency result is claimed. Restart uses serial input; a physical pushbutton adapter is not implemented.

## Test the portable game

```powershell
g++ -std=c++17 -Wall -Wextra -Werror tests/test_core.cpp -o test_core.exe
.\test_core.exe
```

Checks cover input bounds, collisions, score/life changes, game-over and restart. The code intentionally has no Wi-Fi, credentials, telemetry simulation presented as hardware data, or third-party game assets. See [the actual-hardware checklist](WIRING_AND_SOURCE.md).
