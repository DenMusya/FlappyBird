#pragma once
#include <numbers>

#include "../utils/Config.h"
#include "../utils/Utils.h"
#include "GameObject.h"
#include "Pipe.h"

class Bird : public GameObject {
 private:
  const BirdConfig Config;
  float _velocityY = 0.0f;

 public:
  Bird(const BirdConfig& config);

  bool IsFinished(const Pipe& pipe) const;
  bool OutMap() const;

  void Update(float dt);
  void Jump();
};
