#include "Pipe.h"

#include "../core/Engine.h"
#include "../graphics/Sprite.h"
#include "../graphics/Visuals.h"
#include "../physics/Collider.h"

Pipe::Pipe(Vector2 size, Vector2 pos, float distanceBetween)
    : GameObject(size + Vector2{0, size.y + distanceBetween}, pos) {
  std::shared_ptr<GameObject> upperPipe = GameObject::Create<GameObject>(size);
  std::shared_ptr<GameObject> lowerPipe = GameObject::Create<GameObject>(
      size, Vector2{0, size.y + distanceBetween});

  upperPipe->AddComponent<Sprite>(Vector2u(size), Visuals::Pipe);
  lowerPipe->AddComponent<Sprite>(Vector2u(size), Visuals::Pipe);

  upperPipe->AddComponent<Collider::BoxCollider>(size);
  lowerPipe->AddComponent<Collider::BoxCollider>(size);

  AddChild(upperPipe);
  AddChild(lowerPipe);
}

bool Pipe::Disappeared() const {
  return _transform.position.x + GetSize().x < 0;
}

bool Pipe::IsFinished() const { return _finished; }

void Pipe::Finish() { _finished = true; }

void Pipe::Update(float dt) { Move(Vector2{-dt * Speed, 0}); }