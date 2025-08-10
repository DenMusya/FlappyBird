#pragma once
#include "../utils/Config.h"
#include "GameObject.h"

class Pipe : public GameObject {
 public:
  Pipe(Vector2 pos, const PipeConfig& config);

  bool Disappeared() const;
  bool IsFinished() const;
  void Finish();
  void Update(float dt);

 private:
  const PipeConfig Config;
  bool _finished = false;
};
