#include "config.h"
#include "game.h"
#if ENABLE_TFT
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
Adafruit_ST7735 screen(TFT_CS, TFT_DC, TFT_RST);
#endif
pocket::Game game;
int simulatedAdc = 512;
uint32_t lastStep = 0, lastReport = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("NEW REFERENCE paddle game. Serial a/d=move, space=restart."));
  Serial.println(F("Uses one analog axis only; not a two-axis ADC implementation."));
#if ENABLE_TFT
  screen.initR(INITR_BLACKTAB); screen.setRotation(0); screen.fillScreen(ST77XX_BLACK);
#endif
  game.restart();
}

void loop() {
  const uint32_t now = millis();
  uint8_t commands = 0;
  while (Serial.available() && commands++ < 16) {
    const char c = char(Serial.read());
    if (c == ' ') game.restart();
#if !ENABLE_JOYSTICK_INPUT
    if (c == 'a') simulatedAdc = max(0, simulatedAdc - 64);
    if (c == 'd') simulatedAdc = min(1023, simulatedAdc + 64);
#endif
  }
#if ENABLE_JOYSTICK_INPUT
  game.input(analogRead(A0));
#else
  game.input(simulatedAdc);
#endif
  if (uint32_t(now - lastStep) >= 20UL) {
    lastStep = now; // No unbounded catch-up after a stall.
    game.step();
#if ENABLE_TFT
    screen.fillScreen(ST77XX_BLACK);
    screen.setCursor(0, 0); screen.setTextSize(1); screen.setTextColor(ST77XX_WHITE);
    screen.print("S:"); screen.print(game.score); screen.print(" L:"); screen.print(game.lives);
    screen.fillRect(game.paddleX, game.paddleY, game.paddleWidth, 4, ST77XX_GREEN);
    screen.fillCircle(int(game.ballX), int(game.ballY), 2, ST77XX_WHITE);
    if (!game.playing) { screen.setCursor(10, 65); screen.print("GAME OVER"); }
#endif
  }
  if (uint32_t(now - lastReport) >= 500UL) {
    lastReport = now; Serial.print(F("REFERENCE score=")); Serial.print(game.score);
    Serial.print(F(" lives=")); Serial.print(game.lives);
    Serial.print(F(" paddle=")); Serial.println(game.paddleX);
  }
  delay(1);
}
