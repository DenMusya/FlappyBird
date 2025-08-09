#include "Timer.h"

Timer::Timer() : _accumulatedTime(0.0f) {}

void Timer::AddTime(float delta) { _accumulatedTime += delta; }

void Timer::Reset() { _accumulatedTime = 0.0f; }

float Timer::ElapsedTime() const { return _accumulatedTime; }