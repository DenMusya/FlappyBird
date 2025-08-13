#include "Component.h"

#include "../game/GameObject.h"

std::shared_ptr<GameObject> Component::GetOwner() const {
  return _owner.lock();
}

void Component::SetOwner(std::shared_ptr<GameObject> owner) { _owner = owner; }

bool Component::IsActive() const { return _isActive; }

void Component::Activate() { _isActive = true; }

void Component::Disactivate() { _isActive = false; }