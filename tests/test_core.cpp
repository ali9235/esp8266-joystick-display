#include "../firmware/joystick_display/game.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
static int checks = 0;
#define CHECK(test) do { ++checks; if (!(test)) { std::cerr << "FAIL line " << __LINE__ << "\n"; std::exit(1); } } while (0)

int main() {
  pocket::Game g; CHECK(!g.playing); g.restart(); CHECK(g.playing); CHECK(g.lives == 3);
  g.input(-100); CHECK(g.paddleX == 0); g.input(2000); CHECK(g.paddleX == 100);
  g.input(512); CHECK(g.paddleX >= 49 && g.paddleX <= 51);
  g.ballX = 1; g.vx = -1; g.step(); CHECK(g.ballX >= 2 && g.vx > 0);
  g.ballY = 13; g.vy = -1; g.step(); CHECK(g.ballY >= 14 && g.vy > 0);
  g.ballX = float(g.paddleX + 10); g.ballY = 142; g.vy = 2;
  g.step(); CHECK(g.score == 1 && g.vy < 0);
  g.ballY = 163; g.vy = 2; g.step(); CHECK(g.lives == 2);
  g.ballY = 163; g.vy = 2; g.step(); g.ballY = 163; g.vy = 2; g.step();
  CHECK(!g.playing && g.lives == 0); g.step(); CHECK(g.lives == 0);
  g.restart(); CHECK(g.score == 0 && g.lives == 3 && g.playing);
  std::cout << "PASS: " << checks << " core checks; no physical hardware tested.\n";
}
