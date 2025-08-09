#pragma once

#include <stdint.h>

#include <memory>
#include <string>

#include "../core/Engine.h"

struct Color;

extern bool freeze;

void FreezeGame();

void ColorPixel(int32_t x, int32_t y, uint32_t color);
void FillBuffer(uint32_t color);
void DrawBack();

extern uint32_t backBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

void FillBufferGradient(Color color1, Color color2);
uint8_t Lerp(uint8_t a, uint8_t b, float t);

void DebugLog(const std::string& message);
float ToRadians(float degree);

struct Vector2u;

struct Vector2 {
  float x;
  float y;

  Vector2(float x, float y);
  explicit Vector2(Vector2u v);

  Vector2& operator+=(const Vector2& v1);
  Vector2& operator-=(const Vector2& v1);
  Vector2& operator*=(const Vector2& v1);
  Vector2& operator/=(const Vector2& v1);

  Vector2& operator*=(float value);

  static const Vector2 Zero;
};

struct Vector2u {
  uint32_t x;
  uint32_t y;

  Vector2u(uint32_t x, uint32_t y);
  explicit Vector2u(Vector2 v);

  Vector2u& operator+=(const Vector2u& v1);
  Vector2u& operator*=(uint32_t value);

  static const Vector2u Zero;
};

struct Transform {
  Vector2 position = Vector2::Zero;
  Vector2 scale = Vector2{1.0f, 1.0f};
  float angle = 0.0f;

  Transform& operator+=(const Transform& transform);
};

Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);
Vector2 operator/(const Vector2& v1, const Vector2& v2);
Vector2 operator*(const Vector2& v1, const Vector2& v2);

Vector2 operator*(const Vector2& v1, float value);
Vector2 operator*(float value, const Vector2& v1);

Vector2u operator+(const Vector2u& v1, const Vector2u& v2);
Vector2u operator*(const Vector2u& v1, uint32_t value);
Vector2u operator*(uint32_t value, const Vector2u& v1);

Transform operator+(const Transform& transform1, const Transform& transform);

void EndWindow(int32_t score);
