
#include <windows.h>

#undef max
#undef min

#include <algorithm>
#include <numbers>
#include <random>
#include <string>

#include "../core/Engine.h"
#include "../graphics/Color.h"
#include "Utils.h"

void DebugLog(const std::string& message) {
  OutputDebugStringA(message.c_str());
  OutputDebugStringA("\n");
}

float ToRadians(float degree) { return std::numbers::pi * degree / 180.0f; }

bool freeze = false;
void FreezeGame() { freeze = true; }

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

float RandomFloat(float x, float y) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(x, y);

  return dis(gen);
}

uint8_t Lerp(uint8_t a, uint8_t b, float t) { return a + t * (b - a); }

Vector2::Vector2(float x, float y) : x(x), y(y) {}
Vector2::Vector2(Vector2u v) : x(v.x), y(v.y) {}

Vector2& Vector2::operator+=(const Vector2& v1) {
  x += v1.x;
  y += v1.y;
  return *this;
}

Vector2& Vector2::operator-=(const Vector2& v1) {
  x -= v1.x;
  y -= v1.y;
  return *this;
}

Vector2& Vector2::operator*=(const Vector2& v1) {
  x *= v1.x;
  y *= v1.y;
  return *this;
}

Vector2& Vector2::operator/=(const Vector2& v1) {
  x /= v1.x;
  y /= v1.y;
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

Vector2 operator-(const Vector2& v1, const Vector2& v2) {
  Vector2 copy = v1;
  return copy -= v2;
}

Vector2 operator*(const Vector2& v1, const Vector2& v2) {
  Vector2 copy = v1;
  return copy *= v2;
}

Vector2 operator/(const Vector2& v1, const Vector2& v2) {
  Vector2 copy = v1;
  return copy /= v2;
}

Vector2 operator*(const Vector2& v1, float value) {
  Vector2 copy = v1;
  return copy *= value;
}

Vector2 operator*(float value, const Vector2& v1) { return v1 * value; }

////////////
Vector2u::Vector2u(uint32_t x, uint32_t y) : x(x), y(y) {}
Vector2u::Vector2u(Vector2 v) : x(v.x), y(v.y) {}

Vector2u& Vector2u::operator+=(const Vector2u& v1) {
  x += v1.x;
  y += v1.y;
  return *this;
}

Vector2u& Vector2u::operator*=(uint32_t value) {
  x *= value;
  y *= value;
  return *this;
}

Vector2u operator+(const Vector2u& v1, const Vector2u& v2) {
  Vector2u copy = v1;
  return copy += v2;
}

Vector2u operator*(const Vector2u& v1, uint32_t value) {
  Vector2u copy = v1;
  return copy *= value;
}

Vector2u operator*(uint32_t value, const Vector2u& v1) { return v1 * value; }

Transform& Transform::operator+=(const Transform& transform) {
  position += transform.position;
  angle += transform.angle;
  scale.x *= transform.scale.x;
  scale.y *= transform.scale.y;

  return *this;
}

Transform operator+(const Transform& transform1, const Transform& transform2) {
  Transform copy = transform1;
  return copy += transform2;
}

void EndWindow(int32_t score) {}

const Vector2 Vector2::Zero = Vector2{0.0f, 0.0f};
const Vector2u Vector2u::Zero = Vector2u(0u, 0u);