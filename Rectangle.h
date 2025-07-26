#pragma once
#include "Movable.h"
#include "Drawable.h"

class Rectangle : Drawable, Movable {
private:
  Vector2 _pivot;
  int32_t _width;
  int32_t _height;
  uint32_t _color;

  int32_t _borderWidth;
  uint32_t _borderColor;
public:
  Rectangle(Vector2 pivot, int32_t width, int32_t height, uint32_t color, int32_t borderWidth = 5 , uint32_t borderColor = Color::Black);

  void draw() override;

  void move(Vector2 delta) override;

  Vector2 GetPivot() const;
  int32_t GetWidth() const;
  int32_t GetHeight() const;

  bool OnCollision(const Rectangle& other) const;

};