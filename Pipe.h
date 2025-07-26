#pragma once

#include "Rectangle.h"

class Pipe : Drawable, Movable {
public:
  Pipe(Vector2 pivot, int32_t distanceBetween, int32_t width, int32_t height, uint32_t color);

  void draw() override;
  void move(Vector2 delta) override;

  bool Disappeared() const;

  const Rectangle& GetLowerRect() const;
  const Rectangle& GetUpperRect() const;

  bool IsFinished() const;
  void Finish();

private:
  Rectangle _upperRect;
  Rectangle _lowerRect;

  bool _finished = false;
};