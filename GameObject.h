#pragma once
#include <memory>
#include <vector>

#include "Utils.h"

class Component;

class GameObject : std::enable_shared_from_this<GameObject> {
 public:
  GameObject(Vector2 pos, float width, float height);

  void Move(Vector2 vec);
  void Rotate(float angle);
  std::shared_ptr<GameObject> GetPtr();

  void AddChild(std::shared_ptr<GameObject> child);

  Vector2 GetLocalPos() const;
  float GetWidth() const;
  float GetHeight() const;
  float GetLocalRotation() const;
  const std::vector<std::shared_ptr<GameObject>>& GetChilds() const;

  Vector2 GetGlobalPos() const;
  float GetGlobalRotation() const;

  void SetParent(std::shared_ptr<GameObject> parent);
  void SetLocalPos(Vector2 pos);
  void SetLocalRotation(float angle);
  void SetWidth(float width);
  void SetHeight(float height);

  template <typename T, typename... Args>
  void AddComponent(Args&&... args);

  template <typename T>
  T* GetComponent() const;

 private:
  Vector2 _pos;
  float _angle;  // rads
  // float _scale; // maybe later

  float _width;
  float _height;

  std::weak_ptr<GameObject> _parent;
  std::vector<std::shared_ptr<GameObject>> _childs;

  std::vector<std::unique_ptr<Component>> _components;
};
