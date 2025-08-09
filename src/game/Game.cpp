#include <memory.h>
#include <stdlib.h>

#include "../core/Engine.h"
#include "../graphics/Visuals.h"
#include "GameObject.h"
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
#include <windows.h>

#include <numbers>
#include <queue>
#include <string>

#include "../graphics/RenderManager.h"
#include "../graphics/Sprite.h"
#include "../physics/ColliderManager.h"
#include "../utils/Timer.h"
#include "Bird.h"
#include "PipeSpawner.h"

// void DebugLog(const std::string& message) {
//   OutputDebugStringA(message.c_str());
//   OutputDebugStringA("\n");  // перенос строки
// }

std::shared_ptr<Bird> bird;

std::shared_ptr<PipeSpawner> pipeSpawner;
std::vector<std::shared_ptr<Pipe>> pipes;
std::shared_ptr<Pipe> pipe;
Timer timer;

// initialize game data in this function
void initialize() {
  bird = GameObject::Create<Bird>(Vector2{64, 64}, Vector2::Zero);
  bird->Scale(1.5f);
  bird->SetPosition(Vector2{SCREEN_WIDTH, SCREEN_HEIGHT} * 0.5f,
                    PivotType::Center);

  pipeSpawner = GameObject::Create<PipeSpawner>();
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)

void act(float dt) {
  if (freeze) return;
  bird->Rotate(dt);
  timer.AddTime(dt);
  bird->Update(dt);
  for (auto& pipe : pipes) {
    pipe->Update(dt);
  }

  if (timer.ElapsedTime() > pipeSpawner->TimeToNewPipe) {
    timer.Reset();
    pipes.push_back(pipeSpawner->SpawnPipe());

    // DebugLog(std::to_string(pipes.size()));
  }

  if (!pipes.empty() && pipes.front()->Disappeared()) {
    pipes.erase(pipes.begin());
  }

  if (is_key_pressed(VK_SPACE)) bird->Jump();

  if (is_key_pressed(VK_ESCAPE) || bird->OutMap()) schedule_quit_game();

  ColliderManager::UpdateColliders();
  ColliderManager::CheckCollisions();
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors
// (8 bits per R, G, B)
void draw() {
  FillBuffer(0xFF0000);
  RenderManager::RenderAll();
  ColliderManager::DrawColliders();
}

// free game data in this function
void finalize() {}
