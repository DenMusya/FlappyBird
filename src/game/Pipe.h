#pragma once
#include "GameObject.h"

class Pipe : public GameObject {
 public:
  Pipe(Vector2 size, Vector2 pos, float distanceBetween);

  bool Disappeared() const;
  bool IsFinished() const;
  void Finish();
  void Update(float dt);

 private:
  bool _finished = false;
  const float Speed = 300.0f;
};
