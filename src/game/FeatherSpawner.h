#pragma once

#include <vector>

#include "../utils/Config.h"
#include "Feather.h"
#include "GameObject.h"

class FeatherSpawner : public GameObject {
 public:
  void SpawnFeathers(Vector2 pos);
  void ClearFeathers();
  std::span<std::shared_ptr<Feather>> GetFeathers();

 private:
  std::vector<std::shared_ptr<Feather>> _feathers;
};