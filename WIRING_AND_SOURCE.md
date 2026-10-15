# Source and connection checklist

The photograph and owner confirm an independent physical project. Its original source was not located; [new reference firmware](FIRMWARE.md) is now provided at the owner's request. Confirm the display driver, board revision and actual electrical connections before using the optional hardware adapter.

| Signal group | Visible / known | Missing detail |
| --- | --- | --- |
| Joystick | Module labels include axes and switch | Connected GPIOs, analog-input arrangement, button handling |
| TFT | Module marked 1.8-inch 128×160 RGB | Controller, supply/logic requirements, actual clock/data/select/DC/reset pins |
| Power | USB cable visible at controller | Full supply/ground distribution and purpose of white module |
| Firmware behavior | Game-like screen photographed | Game rules, input mapping, original sketch and dependencies |

Do not infer connections from jumper colours or substitute the ESP32 robot joystick sketch. A pin map should come from the actual source checked against the physical build. A short recording of each input and its screen response would provide stronger evidence than a static screen alone.

## Connect the new reference implementation in stages

1. Identify the exact ESP8266 board and its A0 input limit. The bare chip and development-board analog front end are not interchangeable. Establish the joystick supply and maximum axis voltage before connecting its signal.
2. The new reference uses **one horizontal analog axis only**. Route the electrically compatible axis signal to A0 and provide the appropriate signal ground. The second axis and physical switch are not used by this implementation; restart is a serial command.
3. Read the TFT controller and module voltage specifications. The supplied adapter is ST7735 black-tab 128×160 only. A different controller requires a different driver rather than a guessed initialization profile.
4. Identify the selected board's hardware SPI clock/data signals, then trace display clock/data and any required chip-select, DC and reset connections. Enter actual control pins in `TFT_CS`, `TFT_DC`, `TFT_RST`. A negative reset pin is permitted only with a confirmed alternative reset arrangement. No display pin numbers are inferred from the photo.
5. Check that proposed pins do not overlap each other or needed serial signals and do not interfere with board boot requirements. Confirm power distribution, grounds and logic-level compatibility before connecting the display.
6. Compile and test the default serial-only configuration first. Enable `ENABLE_JOYSTICK_INPUT` and `ADC_INTERFACE_VERIFIED` only after verifying A0 compatibility. Enable the TFT/model/reset flags only after confirming the module and reset path.
7. With the new firmware deliberately flashed to a verified board, test serial `a`, `d` and space before physical inputs. Then verify the full left/right paddle range, collision scoring, three-life game-over and restart. Record actual refresh/flicker behavior; the software step interval is not a measured display rate.

The configuration intentionally provides **unset control pins**, not a ready-to-copy photograph wiring map. Keep a final pin table with source signal, MCU GPIO, destination pin, voltage domain and verification note beside the actual build.
