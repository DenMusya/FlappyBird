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
#include "Background.h"
#include "Bird.h"
#include "PipeSpawner.h"
#include "Text.h"

namespace {

struct GameState {
  std::shared_ptr<Background> background;
  std::shared_ptr<Bird> bird;
  std::shared_ptr<PipeSpawner> pipeSpawner;
  std::shared_ptr<Text> scoreText;
  std::shared_ptr<Text> fpsText;
  std::shared_ptr<Text> settingsText;

  uint32_t currentScore = 0;
};

GameState g_state;
}  // namespace

void ResetGame() {
  g_state.bird->Reset();
  g_state.pipeSpawner->ClearPipes();
  g_state.currentScore = 0;
  (*g_state.scoreText) = "Score: 0";
  freeze = true;
}

void initialize() {
  g_state.background = GameObject::Create<Background>(g_config.background);
  g_state.bird = GameObject::Create<Bird>(g_config.bird);
  g_state.pipeSpawner =
      GameObject::Create<PipeSpawner>(g_config.pipeSpawner, g_config.pipe);
  g_state.scoreText = GameObject::Create<Text>(g_config.text, "Score: 0");
  g_state.fpsText = GameObject::Create<Text>(g_config.text, "");
  g_state.settingsText = GameObject::Create<Text>(
      g_config.text, "Space: Jump\nTab: pause\nShift: restart game\n");

  g_state.settingsText->Scale(0.5);
  g_state.settingsText->SetPosition(
      Vector2{SCREEN_WIDTH - 165, SCREEN_HEIGHT - 50});

  g_state.scoreText->SetPosition(Vector2{2, 2});
  g_state.fpsText->SetPosition(Vector2{2, SCREEN_HEIGHT - 23});
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

  if (input.IsKeyPressed(VK_SHIFT)) {
    ResetGame();
  }
}

void UpdateScore() {
  g_state.currentScore += 1;
  *(g_state.scoreText) = "Score: " + std::to_string(g_state.currentScore);
}

void ProcessPipes() {
  for (auto& pipe : g_state.pipeSpawner->GetPipes()) {
    if (g_state.bird->IsFinished(*pipe) && !pipe->IsFinished()) {
      pipe->Finish();
      UpdateScore();
    }
  }
}

Timer timer;
float timeFps = 0.25f;

void UpdateGameState(float dt) {
  InputManager::Get().Update(dt);
  timer.AddTime(dt);
  if (timer.ElapsedTime() > timeFps) {
    timer.Reset();
    (*g_state.fpsText) = "FPS: " + std::to_string(int(1 / dt));
  }

  if (freeze) return;
  g_state.bird->Update(dt);
  if (g_state.bird->IsDead()) return;
  g_state.background->Update(dt);
  g_state.pipeSpawner->Update(dt);

  if (g_state.bird->OutMap()) {
    g_state.bird->OnDead();
  }

  for (auto& pipe : g_state.pipeSpawner->GetPipes()) {
    pipe->Update(dt);
  }
}

void UpdateCollisions() {
  if (g_state.bird->IsDead()) return;
  ColliderManager::UpdateColliders();
  ColliderManager::CheckCollisions();
}

void act(float dt) {
  HandleInput();
  UpdateGameState(dt);
  ProcessPipes();
  UpdateCollisions();
}

void draw() {
  RenderManager::RenderAll();
  g_state.scoreText->Draw();
  g_state.fpsText->Draw();
  g_state.settingsText->Draw();
  // ColliderManager::DrawColliders();
}

void finalize() {}
