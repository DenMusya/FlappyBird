#pragma once

class Drawable {
public:
  void virtual draw() = 0;
  virtual ~Drawable() = default;
};