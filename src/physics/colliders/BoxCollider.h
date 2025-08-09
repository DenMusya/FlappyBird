#pragma once

#include "PolygonCollider.h"

namespace Collider {
class BoxCollider : public PolygonCollider {  // doesnt rotate
 public:
  explicit BoxCollider(
      Vector2 size, Vector2 luCornerOffset = Vector2::Zero,
      const std::function<void()>& foo = []() {});

 private:
  static const uint32_t NumPoints = 4;
};
}  // namespace Collider