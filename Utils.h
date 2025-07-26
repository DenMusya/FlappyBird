#pragma once

#include <stdint.h>

struct Color {
  static const uint32_t Yellow = 0xFFFF00;
  static const uint32_t Blue = 0x0000FF;
  static const uint32_t DeepSkyBlue = 0x00BFFF;
  static const uint32_t DarkGray = 0xA9A9A9;
  static const uint32_t SkyBlue = 0x87CEEB;
  static const uint32_t Gray = 0x2d2d2d;
  static const uint32_t Black = 0x000000;
};


void ColorPixel(int32_t x, int32_t y, uint32_t color);
void FillBuffer(uint32_t color);

struct Vector2 {
  float x;
  float y;

  Vector2& operator+=(const Vector2& v1);
  Vector2& operator*=(float value);
};

Vector2 operator+(const Vector2& v1, const Vector2& v2);

Vector2 operator*(const Vector2& v1, float value);
Vector2 operator*(float value, const Vector2& v1);

void EndWindow(int32_t score);

template<typename T>
T Min(T value) {
    return value;
}

//template<typename T>
//T Min(T value1, T value2) {
//    return value1 > value2 ? value2 : value1;
//}
//
//template<typename T, typename... Args>
//T Min(T value, Args... args) {
//    return Min(value, Min(args...));
//}
