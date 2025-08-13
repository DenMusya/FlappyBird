#pragma once
#include <queue>

#include "../utils/Config.h"
#include "GameObject.h"

class Background : public GameObject {
 public:
  Background(const BackgroundConfig& config);
  void Update(float dt);

 private:
  const BackgroundConfig Config;
  Vector2 _spriteSize;
  std::queue<std::shared_ptr<GameObject>> _background;
};