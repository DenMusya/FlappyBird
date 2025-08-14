#include "Bird.h"

#include "../core/Engine.h"
#include "../graphics/Sprite.h"
#include "../graphics/Visuals.h"
#include "../physics/Collider.h"

Bird::Bird(const BirdConfig& config) : GameObject(config.size), Config(config) {
  _baseSprite = AddComponent<Sprite>(Config.baseSpritePath);
  _deadSprite = AddComponent<Sprite>(Config.deadSpritePath);

  _deadSprite->Disactivate();

  auto onDead = [this]() { this->OnDead(); };
  AddComponent<Collider::EllipseCollider>(Config.colliderRadiusX,
                                          Config.colliderRadiusY,
                                          Config.size * 0.5f, onDead);

  Scale(config.scale);
  SetPosition(config.beginPosition, PivotType::Center);
}

bool Bird::IsFinished(const Pipe& pipe) const {
  if (GetGlobalTransform().position.x >
      pipe.GetGlobalTransform().position.x + pipe.GetSize().x) {
    return true;
  }

  return false;
}

bool Bird::OutMap() const {
  auto transform = GetGlobalTransform();
  auto size = GetSize();
  return transform.position.y > SCREEN_HEIGHT ||
         transform.position.y + size.y < 0;
}

void Bird::Update(float dt) {
  if (!_isDead) {
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
  } else {
    if (!_featherSpawner) {
      _featherSpawner = GameObject::Create<FeatherSpawner>();
      _featherSpawner->SpawnFeathers(GetGlobalTransform().position);
    }
    _velocityY += Config.gravity * dt;
    Move(Vector2{0, _velocityY * dt});
    Rotate(Config.deadRotationSpeed * dt);
    for (auto& feather : _featherSpawner->GetFeathers()) {
      feather->Update(dt);
    }
  }
}

void Bird::Jump() { _velocityY = -Config.jumpForce; }

void Bird::Reset() {
  SetRotation(0);
  SetPosition(Config.beginPosition, PivotType::Center);
  _velocityY = 0.0f;
  _featherSpawner = nullptr;
  _isDead = false;
  _baseSprite->Activate();
  _deadSprite->Disactivate();
}

bool Bird::IsDead() const { return _isDead; }

void Bird::OnDead() {
  _velocityY = -1.4 * Config.jumpForce;
  _isDead = true;
  _baseSprite->Disactivate();
  _deadSprite->Activate();
}