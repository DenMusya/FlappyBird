#include "Collider.h"

#include <algorithm>

#include "GameObject.h"

//
// BaseCollider
//

bool Collider::CheckCollision(const GameObject& obj1, const GameObject& obj2) {
  if (ProcessCollisionRecursion(obj1, obj2)) {
    return true;
  }

  for (const auto& child : obj1.GetChilds()) {
    if (CheckCollision(*child, obj2)) {
      return true;
    }
  }

  return false;
}

bool Collider::ProcessCollisionRecursion(const GameObject& obj1,
                                         const GameObject& obj2) {
  BaseCollider* collider1 = obj1.GetComponent<BaseCollider>();

  BaseCollider* collider2 = obj2.GetComponent<BaseCollider>();

  if (collider1 && collider2 && collider1->Intersects(*collider2)) {
    return true;
  }

  for (const auto& child : obj2.GetChilds()) {
    if (ProcessCollisionRecursion(obj1, *child)) {
      return true;
    }
  }

  return false;
}

//
// CircleCollider
//

Collider::CircleCollider::CircleCollider(float radius) : _radius(radius) {}

bool Collider::CircleCollider::Intersects(const BaseCollider& other) const {
  if (auto circle = dynamic_cast<const CircleCollider*>(&other)) {
    return this->IntersectsWithCircle(*circle);
  }
  if (auto box = dynamic_cast<const BoxCollider*>(&other)) {
    return this->IntersectsWithBox(*box);
  }

  return false;
}

bool Collider::CircleCollider::IntersectsWithBox(
    const BoxCollider& other) const {
  Vector2 centre = GetCentre();
  float radius = GetRadius();

  Vector2 pos = other.GetPos();
  float width = other.GetWidth();
  float height = other.GetHeight();

  float closestX = std::clamp(centre.x, pos.x, pos.x + width);
  float closestY = std::clamp(centre.y, pos.y, pos.y + height);

  float dx = closestX - centre.x;
  float dy = closestY - centre.y;

  return dx * dx + dy * dy <= radius * radius;
}

bool Collider::CircleCollider::IntersectsWithCircle(
    const CircleCollider& other) const {
  Vector2 centre1 = GetCentre();
  Vector2 centre2 = other.GetCentre();

  float dx = centre1.x - centre2.x;
  float dy = centre1.y - centre2.y;

  float dist = _radius + other._radius;

  return dx * dx + dy * dy <= dist * dist;
}

Vector2 Collider::CircleCollider::GetCentre() const {
  return GetOwner()->GetGlobalPos() +
         0.5f * Vector2{GetOwner()->GetWidth(), GetOwner()->GetHeight()};
}

float Collider::CircleCollider::GetRadius() const { return _radius; }

//
// BoxCollider
//

bool Collider::BoxCollider::Intersects(const BaseCollider& other) const {
  if (auto circle = dynamic_cast<const CircleCollider*>(&other)) {
    return this->IntersectsWithCircle(*circle);
  }
  if (auto box = dynamic_cast<const BoxCollider*>(&other)) {
    return this->IntersectsWithBox(*box);
  }

  return false;
}

bool Collider::BoxCollider::IntersectsWithBox(const BoxCollider& other) const {
  Vector2 pos1 = GetPos();
  float width1 = GetWidth();
  float height1 = GetHeight();

  Vector2 pos2 = GetPos();
  float width2 = GetWidth();
  float height2 = GetHeight();

  float thisLeft = pos1.x;
  float thisTop = pos1.y;
  float thisRight = pos1.x + width1;
  float thisBottom = pos1.y + height1;

  float otherLeft = pos2.x;
  float otherTop = pos2.y;
  float otherRight = pos2.x + width2;
  float otherBottom = pos2.y + height2;

  bool overlapX = thisLeft <= otherRight && otherLeft <= thisRight;
  bool overlapY = thisTop <= otherBottom && otherTop <= thisBottom;

  return overlapX && overlapY;
}

bool Collider::BoxCollider::IntersectsWithCircle(
    const CircleCollider& other) const {
  Vector2 centre = other.GetCentre();
  float radius = other.GetRadius();

  Vector2 pos = GetPos();
  float width = GetWidth();
  float height = GetHeight();

  float closestX = std::clamp(centre.x, pos.x, pos.x + width);
  float closestY = std::clamp(centre.y, pos.y, pos.y + height);

  float dx = closestX - centre.x;
  float dy = closestY - centre.y;

  return dx * dx + dy * dy <= radius * radius;
}

Vector2 Collider::BoxCollider::GetPos() const {
  return GetOwner()->GetGlobalPos();
}

float Collider::BoxCollider::GetWidth() const { return GetOwner()->GetWidth(); }

float Collider::BoxCollider::GetHeight() const {
  return GetOwner()->GetHeight();
}