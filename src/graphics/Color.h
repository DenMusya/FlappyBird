#pragma once
#include <cstdint>

enum class ColorFormat { ARGB, RGBA };

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

  Color(uint32_t color, ColorFormat format = ColorFormat::RGBA);
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);
  Color() = default;

  uint32_t GetARGB() const;

  bool IsTransparent() const;

  static Color Lerp(const Color& color1, const Color& color2, float t);
};
