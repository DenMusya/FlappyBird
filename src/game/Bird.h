#pragma once
#include <numbers>

#include "../utils/Utils.h"
#include "GameObject.h"

class Bird : public GameObject {
 public:
  Bird(Vector2 size, Vector2 pos);

  // bool IsFinished(Pipe& pipe);
  bool OutMap();

  void Update(float dt);
  void Jump();

 private:
  float _velocityY = 0.0f;
  const float _gravity = 750.0f;
  const float _jumpForce = 350.0f;
  const float _terminalVelocity = 500.0f;
  const float _rotateSpeed = 0.02f;

  const float _terminalTopRotation = ToRadians(45);
  const float _terminalDownRotation = -ToRadians(15);
  const float _rightDistance = 21.0f;
  const float _upperDistance = 13.5f;
  ;

  // Rectangle _body;
};
