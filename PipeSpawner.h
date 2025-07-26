#pragma once
#include "Utils.h"
#include "Pipe.h"
#include <memory>

class PipeSpawner
{
public:
  std::unique_ptr<Pipe> SpawnPipe();
private:
  static const uint32_t PipeColor = Color::Gray;
  static const int32_t PipeWidth = 100;
  static const int32_t PipeHeight = 600;
  static const int32_t DistanceBetweenPipes = 200;
  static const int32_t RandomLowerBound = -300;
  static const int32_t RandomUpperBound = 300;


  static const float PipeSpeed;
  static const Vector2 Pivot;
};


