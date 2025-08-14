#include "RenderManager.h"

#include <windows.h>

#include <string>

std::vector<Sprite*> RenderManager::_sprites;

void RenderManager::RenderAll() {
  for (auto& sprite : _sprites) {
    if (sprite->IsActive()) {
      sprite->Draw();
    }
  }
}

void RenderManager::RegisterSprite(Sprite* sprite) {
  _sprites.push_back(sprite);
}

void RenderManager::UnregisterSprite(Sprite* sprite) {
  auto it = std::find(_sprites.begin(), _sprites.end(), sprite);
  if (it != _sprites.end()) {
    _sprites.erase(it);
  }
}