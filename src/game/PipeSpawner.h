#pragma once
#include <memory>
#include <span>

#include "../utils/Config.h"
#include "../utils/Timer.h"
#include "../utils/Utils.h"
#include "Pipe.h"

class PipeSpawner : public GameObject {
 public:
  PipeSpawner(const PipeSpawnerConfig& spawnerConfig,
              const PipeConfig& PipeConfig);

  void Update(float dt);

  std::span<std::shared_ptr<Pipe>> GetPipes();

 private:
  std::shared_ptr<Pipe> SpawnPipe();

  const PipeConfig PipePreset;
  const PipeSpawnerConfig SpawnerConfig;

  std::vector<std::shared_ptr<Pipe>> _pipes;
  Timer _timer;
};
