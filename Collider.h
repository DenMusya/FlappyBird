#pragma once

#include <memory>

#include "Component.h"
#include "Utils.h"

class GameObject;

namespace Collider {

class BoxCollider;
class CircleCollider;

class BaseCollider : public Component {
 public:
  virtual bool Intersects(const BaseCollider& other) const = 0;
  virtual ~BaseCollider() = default;

 protected:
  virtual bool IntersectsWithBox(const BoxCollider& other) const = 0;
  virtual bool IntersectsWithCircle(const CircleCollider& other) const = 0;
};

class CircleCollider : public BaseCollider {
 public:
  CircleCollider(float radius);
  bool Intersects(const BaseCollider& other) const override;

  Vector2 GetCentre() const;
  float GetRadius() const;

 protected:
  virtual bool IntersectsWithBox(const BoxCollider& other) const override;
  virtual bool IntersectsWithCircle(const CircleCollider& other) const override;

 private:
  float _radius;
};

class BoxCollider : public BaseCollider {
 public:
  BoxCollider() = default;

  bool Intersects(const BaseCollider& other) const override;

  Vector2 GetPos() const;
  float GetWidth() const;
  float GetHeight() const;

 protected:
  virtual bool IntersectsWithBox(const BoxCollider& other) const override;
  virtual bool IntersectsWithCircle(const CircleCollider& other) const override;
};

bool CheckCollision(const GameObject& obj1, const GameObject& obj2);
bool ProcessCollisionRecursion(const GameObject& obj1, const GameObject& obj2);

}  // namespace Collider