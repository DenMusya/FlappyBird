#pragma once
#include <numbers>

#include "../utils/Config.h"
#include "../utils/Utils.h"
#include "GameObject.h"

class Bird : public GameObject {
 private:
  const BirdConfig Config;
  float _velocityY = 0.0f;

 public:
  Bird(const BirdConfig& config);

  // bool IsFinished(Pipe& pipe);
  bool OutMap();

  void Update(float dt);
  void Jump();
};
