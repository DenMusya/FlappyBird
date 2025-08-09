#pragma once
#include <vector>

#include "Sprite.h"

class RenderManager {
 public:
  static void RenderAll();
  static void RegisterSprite(Sprite* sprite);
  static void UnregisterSprite(Sprite* sprite);

 private:
  static std::vector<Sprite*> _sprites;
};
