#include "PipeSpawner.h"
#include "Engine.h"

const float PipeSpawner::PipeSpeed = 100.0f;
const Vector2 PipeSpawner::Pivot{ SCREEN_WIDTH, -PipeHeight + (SCREEN_HEIGHT / 2.0f - DistanceBetweenPipes / 2.0f)};

std::unique_ptr<Pipe> PipeSpawner::SpawnPipe() {
  return std::make_unique<Pipe>(Pivot + Vector2{0.0f, static_cast<float>(RandomLowerBound + std::rand() % (RandomUpperBound - RandomLowerBound + 1))},
         DistanceBetweenPipes, PipeWidth, PipeHeight, PipeColor);
}