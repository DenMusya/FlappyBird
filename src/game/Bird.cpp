#include "Bird.h"

#include "../core/Engine.h"
#include "../graphics/Sprite.h"
#include "../graphics/Visuals.h"
#include "../physics/Collider.h"

Bird::Bird(Vector2 size, Vector2 pos) : GameObject(size, pos) {
  AddComponent<Sprite>(Vector2u(size), Visuals::Bird);
  AddComponent<Collider::EllipseCollider>(_rightDistance, _upperDistance,
                                          size * 0.5f, FreezeGame);
}

// bool Bird::IsFinished(Pipe& pipe) {
//   if (pipe.IsFinished()) return false;
//
//   if (GetGlobalPos().x > pipe.GetGlobalPos().x + pipe.GetWidth()) {
//     pipe.Finish();
//     return true;
//   }
//
//   return false;
// }

bool Bird::OutMap() {
  auto transform = GetGlobalTransform();
  auto size = GetSize();
  return transform.position.y > SCREEN_HEIGHT ||
         transform.position.y + size.y < 0;
}

void Bird::Update(float dt) {
  _velocityY += _gravity * dt;

  if (_velocityY > _terminalVelocity) {
    _velocityY = _terminalVelocity;
  }

  Move(Vector2{0, _velocityY * dt});
}

void Bird::Jump() { _velocityY = -_jumpForce; }