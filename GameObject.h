#pragma once
#include <memory>

// #include "Collider.h"
#include "Utils.h"

namespace Collider {
class BaseCollider;
}

class GameObject : std::enable_shared_from_this<GameObject> {
 public:
  GameObject(Vector2 pos, float width, float height,
             std::unique_ptr<Collider::BaseCollider> collider);

  void Move(Vector2 vec);
  void Rotate(float angle);
  void Init();
  std::shared_ptr<GameObject> GetPtr();
  const std::unique_ptr<Collider::BaseCollider>& GetCollider() const;

  Vector2 GetPos() const;
  float GetWidth() const;
  float GetHeight() const;
  float GetRotation() const;

  void SetPos(Vector2 pos);
  void SetWidth(float width);
  void SetHeight(float height);
  void SetRotation(float angle);

  virtual ~GameObject() = default;

 private:
  Vector2 _pos;
  float _width;
  float _height;
  float _angle;  // rads

  std::unique_ptr<Collider::BaseCollider> _collider;
};
