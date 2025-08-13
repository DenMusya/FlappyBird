#include "Pipe.h"

#include "../core/Engine.h"
#include "../graphics/Sprite.h"
#include "../graphics/Visuals.h"
#include "../physics/Collider.h"

Pipe::Pipe(Vector2 pos, const PipeConfig& config)
    : GameObject(
          config.size + Vector2{0, config.size.y + config.distanceBetweenPipes},
          pos),
      Config(config) {
  std::shared_ptr<GameObject> upperPipe =
      GameObject::Create<GameObject>(Config.size);
  std::shared_ptr<GameObject> lowerPipe = GameObject::Create<GameObject>(
      Config.size, Vector2{0, Config.size.y + Config.distanceBetweenPipes});

  upperPipe->AddComponent<Sprite>(config.spritePath);
  lowerPipe->AddComponent<Sprite>(config.spritePath);

  upperPipe->AddComponent<Collider::BoxCollider>(Config.size);
  lowerPipe->AddComponent<Collider::BoxCollider>(Config.size);

  AddChild(upperPipe);
  AddChild(lowerPipe);
}

bool Pipe::Disappeared() const {
  return _transform.position.x + GetSize().x < 0;
}

bool Pipe::IsFinished() const { return _finished; }

void Pipe::Finish() { _finished = true; }

void Pipe::Update(float dt) { Move(Vector2{-dt * Config.speed, 0}); }