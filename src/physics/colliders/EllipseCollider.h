#pragma once

#include "PolygonCollider.h"

namespace Collider {
class EllipseCollider : public PolygonCollider {
 public:
  EllipseCollider(
      float a, float b, Vector2 centerOffset,
      const std::function<void()>& foo = []() {});

 private:
  static const uint32_t NumPoints = 32;
};
}  // namespace Collider