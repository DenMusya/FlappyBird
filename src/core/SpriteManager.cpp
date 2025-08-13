#define STB_IMAGE_IMPLEMENTATION
#include "SpriteManager.h"

#include "stb_image.h"

std::unique_ptr<SpriteManager> SpriteManager::_instance;

SpriteManager& SpriteManager::Get() {
  if (!_instance) {
    _instance = std::make_unique<SpriteManager>();
  }
  return *_instance;
}

SpriteManager::Image SpriteManager::Load(const char* pathToSprite) {
  if (!_sprites.contains(pathToSprite)) {
    int w, h;
    unsigned char* data =
        stbi_load(pathToSprite, &w, &h, nullptr, STBI_rgb_alpha);

    uint32_t* pixels = new uint32_t[w * h];

    for (int y = 0; y < h; ++y) {
      for (int x = 0; x < w; ++x) {
        int pos = (x + y * w) * 4;
        uint8_t r = data[pos];
        uint8_t g = data[pos + 1];
        uint8_t b = data[pos + 2];
        uint8_t a = data[pos + 3];

        pixels[pos / 4] = (a << 24) | (r << 16) | (g << 8) | b;
      }
    }
    _sprites[pathToSprite] = Image{pixels, w, h};

    stbi_image_free(data);
  }
  return _sprites[pathToSprite];
}

SpriteManager::~SpriteManager() {
  for (auto& [key, image] : _sprites) {
    delete[] image.data;
  }
}