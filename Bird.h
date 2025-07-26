#pragma once
#include "Rectangle.h"
#include "Movable.h"
#include "Drawable.h"
#include "Engine.h"
#include "Utils.h"
#include "Pipe.h"

class Bird : Movable, Drawable
{
public:
  Bird();

  void move(Vector2 delta) override;
  void draw() override;

  bool OnCollision(const Pipe& pipe) const;
  bool IsFinished(Pipe& pipe);
  bool OutMap();

  void update(float dt);
  void Jump();
private:
  float _velocityY = 0.0f;
  const float _gravity = 750.0f;
  const float _jumpForce = 350.0f;
  const float _terminalVelocity = 500.0f;;

  Rectangle _body;
};

