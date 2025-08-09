#include "PolygonCollider.h"

#include "../../game/GameObject.h"
#include "BaseCollider.h"

Collider::PolygonCollider::PolygonCollider(Vector2 centerOffset,
                                           const std::function<void()>& foo)
    : BaseCollider(foo), _centerOffset(centerOffset) {}

bool Collider::PolygonCollider::Intersects(const BaseCollider& other) const {
  if (auto it = dynamic_cast<const PolygonCollider*>(&other)) {
    return IntersectsWithPolygon(*it);
  }
  return false;
}

void Collider::PolygonCollider::AddPoint(Vector2 point) {
  _localPoints.push_back(point);
}

std::span<Vector2> Collider::PolygonCollider::GetPoints() const {
  return _globalPoints;
}

bool Collider::PolygonCollider::IntersectsWithPolygon(
    const PolygonCollider& other) const {
  UpdatePoints();
  const std::vector<Vector2>& polyA = _globalPoints;
  const std::vector<Vector2>& polyB = other._globalPoints;

  auto GetEdgeNormal = [](const Vector2& p1,
                          const Vector2& p2) -> std::pair<float, float> {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    // Ќормаль (перпендикул€р): (-dy, dx)
    float length = sqrt(dx * dx + dy * dy);
    return {-dy / length, dx / length};
  };

  uint32_t nA = polyA.size();
  uint32_t nB = polyB.size();

  // ѕеребираем все оси нормалей из обоих полигонов
  for (uint32_t i = 0; i < nA; ++i) {
    const Vector2& p1 = polyA[i];
    const Vector2& p2 = polyA[(i + 1) % nA];
    auto [axisX, axisY] = GetEdgeNormal(p1, p2);

    if (!OverlapOnAxis(polyA, polyB, axisX, axisY))
      return false;  // раздел€юща€ ось найдена
  }

  for (uint32_t i = 0; i < nB; ++i) {
    const Vector2& p1 = polyB[i];
    const Vector2& p2 = polyB[(i + 1) % nB];
    auto [axisX, axisY] = GetEdgeNormal(p1, p2);

    if (!OverlapOnAxis(polyA, polyB, axisX, axisY)) return false;
  }

  // Ќи одной раздел€ющей оси Ч есть пересечение
  return true;
}

bool Collider::PolygonCollider::OverlapOnAxis(const std::vector<Vector2>& polyA,
                                              const std::vector<Vector2>& polyB,
                                              float axisX, float axisY) {
  auto Project = [](const std::vector<Vector2>& poly, float axisX, float axisY,
                    float& min, float& max) {
    min = max = (poly[0].x * axisX + poly[0].y * axisY);
    for (uint32_t i = 1; i < poly.size(); ++i) {
      float proj = poly[i].x * axisX + poly[i].y * axisY;
      if (proj < min) min = proj;
      if (proj > max) max = proj;
    }
  };

  float minA, maxA, minB, maxB;
  Project(polyA, axisX, axisY, minA, maxA);
  Project(polyB, axisX, axisY, minB, maxB);

  // Ќет перекрыти€ Ч есть раздел€юща€ ось
  return !(maxA < minB || maxB < minA);
}

void Collider::PolygonCollider::UpdatePoints() const {
  _globalPoints.clear();
  Transform transform = GetOwner()->GetGlobalTransform();
  Vector2 centerObject = GetOwner()->GetGlobalCenter();
  Vector2 oldPos =
      (transform.position - centerObject) / transform.scale + centerObject;
  Vector2 globCenter = oldPos + _centerOffset;

  float cosA = cosf(-transform.angle);
  float sinA = sinf(-transform.angle);

  for (const auto& p : _localPoints) {
    Vector2 pNew = p;

    pNew.x *= transform.scale.x;
    pNew.y *= transform.scale.y;

    float rotX = pNew.x * cosA - pNew.y * sinA;
    float rotY = pNew.x * sinA + pNew.y * cosA;

    _globalPoints.push_back(Vector2{rotX, rotY} + globCenter);
  }
}

void Collider::PolygonCollider::Draw() const {
  static int dx[] = {1, 1, 1, -1, -1, -1, 0, 0, 0};
  static int dy[] = {0, -1, 1, -1, 1, 0, 1, -1, 0};
  for (auto p : _globalPoints) {
    for (int i = 0; i < 8; ++i) {
      ColorPixel(roundf(p.x) + dx[i], roundf(p.y) + dy[i], 0xd3ae37);
    }
    ColorPixel(roundf(p.x), roundf(p.y), 0x0);
  }
}