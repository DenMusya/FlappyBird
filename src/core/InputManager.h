#pragma once
#include <memory>
#include <unordered_map>

class InputManager {
 public:
  static InputManager& Get();

  void Update(float dt);

  bool IsKeyPressed(int key, float cooldownTime = 0.0f);

  InputManager() = default;

 private:
  static std::unique_ptr<InputManager> _instance;

  struct KeyState {
    bool isDown = false;
    bool wasDown = false;
    float cooldown = 0.0f;
  };

  std::unordered_map<int, KeyState> _keys;

  InputManager(const InputManager&) = delete;
  InputManager& operator=(const InputManager&) = delete;
};