#include "EllipseCollider.h"

#include <numbers>

Collider::EllipseCollider::EllipseCollider(float a, float b,
                                           Vector2 centerOffset,
                                           const std::function<void()>& foo)
    : PolygonCollider(centerOffset, foo) {
  for (uint32_t i = 0; i < NumPoints; ++i) {
    float angle = 2 * i * std::numbers::pi / NumPoints;
    float x = a * cosf(angle);
    float y = b * sinf(angle);
    AddPoint(Vector2{x, y});
  }
}