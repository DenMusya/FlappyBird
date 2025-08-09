#pragma once
#include "colliders/BaseCollider.h"
#include "colliders/BoxCollider.h"
#include "colliders/EllipseCollider.h"
#include "colliders/PolygonCollider.h"

// #include <functional>
// #include <memory>
// #include <span>
//
// #include "../core/Component.h"
// #include "../utils/Utils.h"

// class GameObject;
//
// namespace Collider {
//
// class BoxCollider;
// class CircleCollider;
// class PolygonCollider;
//
// class BaseCollider : public Component {
//  public:
//   bool Intersects(const BaseCollider& other) const;
//   virtual ~BaseCollider();
//   void Init() override;
//   void OnCollision();
//   explicit BaseCollider(const std::function<void()>& foo);
//
//  protected:
//   std::function<void()> _onCollision = []() {};
//   virtual bool IntersectsWithBox(const BoxCollider& other) const = 0;
//   virtual bool IntersectsWithCircle(const CircleCollider& other) const = 0;
//   virtual bool IntersectsWithPolygon(const PolygonCollider& other) const = 0;
// };
//
// class CircleCollider : public BaseCollider {
//  public:
//   explicit CircleCollider(
//       float radius, const std::function<void()>& foo = []() {});
//   // bool Intersects(const BaseCollider& other) const override;
//
//   Vector2 GetCentre() const;
//   float GetRadius() const;
//
//  protected:
//   bool ProcessIntersect(const BaseCollider& other) const override;
//   bool IntersectsWithBox(const BoxCollider& other) const override;
//   bool IntersectsWithCircle(const CircleCollider& other) const override;
//   bool IntersectsWithPolygon(const PolygonCollider& other) const override;
//
//  private:
//   float _radius;
// };
//
// class BoxCollider : public BaseCollider {
//  public:
//   explicit BoxCollider(const std::function<void()>& foo = []() {});
//
//   bool Intersects(const BaseCollider& other) const override;
//
//   Vector2 GetPos() const;
//   float GetWidth() const;
//   float GetHeight() const;
//
//  protected:
//   bool ProcessIntersect(const BaseCollider& other) const override;
//   bool IntersectsWithBox(const BoxCollider& other) const override;
//   bool IntersectsWithCircle(const CircleCollider& other) const override;
//   bool IntersectsWithPolygon(const PolygonCollider& other) const override;
// };
//
// class PolygonCollider : public BaseCollider {
//  private:
//   std::vector<Vector2> _localPoints;
//   mutable std::vector<Vector2> _globalPoints;
//   Vector2 _centerOffset;
//   void UpdatePoints();
//
//  public:
//   explicit PolygonCollider(
//       Vector2 centerOffset, const std::function<void()>& foo = []() {});
//   void AddPoint(Vector2 point);
//   std::span<Vector2> GetPoints();
//
//  protected:
//   bool ProcessIntersect(const BaseCollider& other) const override;
//   bool IntersectsWithBox(const BoxCollider& other) const override;
//   bool IntersectsWithCircle(const CircleCollider& other) const override;
//   bool IntersectsWithPolygon(const PolygonCollider& other) const override;
//
//  private:
//   static bool OverlapOnAxis(const std::vector<Vector2>& polyA,
//                             const std::vector<Vector2>& polyB, float axisX,
//                             float axisY);
// };
//
// class EllipseCollider : public PolygonCollider {
//  public:
//   EllipseCollider(
//       float a, float b, Vector2 centerOffset,
//       const std::function<void()>& foo = []() {});
//
//  private:
//   static const uint32_t NumPoints = 16;
// };
//
// }  // namespace Collider