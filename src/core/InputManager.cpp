#include "InputManager.h"

#include "Engine.h"

std::unique_ptr<InputManager> InputManager::_instance;

InputManager& InputManager::Get() {
  if (!_instance) {
    _instance = std::make_unique<InputManager>();
  }
  return *_instance;
}

void InputManager::Update(float dt) {
  for (auto& [key, state] : _keys) {
    state.wasDown = state.isDown;
    state.isDown = is_key_pressed(key);

    state.cooldown -= dt;
  }
}

bool InputManager::IsKeyPressed(int key, float cooldownTime) {
  auto& state = _keys[key];

  if (state.isDown && !state.wasDown && state.cooldown <= 0) {
    state.cooldown = cooldownTime;
    return true;
  }
  return false;
}