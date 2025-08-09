#pragma once
#include <cstdint>

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

  Color(uint32_t color) {
    r = (color >> 24u) & 0xFFu;
    g = (color >> 16u) & 0xFFu;
    b = (color >> 8u) & 0xFFu;
    a = color & 0xFFu;
  }

  Color() = default;

  uint32_t GetRGB() const { return (r << 16) | (g << 8) | b; }

  bool IsTransparent() const { return a == 0; }
};
