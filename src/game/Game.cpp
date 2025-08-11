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

#include "../core/InputManager.h"
#include "../graphics/Color.h"
#include "../graphics/RenderManager.h"
#include "../graphics/Sprite.h"
#include "../physics/ColliderManager.h"
#include "../utils/Config.h"
#include "../utils/Timer.h"
#include "Bird.h"
#include "PipeSpawner.h"
#include "Text.h"

namespace {

struct GameState {
  std::shared_ptr<Bird> bird;
  std::shared_ptr<PipeSpawner> pipeSpawner;
  std::shared_ptr<Text> scoreText;

  uint32_t currentScore = 0;
};

GameState g_state;
}  // namespace

void initialize() {
  FillBufferGradient(Color(0xB6C02FFF), Color(0x5178ecFF));
  g_state.bird = GameObject::Create<Bird>(g_config.bird);
  g_state.pipeSpawner =
      GameObject::Create<PipeSpawner>(g_config.pipeSpawner, g_config.pipe);
  g_state.scoreText =
      GameObject::Create<Text>(g_config.scoreConfig, "Score: 0");
}

void HandleInput() {
  InputManager& input = InputManager::Get();

  if (input.IsKeyPressed(VK_ESCAPE)) {
    schedule_quit_game();
  }

  if (input.IsKeyPressed(VK_TAB, 0.2f)) freeze = !freeze;

  if (input.IsKeyPressed(VK_SPACE)) {
    g_state.bird->Jump();
  }
}

void act(float dt) {
  HandleInput();
  InputManager::Get().Update(dt);
  // if (is_key_pressed(VK_TAB)) freeze = !freeze;
  if (freeze) return;
  g_state.bird->Update(dt);
  g_state.pipeSpawner->Update(dt);
  for (auto& pipe : g_state.pipeSpawner->GetPipes()) {
    pipe->Update(dt);
    if (g_state.bird->IsFinished(*pipe) && !pipe->IsFinished()) {
      pipe->Finish();
      g_state.currentScore += 1;
      *(g_state.scoreText) = "Score: " + std::to_string(g_state.currentScore);
    }
  }

  // if (is_key_pressed(VK_SPACE)) g_state.bird->Jump();

  if (g_state.bird->OutMap()) schedule_quit_game();

  ColliderManager::UpdateColliders();
  ColliderManager::CheckCollisions();
}

void draw() {
  DrawBack();
  RenderManager::RenderAll();
  g_state.scoreText->Draw();
  // ColliderManager::DrawColliders();
}

void finalize() {}
