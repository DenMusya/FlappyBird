#include <memory.h>
#include <stdlib.h>

#include <list>

#include "Bird.h"
#include "Engine.h"
#include "Pipe.h"
#include "PipeSpawner.h"
#include "Text.h"
#include "Timer.h"
#include "Utils.h"

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT,
//                                       VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 -
//  left button, 1 - right button) clear_buffer() - set all pixels in buffer to
//  'black' is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

// initialize game data in this function

std::list<std::unique_ptr<Pipe>> listPipes;

PipeSpawner pipeSpawner;

Bird bird;
Text scoreText;

Timer pipeTimer;

const float timeToNewPipe = 2.0f;
const float pipeSpeed = 500.0f;

int32_t score = 0;

void initialize() { scoreText = "Score: 0"; }

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt) {
  pipeTimer.AddTime(dt);

  if (!listPipes.empty() && listPipes.front()->Disappeared()) {
    listPipes.pop_front();
  }

  for (auto& pipe : listPipes) {
    pipe->move(Vector2{-1.0f, 0.0f} * dt * pipeSpeed);
    if (bird.IsFinished(*pipe)) {
      ++score;
      scoreText = "Score: " + std::to_string(score);
    }
    // score += bird.IsFinished(*pipe);
  }

  if (pipeTimer.ElapsedTime() >= timeToNewPipe) {
    pipeTimer.Reset();
    listPipes.push_back(pipeSpawner.SpawnPipe());
  }

  bird.update(dt);

  if (is_key_pressed(VK_SPACE)) {
    bird.Jump();
  }

  for (auto& pipe : listPipes) {
    if (bird.OnCollision(*pipe)) {
      EndWindow(score);
      schedule_quit_game();
    }
  }

  if (bird.OutMap()) {
    EndWindow(score);
    schedule_quit_game();
  }

  if (is_key_pressed(VK_ESCAPE)) schedule_quit_game();
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors
// (8 bits per R, G, B)
void draw() {
  FillBuffer(Color::Green);
  for (auto& pipe : listPipes) {
    pipe->draw();
  }
  bird.draw();
  scoreText.draw();
}

// free game data in this function
void finalize() {}
