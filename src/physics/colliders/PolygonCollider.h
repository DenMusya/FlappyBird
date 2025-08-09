#pragma once

#include <span>

#include "BaseCollider.h"

namespace Collider {
class PolygonCollider : public BaseCollider {
 private:
  std::vector<Vector2> _localPoints;
  mutable std::vector<Vector2> _globalPoints;
  Vector2 _centerOffset;

 public:
  bool Intersects(const BaseCollider& other) const override;
  explicit PolygonCollider(
      Vector2 centerOffset, const std::function<void()>& foo = []() {});
  void AddPoint(Vector2 point);
  std::span<Vector2> GetPoints() const;
  void UpdatePoints() const;
  void Draw() const override;

 protected:
  bool IntersectsWithPolygon(const PolygonCollider& other) const override;

 private:
  static bool OverlapOnAxis(const std::vector<Vector2>& polyA,
                            const std::vector<Vector2>& polyB, float axisX,
                            float axisY);
};
}  // namespace Collider