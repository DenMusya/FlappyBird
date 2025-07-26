#include "Text.h"
#include "Font.h"
#include "Utils.h"

Text::Text(const std::string& str, Vector2 pivot, uint32_t scale = 1): _str(str), _pivot(pivot), _scale(scale) {}

Text& Text::operator=(const std::string& str) {
  _str = str;
  return *this;
}

void Text::DrawChar(Vector2 pos, char c) {
  for (int row = 0; row < CharHeight; ++row) {
    uint8_t bits = Font::get(c)[row];
    for (int col = 0; col < CharWidth; ++col) {
      if (bits & (1 << (CharWidth - 1 - col))) {
        for (int dy = 0; dy < _scale; ++dy) {
          for (int dx = 0; dx < _scale; ++dx) {
            ColorPixel(pos.x + col * _scale + dx, pos.y + row * _scale + dy,
                       color);
          }
        }
      }
    }
  }
}

void Text::draw() {
  Vector2 pos = _pivot;
  for (char c : _str) {
    DrawChar(pos, c);
    pos += _scale * Vector2{ CharWidth + 1, 0 };
  }
}

void Text::move(Vector2 delta) { _pivot += delta; }