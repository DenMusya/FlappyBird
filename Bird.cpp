#include "Bird.h"

Bird::Bird() :_body(Vector2{ SCREEN_WIDTH / 2.0f - 30 , SCREEN_HEIGHT / 2.0f - 30 }, 60, 60, Color::Yellow) {}

void Bird::draw() {
  _body.draw();
}

void Bird::move(Vector2 delta) {
  _body.move(delta);
}

bool Bird::OnCollision(const Pipe& pipe) const {
  return _body.OnCollision(pipe.GetLowerRect()) || _body.OnCollision(pipe.GetUpperRect());
}

bool Bird::IsFinished(Pipe& pipe) {
  if (pipe.IsFinished()) return false;

  if (_body.GetPivot().x > pipe.GetLowerRect().GetPivot().x + pipe.GetLowerRect().GetWidth()) {
    pipe.Finish();
    return true;
  }


  return false;
}

bool Bird::OutMap() {
  return !_body.OnCollision(Rectangle(Vector2{ 0,0 }, SCREEN_WIDTH, SCREEN_HEIGHT, Color::Blue));
}


void Bird::update(float dt) {
  _velocityY += _gravity * dt;

  if (_velocityY > _terminalVelocity) {
    _velocityY = _terminalVelocity;
  }

  _body.move(Vector2{ 0, _velocityY * dt });
}

void Bird::Jump() {
  _velocityY = -_jumpForce;
}
