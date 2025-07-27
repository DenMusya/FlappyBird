#include "Bird.h"

Bird::Bird(Vector2 pos, float width, float height, float colliderRadius)
    : GameObject(pos, width, height,
                 std::make_unique<Collider::CircleCollider>(colliderRadius)) {}

bool Bird::OnCollision(const Pipe& pipe) const {
  /*return GetCollider()->Intersects(pipe.GetLowerRect().GetCollider()) ||
         GetCollider()->Intersects(pipe.GetUpperRect().GetCollider());*/
}

bool Bird::IsFinished(Pipe& pipe) {
  if (pipe.IsFinished()) return false;

  if (_body.GetPivot().x >
      pipe.GetLowerRect().GetPivot().x + pipe.GetLowerRect().GetWidth()) {
    pipe.Finish();
    return true;
  }

  return false;
}

bool Bird::OutMap() {
  return GetPos().y > SCREEN_HEIGHT || GetPos().y + GetHeight() < 0;
}

void Bird::update(float dt) {
  _velocityY += _gravity * dt;

  if (_velocityY > _terminalVelocity) {
    _velocityY = _terminalVelocity;
  }

  Move(Vector2{0, _velocityY * dt});
}

void Bird::Jump() { _velocityY = -_jumpForce; }
