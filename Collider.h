#pragma once

#include <memory>

#include "GameObject.h"
#include "Utils.h"

namespace Collider {

class BoxCollider;
class CircleCollider;

class BaseCollider {
 public:
  virtual bool Intersects(const BaseCollider& other) const = 0;
  virtual bool IntersectsWithBox(const BoxCollider& other) const = 0;
  virtual bool IntersectsWithCircle(const CircleCollider& other) const = 0;

  void SetGameObject(std::shared_ptr<GameObject> gameObject);

  virtual ~BaseCollider() = default;

 protected:
  std::shared_ptr<GameObject> _gameObject;
};

class CircleCollider : BaseCollider {
 public:
  CircleCollider(float radius);
  bool Intersects(const BaseCollider& other) const override;
  bool IntersectsWithBox(const BoxCollider& other) const override;
  bool IntersectsWithCircle(const CircleCollider& other) const override;

  Vector2 GetCentre() const;
  float GetRadius() const;

 private:
  float _radius;
};

class BoxCollider : BaseCollider {
 public:
  BoxCollider() = default;

  bool Intersects(const BaseCollider& other) const override;
  bool IntersectsWithBox(const BoxCollider& other) const override;
  bool IntersectsWithCircle(const CircleCollider& other) const override;

  Vector2 GetPos() const;
  float GetWidth() const;
  float GetHeight() const;
};

}  // namespace Collider