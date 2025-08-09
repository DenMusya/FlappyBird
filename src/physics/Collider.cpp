#include "Collider.h"
//
// #include <algorithm>
//
// #include "../game/GameObject.h"
// #include "ColliderManager.h"
//
// BaseCollider
//

// Collider::BaseCollider::BaseCollider(const std::function<void()>& foo)
//     : _onCollision(foo) {}
//
// bool Collider::BaseCollider::Intersects(const BaseCollider& other) const {
//   return other.ProcessIntersect(*this);
// }
//
// Collider::BaseCollider::~BaseCollider() {
//   ColliderManager::UnregisterCollider(this);
// }
//
// void Collider::BaseCollider::Init() {
// ColliderManager::RegisterCollider(this); }
//
// void Collider::BaseCollider::OnCollision() { _onCollision(); }
//
////
//// CircleCollider
////
//
// Collider::CircleCollider::CircleCollider(float radius,
//                                         const std::function<void()>& foo)
//    : BaseCollider(foo), _radius(radius) {}
//
// bool Collider::CircleCollider::ProcessIntersect(
//    const BaseCollider& other) const {
//  return other.IntersectsWithCircle(*this);
//}
//
// bool Collider::CircleCollider::IntersectsWithBox(
//    const BoxCollider& other) const {
//  Vector2 centre = GetCentre();
//  float radius = GetRadius();
//
//  Vector2 pos = other.GetPos();
//  float width = other.GetWidth();
//  float height = other.GetHeight();
//
//  float closestX = std::clamp(centre.x, pos.x, pos.x + width);
//  float closestY = std::clamp(centre.y, pos.y, pos.y + height);
//
//  float dx = closestX - centre.x;
//  float dy = closestY - centre.y;
//
//  return dx * dx + dy * dy <= radius * radius;
//}
//
// bool Collider::CircleCollider::IntersectsWithCircle(
//    const CircleCollider& other) const {
//  Vector2 centre1 = GetCentre();
//  Vector2 centre2 = other.GetCentre();
//
//  float dx = centre1.x - centre2.x;
//  float dy = centre1.y - centre2.y;
//
//  float dist = GetRadius() + other.GetRadius();
//
//  return dx * dx + dy * dy <= dist * dist;
//}
//
// Vector2 Collider::CircleCollider::GetCentre() const {
//  return GetOwner()->GetGlobalCenter();
//}
//
// float Collider::CircleCollider::GetRadius() const {
//  return _radius * GetOwner()->GetGlobalTransform().scale.x;
//}
//
////
//// BoxCollider
////
//
// Collider::BoxCollider::BoxCollider(const std::function<void()>& foo)
//    : BaseCollider(foo) {}
//
// bool Collider::BoxCollider::Intersects(const BaseCollider& other) const {
//  if (auto circle = dynamic_cast<const CircleCollider*>(&other)) {
//    return this->IntersectsWithCircle(*circle);
//  }
//  if (auto box = dynamic_cast<const BoxCollider*>(&other)) {
//    return this->IntersectsWithBox(*box);
//  }
//
//  return false;
//}
//
// bool Collider::BoxCollider::IntersectsWithBox(const BoxCollider& other) const
// {
//  Vector2 pos1 = GetPos();
//  float width1 = GetWidth();
//  float height1 = GetHeight();
//
//  Vector2 pos2 = other.GetPos();
//  float width2 = other.GetWidth();
//  float height2 = other.GetHeight();
//
//  float thisLeft = pos1.x;
//  float thisTop = pos1.y;
//  float thisRight = pos1.x + width1;
//  float thisBottom = pos1.y + height1;
//
//  float otherLeft = pos2.x;
//  float otherTop = pos2.y;
//  float otherRight = pos2.x + width2;
//  float otherBottom = pos2.y + height2;
//
//  bool overlapX = thisLeft <= otherRight && otherLeft <= thisRight;
//  bool overlapY = thisTop <= otherBottom && otherTop <= thisBottom;
//
//  return overlapX && overlapY;
//}
//
// bool Collider::BoxCollider::IntersectsWithCircle(
//    const CircleCollider& other) const {
//  Vector2 centre = other.GetCentre();
//  float radius = other.GetRadius();
//
//  Vector2 pos = GetPos();
//  float width = GetWidth();
//  float height = GetHeight();
//
//  float closestX = std::clamp(centre.x, pos.x, pos.x + width);
//  float closestY = std::clamp(centre.y, pos.y, pos.y + height);
//
//  float dx = closestX - centre.x;
//  float dy = closestY - centre.y;
//
//  return dx * dx + dy * dy <= radius * radius;
//}
//
// Vector2 Collider::BoxCollider::GetPos() const {
//  return GetOwner()->GetGlobalTransform().position;
//}
//
// float Collider::BoxCollider::GetWidth() const {
//  return GetOwner()->GetSize().x;
//}
//
// float Collider::BoxCollider::GetHeight() const {
//  return GetOwner()->GetSize().y;
//}
//
////
//// PolygonCollider
////
//
// Collider::PolygonCollider::PolygonCollider(Vector2 centerOffset,
//                                           const std::function<void()>& foo)
//    : BaseCollider(foo), _centerOffset(centerOffset) {}
//
// void Collider::PolygonCollider::AddPoint(Vector2 point) {
//  _localPoints.push_back(point);
//}
//
// std::span<Vector2> Collider::PolygonCollider::GetPoints() {
//  return _globalPoints;
//}
//
// bool Collider::PolygonCollider::IntersectsWithPolygon(
//    const PolygonCollider& other) {
//  UpdatePoints();
//  const std::vector<Vector2>& polyA = _globalPoints;
//  const std::vector<Vector2>& polyB = other._globalPoints;
//
//  auto GetEdgeNormal = [](const Vector2& p1,
//                          const Vector2& p2) -> std::pair<float, float> {
//    float dx = p2.x - p1.x;
//    float dy = p2.y - p1.y;
//    // Ќормаль (перпендикул€р): (-dy, dx)
//    float length = sqrt(dx * dx + dy * dy);
//    return {-dy / length, dx / length};
//  };
//
//  uint32_t nA = polyA.size();
//  uint32_t nB = polyB.size();
//
//  // ѕеребираем все оси нормалей из обоих полигонов
//  for (uint32_t i = 0; i < nA; ++i) {
//    const Vector2& p1 = polyA[i];
//    const Vector2& p2 = polyA[(i + 1) % nA];
//    auto [axisX, axisY] = GetEdgeNormal(p1, p2);
//
//    if (!OverlapOnAxis(polyA, polyB, axisX, axisY))
//      return false;  // раздел€юща€ ось найдена
//  }
//
//  for (uint32_t i = 0; i < nB; ++i) {
//    const Vector2& p1 = polyB[i];
//    const Vector2& p2 = polyB[(i + 1) % nB];
//    auto [axisX, axisY] = GetEdgeNormal(p1, p2);
//
//    if (!OverlapOnAxis(polyA, polyB, axisX, axisY)) return false;
//  }
//
//  // Ќи одной раздел€ющей оси Ч есть пересечение
//  return true;
//}
//
// bool Collider::PolygonCollider::OverlapOnAxis(const std::vector<Vector2>&
// polyA,
//                                              const std::vector<Vector2>&
//                                              polyB, float axisX, float axisY)
//                                              {
//  auto Project = [](const std::vector<Vector2>& poly, float axisX, float
//  axisY,
//                    float& min, float& max) {
//    min = max = (poly[0].x * axisX + poly[0].y * axisY);
//    for (uint32_t i = 1; i < poly.size(); ++i) {
//      float proj = poly[i].x * axisX + poly[i].y * axisY;
//      if (proj < min) min = proj;
//      if (proj > max) max = proj;
//    }
//  };
//
//  float minA, maxA, minB, maxB;
//  Project(polyA, axisX, axisY, minA, maxA);
//  Project(polyB, axisX, axisY, minB, maxB);
//
//  // Ќет перекрыти€ Ч есть раздел€юща€ ось
//  return !(maxA < minB || maxB < minA);
//}
//
// void Collider::PolygonCollider::UpdatePoints() {
//  _globalPoints.clear();
//  Transform transform = GetOwner()->GetGlobalTransform();
//  Vector2 centerObject = GetOwner()->GetGlobalCenter();
//  Vector2 oldPos =
//      (transform.position - centerObject) / transform.scale + centerObject;
//  Vector2 globCenter = oldPos + _centerOffset;
//
//  float cosA = cosf(transform.angle);
//  float sinA = sinf(transform.angle);
//
//  for (const auto& p : _localPoints) {
//    Vector2 pNew = p;
//
//    pNew.x *= transform.scale.x;
//    pNew.y *= transform.scale.y;
//
//    float rotX = pNew.x * cosA - pNew.y * sinA;
//    float rotY = pNew.x * sinA + pNew.y * cosA;
//
//    _globalPoints.push_back(Vector2{rotX, rotY} + globCenter);
//  }
//}
//
// #include <numbers>
//
// Collider::EllipseCollider::EllipseCollider(float a, float b,
//                                           Vector2 centerOffset,
//                                           const std::function<void()>& foo)
//    : PolygonCollider(centerOffset, foo) {
//  for (uint32_t i = 0; i < NumPoints; ++i) {
//    float angle = 2 * i * std::numbers::pi / NumPoints;
//    float x = a * cosf(angle);
//    float y = b * sinf(angle);
//    AddPoint(Vector2{x, y});
//  }
//}