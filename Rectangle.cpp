#include "Rectangle.h"
#include "Utils.h"
#include <algorithm>

Rectangle::Rectangle(Vector2 pivot, int32_t width, int32_t height, uint32_t color, int32_t borderWidth, uint32_t borderColor) :
    _pivot(pivot), _width(width), _height(height), _color(color), _borderWidth(borderWidth), _borderColor(borderColor) {}

void Rectangle::draw() {
  for (int32_t i = 0; i < _height; ++i) {
    for (int32_t j = 0; j < _width; ++j) {
      bool isBorder = std::min(std::min(i, j), std::min(_height - i - 1, _width - j - 1)) < _borderWidth;


      ColorPixel(_pivot.x + j, _pivot.y + i, isBorder ? _borderColor : _color);
    }
  }
}

void Rectangle::move(Vector2 delta) {
  _pivot += delta;
}

bool Rectangle::OnCollision(const Rectangle& other) const {
  int32_t thisLeft = _pivot.x;
  int32_t thisTop = _pivot.y;
  int32_t thisRight = _pivot.x + _width;
  int32_t thisBottom = _pivot.y + _height;

  int32_t otherLeft = other._pivot.x;
  int32_t otherTop = other._pivot.y;
  int32_t otherRight = other._pivot.x + other._width;
  int32_t otherBottom = other._pivot.y + other._height;

  bool overlapX = thisLeft <= otherRight && otherLeft <= thisRight;
  bool overlapY = thisTop <= otherBottom && otherTop <= thisBottom;

  return overlapX && overlapY;
}

Vector2 Rectangle::GetPivot() const {
  return _pivot;
}

int32_t Rectangle::GetWidth() const {
  return _width;
}

int32_t  Rectangle::GetHeight() const {
  return _height;
}