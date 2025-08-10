#include "Color.h"

#include <algorithm>

Color::Color(uint32_t color, ColorFormat format) {
  if (format == ColorFormat::RGBA) {
    r = (color >> 24u) & 0xFFu;
    g = (color >> 16u) & 0xFFu;
    b = (color >> 8u) & 0xFFu;
    a = color & 0xFFu;
  } else if (format == ColorFormat::ARGB) {
    a = (color >> 24u) & 0xFFu;
    r = (color >> 16u) & 0xFFu;
    g = (color >> 8u) & 0xFFu;
    b = color & 0xFFu;
  }
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : r(r), g(g), b(b), a(a) {}

uint32_t Color::GetARGB() const { return (a << 24) | (r << 16) | (g << 8) | b; }

bool Color::IsTransparent() const { return a == 0; }

Color Color::Lerp(const Color& color1, const Color& color2, float t) {
  uint8_t mx_r = std::max(color1.r, color2.r);
  uint8_t mx_g = std::max(color1.g, color2.g);
  uint8_t mx_b = std::max(color1.b, color2.b);
  uint8_t mx_a = std::max(color1.a, color2.a);

  uint8_t mn_r = std::min(color1.r, color2.r);
  uint8_t mn_g = std::min(color1.g, color2.g);
  uint8_t mn_b = std::min(color1.b, color2.b);
  uint8_t mn_a = std::min(color1.a, color2.a);

  return Color(mn_r + t * (mx_r - mn_r), mn_g + t * (mx_g - mn_g),
               mn_b + t * (mx_b - mn_b), mn_a + t * (mx_a - mn_a));
}