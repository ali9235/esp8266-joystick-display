#pragma once
#include <stdint.h>

namespace pocket {
class Game {
 public:
  static const int width = 128, height = 160, paddleWidth = 28, paddleY = 145;
  float ballX = 64, ballY = 80, vx = 1.0f, vy = -1.5f;
  int paddleX = 50, score = 0, lives = 3;
  bool playing = false;
  void restart() { score = 0; lives = 3; playing = true; resetBall(); }
  void input(int adc) {
    if (adc < 0) adc = 0;
    if (adc > 1023) adc = 1023;
    paddleX = int(static_cast<long>(adc) * (width - paddleWidth) / 1023L);
  }
  void step() {
    if (!playing) return;
    const float previousY = ballY;
    ballX += vx; ballY += vy;
    if (ballX < 2) { ballX = 2; vx = -vx; }
    else if (ballX > width - 3) { ballX = width - 3; vx = -vx; }
    if (ballY < 14) { ballY = 14; vy = -vy; }
    if (vy > 0 && previousY + 2 <= paddleY && ballY + 2 >= paddleY &&
        ballX + 2 >= paddleX && ballX - 2 <= paddleX + paddleWidth) {
      ballY = paddleY - 3; vy = -vy; if (score < 9999) ++score;
    }
    if (ballY > height + 2) { --lives; if (lives <= 0) playing = false; resetBall(); }
  }
 private:
  void resetBall() { ballX = 64; ballY = 80; vx = 1; vy = -1.5f; }
};
}  // namespace pocket
