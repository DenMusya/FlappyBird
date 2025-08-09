#include "ColliderManager.h"

std::vector<Collider::BaseCollider*> ColliderManager::_colliders;

void ColliderManager::CheckCollisions() {
  for (uint32_t i = 0; i < _colliders.size(); ++i) {
    for (uint32_t j = i + 1; j < _colliders.size(); ++j) {
      if (_colliders[i]->GetOwner() != _colliders[j]->GetOwner() &&
          _colliders[i]->Intersects(*_colliders[j])) {
        _colliders[i]->OnCollision();
        _colliders[j]->OnCollision();
      }
    }
  }
}

void ColliderManager::RegisterCollider(Collider::BaseCollider* collider) {
  _colliders.push_back(collider);
}

void ColliderManager::UnregisterCollider(Collider::BaseCollider* collider) {
  auto it = std::find(_colliders.begin(), _colliders.end(), collider);
  if (it != _colliders.end()) {
    _colliders.erase(it);
  }
}

void ColliderManager::UpdateColliders() {
  for (auto& collider : _colliders) {
    if (auto it = dynamic_cast<Collider::PolygonCollider*>(collider)) {
      it->UpdatePoints();
    }
  }
}

void ColliderManager::DrawColliders() {
  for (auto& collider : _colliders) {
    collider->Draw();
    // if (auto it = dynamic_cast<Collider::PolygonCollider*>(collider)) {
    //   for (auto point : it->GetPoints()) {
    //     DebugLog("x: " + std::to_string(point.x) +
    //              ", y: " + std::to_string(point.y));
    //   }
    // }
  }
}