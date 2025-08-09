#include "BaseCollider.h"

#include "../ColliderManager.h"

Collider::BaseCollider::BaseCollider(const std::function<void()>& foo)
    : _onCollision(foo) {}

Collider::BaseCollider::~BaseCollider() {
  ColliderManager::UnregisterCollider(this);
}

void Collider::BaseCollider::Init() { ColliderManager::RegisterCollider(this); }

void Collider::BaseCollider::OnCollision() { _onCollision(); }