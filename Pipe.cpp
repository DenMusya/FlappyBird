#include "Pipe.h"

Pipe::Pipe(Vector2 pivot, float distanceBetween, float width, float height)
    : GameObject(pivot, width, height) {}

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

const Rectangle& Pipe::GetLowerRect() const { return _lowerRect; }

const Rectangle& Pipe::GetUpperRect() const { return _upperRect; }

bool Pipe::IsFinished() const { return _finished; }

void Pipe::Finish() { _finished = true; }