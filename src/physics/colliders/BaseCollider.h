#pragma once

#include <functional>

#include "../../core/Component.h"
#include "../../utils/Utils.h"

class GameObject;

namespace Collider {

class PolygonCollider;

class BaseCollider : public Component {
 public:
  virtual bool Intersects(const BaseCollider& other) const = 0;
  virtual ~BaseCollider();
  void Init() override;
  virtual void Draw() const = 0;
  void OnCollision();
  explicit BaseCollider(const std::function<void()>& foo = []() {});

 protected:
  std::function<void()> _onCollision;
  virtual bool IntersectsWithPolygon(const PolygonCollider& other) const = 0;
};
}  // namespace Collider
