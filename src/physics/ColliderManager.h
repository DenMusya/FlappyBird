#pragma once
#include <vector>

#include "Collider.h"

class ColliderManager {
 public:
  static void CheckCollisions();
  static void RegisterCollider(Collider::BaseCollider* collider);
  static void UnregisterCollider(Collider::BaseCollider* sprite);
  static void UpdateColliders();
  static void DrawColliders();

 private:
  static std::vector<Collider::BaseCollider*> _colliders;
};