#pragma once

#include "../utils/Config.h"
#include "GameObject.h"

class Feather : public GameObject {
 public:
  Feather(const FeatherConfig& featherConfig);
  void Update(float dt);

 private:
  FeatherConfig Config;
};