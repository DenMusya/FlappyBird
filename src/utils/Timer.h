#pragma once
#include "../game/GameObject.h"

class Timer {
 public:
  Timer();

  void AddTime(float delta);

  void Reset();

  float ElapsedTime() const;

 private:
  float _accumulatedTime;
};
