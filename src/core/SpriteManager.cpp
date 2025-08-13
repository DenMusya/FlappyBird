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

    Image image;

    image.borders = new std::vector<Vector2>[h];
    uint32_t* pixels = new uint32_t[w * h];

    for (int y = 0; y < h; ++y) {
      int segStart = -1;
      for (int x = 0; x < w; ++x) {
        int pos = (x + y * w) * 4;
        uint8_t r = data[pos];
        uint8_t g = data[pos + 1];
        uint8_t b = data[pos + 2];
        uint8_t a = data[pos + 3];

        pixels[pos / 4] = (a << 24) | (r << 16) | (g << 8) | b;

        if (a > 0) {
          if (segStart == -1) segStart = x;
        } else {
          if (segStart != -1) {
            image.borders[y].push_back(Vector2{float(segStart), float(x)});
            segStart = -1;
          }
        }
      }
      if (segStart != -1) {
        image.borders[y].push_back({float(segStart), float(w)});
      }
    }

    image.data = pixels;
    image.h = h;
    image.w = w;
    _sprites[pathToSprite] = image;

    stbi_image_free(data);
  }
  return _sprites[pathToSprite];
}

SpriteManager::~SpriteManager() {
  for (auto& [key, image] : _sprites) {
    delete[] image.data;
    delete[] image.borders;
  }
}