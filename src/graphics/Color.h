#pragma once
#include <cstdint>

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

  Color(uint32_t color);
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);
  Color() = default;

  uint32_t GetRGB() const;

  bool IsTransparent() const;

  static Color Lerp(const Color& color1, const Color& color2, float t);
};
