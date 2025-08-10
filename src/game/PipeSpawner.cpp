#include "PipeSpawner.h"

#include "../core/Component.h"
#include "../core/Engine.h"

PipeSpawner::PipeSpawner(const PipeSpawnerConfig& spawnerConfig,
                         const PipeConfig& pipePreset)
    : SpawnerConfig(spawnerConfig), PipePreset(pipePreset) {}

std::shared_ptr<Pipe> PipeSpawner::SpawnPipe() {
  Vector2 pivot{SCREEN_WIDTH,
                -PipePreset.size.y +
                    (SCREEN_HEIGHT - PipePreset.distanceBetweenPipes) / 2.0f};
  float x = pivot.x;
  float y = pivot.y + SpawnerConfig.randomLowerBound +
            std::rand() % static_cast<int>(SpawnerConfig.randomUpperBound -
                                           SpawnerConfig.randomLowerBound + 1);
  return GameObject::Create<Pipe>(Vector2{x, y}, PipePreset);
}

void PipeSpawner::Update(float dt) {
  if (!_pipes.empty() && _pipes.front()->Disappeared()) {
    _pipes.erase(_pipes.begin());
  }

  _timer.AddTime(dt);
  if (_timer.ElapsedTime() > SpawnerConfig.timeToNewPipe) {
    _timer.Reset();
    _pipes.push_back(SpawnPipe());
  }
}

std::span<std::shared_ptr<Pipe>> PipeSpawner::GetPipes() { return _pipes; }