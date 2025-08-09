#include "PipeSpawner.h"

#include "../core/Component.h"
#include "../core/Engine.h"

const Vector2 PipeSpawner::Pivot{
    SCREEN_WIDTH,
    -PipeHeight + (SCREEN_HEIGHT / 2.0f - DistanceBetweenPipes / 2.0f)};

std::shared_ptr<Pipe> PipeSpawner::SpawnPipe() {
  float x = Pivot.x;
  float y = Pivot.y + RandomLowerBound +
            std::rand() % (RandomUpperBound - RandomLowerBound + 1);
  auto pipe = GameObject::Create<Pipe>(Vector2{PipeWidth, PipeHeight},
                                       Vector2{x, y}, DistanceBetweenPipes);
  return pipe;
}