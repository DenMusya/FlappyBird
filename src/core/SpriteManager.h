#pragma once
#include <memory>
#include <string>
#include <unordered_map>

class SpriteManager {
 public:
  struct Image {
    uint32_t* data;
    int w;
    int h;
  };
  static SpriteManager& Get();

  Image Load(const char* pathToSprite);

  ~SpriteManager();

 private:
  std::unordered_map<const char*, Image> _sprites;

  static std::unique_ptr<SpriteManager> _instance;
};