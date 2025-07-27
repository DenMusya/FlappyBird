#pragma once
#include "Collider.h"
#include "Drawable.h"
#include "Engine.h"
#include "GameObject.h"
#include "Movable.h"
#include "Pipe.h"
#include "Rectangle.h"
#include "Utils.h"

class Bird : GameObject {
 public:
  Bird(Vector2 pos, float width, float height, float colliderRadius);

  bool OnCollision(const Pipe& pipe) const;
  bool IsFinished(Pipe& pipe);
  bool OutMap();

  void update(float dt);
  void Jump();

 private:
  float _velocityY = 0.0f;
  const float _gravity = 750.0f;
  const float _jumpForce = 350.0f;
  const float _terminalVelocity = 500.0f;
  ;

  // Rectangle _body;
};
