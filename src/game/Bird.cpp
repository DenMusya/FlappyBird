#include "Bird.h"

#include "../core/Engine.h"
#include "../graphics/Sprite.h"
#include "../graphics/Visuals.h"
#include "../physics/Collider.h"

Bird::Bird(const BirdConfig& config) : GameObject(config.size), Config(config) {
  AddComponent<Sprite>(Vector2u(Config.size), Visuals::Bird);
  AddComponent<Collider::EllipseCollider>(Config.colliderRadiusX,
                                          Config.colliderRadiusY,
                                          Config.size * 0.5f, FreezeGame);

  Scale(config.scale);
  SetPosition(config.beginPosition, PivotType::Center);
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
  _velocityY += Config.gravity * dt;

  if (_velocityY > Config.terminalVelocity) {
    _velocityY = Config.terminalVelocity;
  }

  auto curAngle = GetGlobalTransform().angle;
  if (curAngle - _velocityY * Config.rotateSpeed * dt >
      Config.terminalTopAngle) {
    Rotate(Config.terminalTopAngle - curAngle);
  } else if (curAngle - _velocityY * Config.rotateSpeed * dt <
             Config.terminalDownAngle) {
    Rotate(Config.terminalDownAngle - curAngle);
  } else {
    Rotate(-_velocityY * Config.rotateSpeed * dt);
  }

  Move(Vector2{0, _velocityY * dt});
}

void Bird::Jump() { _velocityY = -Config.jumpForce; }