#include "Sprite.h"

#include <cassert>

#include "../core/Engine.h"
#include "../game/GameObject.h"
#include "RenderManager.h"

Sprite::Sprite(Vector2u size, const uint32_t* sprite)
    : _size(size), _sprite(sprite) {}
#include "Color.h"

void Sprite::Draw() {
  Transform transform = GetOwner()->GetGlobalTransform();

  Vector2 center = 0.5 * Vector2{_size};
  Vector2 pos = transform.position;
  Vector2 scale = transform.scale;
  float angle = transform.angle;

  float cosA = cosf(angle);
  float sinA = sinf(angle);
  float centerX = center.x;
  float centerY = center.y;
  int width = _size.x;
  int height = _size.y;

  int drawWidth = static_cast<int>(width * scale.x);
  int drawHeight = static_cast<int>(height * scale.y);

  for (int y = 0; y < drawHeight; ++y) {
    if (roundf(y + pos.y) > SCREEN_HEIGHT || roundf(y + pos.y) < 0) {
      continue;
    }
    for (int x = 0; x < drawWidth; ++x) {
      float rotX = (x / scale.x - centerX) * cosA -
                   (y / scale.y - centerY) * sinA + centerX;
      float rotY = (x / scale.x - centerX) * sinA +
                   (y / scale.y - centerY) * cosA + centerY;

      int x0 = static_cast<int>(rotX);
      int y0 = static_cast<int>(rotY);
      int x1 = x0 + 1;
      int y1 = y0 + 1;
      float dx = rotX - x0;
      float dy = rotY - y0;

      // Проверка границ
      if (x0 >= 0 && y0 >= 0 && x1 <= width && y1 <= height) {
        // Извлекаем цвета (RGB)
        Color c00 = _sprite[y0 * width + x0];
        Color c01 = _sprite[y1 * width + x0];
        Color c10 = _sprite[y0 * width + x1];
        Color c11 = _sprite[y1 * width + x1];

        Color newColor;
        // Интерполяция
        newColor.r = static_cast<uint8_t>(
            (1 - dx) * (1 - dy) * c00.r + dx * (1 - dy) * c10.r +
            (1 - dx) * dy * c01.r + dx * dy * c11.r);

        newColor.g = static_cast<uint8_t>(
            (1 - dx) * (1 - dy) * c00.g + dx * (1 - dy) * c10.g +
            (1 - dx) * dy * c01.g + dx * dy * c11.g);

        newColor.b = static_cast<uint8_t>(
            (1 - dx) * (1 - dy) * c00.b + dx * (1 - dy) * c10.b +
            (1 - dx) * dy * c01.b + dx * dy * c11.b);

        newColor.a = static_cast<uint8_t>(
            (1 - dx) * (1 - dy) * c00.a + dx * (1 - dy) * c10.a +
            (1 - dx) * dy * c01.a + dx * dy * c11.a);

        if (!newColor.IsTransparent()) {
          ColorPixel(roundf(pos.x + x), roundf(y + pos.y), newColor.GetRGB());
        }
      }
    }
  }
}

Sprite::~Sprite() { RenderManager::UnregisterSprite(this); }

void Sprite::Init() { RenderManager::RegisterSprite(this); }