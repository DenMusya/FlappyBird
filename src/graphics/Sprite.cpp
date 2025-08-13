#include "Sprite.h"

#include <cassert>

#include "../core/Engine.h"
#include "../core/SpriteManager.h"
#include "../game/GameObject.h"
#include "Color.h"
#include "RenderManager.h"

Sprite::Sprite(const std::string& path) {
  SpriteManager::Image data = SpriteManager::Get().Load(path.c_str());

  _size = Vector2u{uint32_t(data.w), uint32_t(data.h)};
  _sprite = data.data;
  _borders = data.borders;
}

Vector2u Sprite::GetSize() const { return _size; }

void Sprite::Draw() {
  Transform transform = GetOwner()->GetGlobalTransform();

  if (transform.angle == 0 && transform.scale.x == 1 &&
      transform.scale.y == 1) {
    FastDraw();
    return;
  }
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

      if (x0 >= 0 && y0 >= 0 && x1 <= width && y1 <= height) {
        Color c00 = GetColor(x0, y0);
        Color c01 = GetColor(x0, y1);
        Color c10 = GetColor(x1, y0);
        Color c11 = GetColor(x1, y1);

        Color newColor;
        // »нтерпол€ци€
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
          ColorPixel(roundf(pos.x + x), roundf(y + pos.y), newColor.GetARGB());
        }
      }
    }
  }
}

void Sprite::FastDraw() {
  Vector2 pos = GetOwner()->GetGlobalTransform().position;
  int startX = std::max(pos.x, 0.0f);
  int startY = std::max(pos.y, 0.0f);
  int endX = std::min(pos.x + _size.x, float(SCREEN_WIDTH));
  int endY = std::min(pos.y + _size.y, float(SCREEN_HEIGHT));
  if (startX >= endX || startY >= endY) return;

  for (int y = startY; y < endY; ++y) {
    int srcY = y - pos.y;
    for (int i = 0; i < _borders[srcY].size(); ++i) {
      startX = std::max(pos.x + _borders[srcY][i].x, 0.0f);
      endX = std::min(pos.x + _borders[srcY][i].y, float(SCREEN_WIDTH));
      if (startX >= endX) continue;

      int copyWidth = endX - startX;
      int srcX = startX - pos.x;

      uint32_t* dest = buffer[y] + startX;
      uint32_t* src = _sprite + (srcY * _size.x + srcX);

      memcpy(dest, src, copyWidth * sizeof(uint32_t));
    }
  }
}

Color Sprite::GetColor(int x, int y) {
  if (x >= _size.x || y >= _size.y) {
    return Color();
  }
  return Color(_sprite[x + y * _size.x], ColorFormat::ARGB);
}

void Sprite::Init() { RenderManager::RegisterSprite(this); }

Sprite::~Sprite() { RenderManager::UnregisterSprite(this); }