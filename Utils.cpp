#include "Engine.h"
#include "Utils.h"
#include <windows.h>
#include <algorithm>
#include <string>

void ColorPixel(int32_t x, int32_t y, uint32_t color) {
  if (x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT) {
    buffer[y][x] = color;
  }
}

void FillBuffer(uint32_t color) {
  for (int i = 0; i < SCREEN_HEIGHT; ++i) {
    std::fill(std::begin(buffer[i]), std::end(buffer[i]), color);
  }
}

Vector2& Vector2::operator+=(const Vector2& v1) {
  x += v1.x;
  y += v1.y;
  return *this;
}

Vector2& Vector2::operator*=(float value) {
  x *= value;
  y *= value;
  return *this;
}

Vector2 operator+(const Vector2& v1, const Vector2& v2) {
  Vector2 copy = v1;
  return copy += v2;
}

Vector2 operator*(const Vector2& v1, float value) {
  Vector2 copy = v1;
  return copy *= value;
}

Vector2 operator*(float value, const Vector2& v1) {
  return v1 * value;
}

void EndWindow(int32_t score) {
  
}
