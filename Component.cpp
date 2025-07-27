#include "Component.h"

#include "GameObject.h"

std::shared_ptr<GameObject> Component::GetOwner() const {
  return _owner.lock();
}

void Component::SetOwner(std::shared_ptr<GameObject> owner) { _owner = owner; }