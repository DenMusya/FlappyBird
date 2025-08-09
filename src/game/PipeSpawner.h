#pragma once
#include <memory>

#include "../utils/Utils.h"
#include "Pipe.h"

class PipeSpawner : public GameObject {
 public:
  std::shared_ptr<Pipe> SpawnPipe();
  const float TimeToNewPipe = 2.0f;

 private:
  static const int32_t PipeWidth = 100;
  static const int32_t PipeHeight = 600;
  static const int32_t DistanceBetweenPipes = 200;
  static const int32_t RandomLowerBound = -300;
  static const int32_t RandomUpperBound = 300;

  static const Vector2 Pivot;
};
