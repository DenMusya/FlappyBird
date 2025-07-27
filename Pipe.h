#pragma once

#include "GameObject.h"

class Pipe : GameObject {
 public:
  Pipe(Vector2 pivot, float distanceBetween, float width, float height);

  void draw() override;
  void move(Vector2 delta) override;

  bool Disappeared() const;

  const Rectangle& GetLowerRect() const;
  const Rectangle& GetUpperRect() const;

  bool IsFinished() const;
  void Finish();

 private:
  bool _finished = false;
};