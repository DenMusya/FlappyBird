#include "Background.h"

#include "../graphics/Sprite.h"

Background::Background(const BackgroundConfig& config) : Config(config) {
  for (uint32_t i = 0; i < Config.spriteDuplicates; ++i) {
    std::shared_ptr<GameObject> dublicate = GameObject::Create<GameObject>();

    dublicate->AddComponent<Sprite>(Config.spritePath);
    _spriteSize = Vector2(dublicate->GetComponent<Sprite>()->GetSize());

    dublicate->Move(Vector2{_spriteSize.x, 0} * i);

    AddChild(dublicate);
    _background.push(dublicate);
  }
}

void Background::Update(float dt) {
  auto front = _background.front();
  if (front->GetGlobalTransform().position.x + _spriteSize.x < 0) {
    _background.pop();
    front->Move(Vector2{_spriteSize.x, 0} * Config.spriteDuplicates);
    _background.push(front);
  }

  Move(Vector2{-1, 0} * Config.speed * dt);
}