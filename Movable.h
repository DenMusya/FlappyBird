#pragma once
#include "Utils.h"

class Movable {
public:
  void virtual move(Vector2) = 0;
  virtual ~Movable() = default;
};