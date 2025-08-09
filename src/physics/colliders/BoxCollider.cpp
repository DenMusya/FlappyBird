#include "BoxCollider.h"

#include <algorithm>

#include "../../game/GameObject.h"
#include "PolygonCollider.h"

Collider::BoxCollider::BoxCollider(Vector2 size, Vector2 luCornerOffset,
                                   const std::function<void()>& foo)
    : PolygonCollider(luCornerOffset + size * 0.5f, foo) {
  AddPoint(Vector2{-size.x / 2, -size.y / 2});
  AddPoint(Vector2{size.x / 2, -size.y / 2});
  AddPoint(Vector2{size.x / 2, size.y / 2});
  AddPoint(Vector2{-size.x / 2, size.y / 2});
}
