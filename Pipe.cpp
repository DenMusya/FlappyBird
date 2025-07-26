#include "Pipe.h"

Pipe::Pipe(Vector2 pivot, int32_t distanceBetween, int32_t width, int32_t height, uint32_t color) :
           _upperRect(pivot, width, height, color),
           _lowerRect(pivot + Vector2{ 0.0f, static_cast<float>(distanceBetween + height) }, width, height, color) {}

void Pipe::draw() {
  _upperRect.draw();
  _lowerRect.draw();
}

void Pipe::move(Vector2 delta) {
  _upperRect.move(delta);
  _lowerRect.move(delta);
}

bool Pipe::Disappeared() const {
  return _upperRect.GetPivot().x + _upperRect.GetWidth() < 0;
}

const Rectangle& Pipe::GetLowerRect() const {
  return _lowerRect;
}

const Rectangle& Pipe::GetUpperRect() const {
  return _upperRect;
}

bool Pipe::IsFinished() const {
  return _finished;
}

void Pipe::Finish() {
  _finished = true;
}