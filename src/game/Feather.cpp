#include "Feather.h"

#include "../graphics/Sprite.h"

Feather::Feather(const FeatherConfig& conf)
    : GameObject(conf.size, conf.pos), Config(conf) {
  auto compt = AddComponent<Sprite>(conf.spritePath);
  Config.size = Vector2(compt->GetSize());
  SetSize(Config.size);
  Scale(conf.scale);
  Rotate(conf.rotation);
}

void Feather::Update(float dt) {
  Config.velocity += Vector2{0, Config.gravity * dt};
  Rotate(dt * Config.rotationSpeed);
  Move(dt * Config.velocity);
}