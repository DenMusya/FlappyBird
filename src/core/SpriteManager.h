#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../utils/Utils.h"

class SpriteManager {
 public:
  struct Image {
    uint32_t* data;
    int w;
    int h;

    std::vector<Vector2>* borders;
  };
  static SpriteManager& Get();

  Image Load(const char* pathToSprite);

  ~SpriteManager();

 private:
  std::unordered_map<const char*, Image> _sprites;

  static std::unique_ptr<SpriteManager> _instance;
};