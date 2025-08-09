#pragma once
#include <memory>
#include <span>
#include <vector>

#include "../core/Component.h"
#include "../utils/Utils.h"

enum class PivotType {
  TopLeft,
  TopCenter,
  TopRight,
  CenterLeft,
  Center,
  CenterRight,
  BottomLeft,
  BottomCenter,
  BottomRight
};

class GameObject : public std::enable_shared_from_this<GameObject> {
 protected:
  Transform _transform = Transform{};
  Vector2 _size = Vector2::Zero;

 public:
  template <typename Derived, typename... Args>
  static std::shared_ptr<Derived> Create(Args&&... args);

  void Move(Vector2 vec);
  void SetPosition(Vector2 pos, PivotType pivot = PivotType::TopLeft);

  void Rotate(float angle);
  void Scale(float scale);
  void ScaleX(float scaleX);
  void ScaleY(float scaleY);

  void AddChild(std::shared_ptr<GameObject> child);
  std::span<GameObject*> GetChilds() const;

  Vector2 GetSize() const;

  Transform GetLocalTransform() const;
  Transform GetGlobalTransform() const;

  Vector2 GetGlobalCenter() const;
  Vector2 GetLocalCenter() const;

  GameObject* GetRootParent();

  void SetLocalTransform(Transform transform);
  void SetSize(Vector2 size);

  template <typename T, typename... Args>
  void AddComponent(Args&&... args);

  template <typename T>
  T* GetComponent() const;

 protected:
  GameObject() = default;
  GameObject(Vector2 size, Vector2 pos = Vector2::Zero);
  void Init();
  std::weak_ptr<GameObject> _parent;

 private:
  std::vector<std::shared_ptr<GameObject>> _childs;
  std::vector<std::shared_ptr<Component>> _components;
  mutable std::vector<GameObject*> _childsCache;
  mutable bool _cacheValid = false;

  Vector2 GetPivotOffset(PivotType pivot) const;
  void UpdateCache() const;
};

template <typename T>
T* GameObject::GetComponent() const {
  for (auto& comp : _components) {
    if (auto ptr = dynamic_cast<T*>(comp.get())) {
      return ptr;
    }
  }
  return nullptr;
}

template <typename T, typename... Args>
void GameObject::AddComponent(Args&&... args) {
  static_assert(std::is_base_of_v<Component, T>,
                "T must inherit from Component");

  if (GetComponent<T>()) {
    return;
  }

  auto ptr = Component::Create<T>(std::forward<Args>(args)...);
  // ptr->SetOwner(shared_from_this());
  _components.push_back(ptr);
}

template <typename Derived, typename... Args>
std::shared_ptr<Derived> GameObject::Create(Args&&... args) {
  static_assert(std::is_base_of_v<GameObject, Derived>,
                "Must inherit from GameObject");

  struct DerivedImpl : public Derived {
    DerivedImpl(Args&&... args) : Derived(std::forward<Args>(args)...) {}
  };

  auto obj = std::make_shared<DerivedImpl>(std::forward<Args>(args)...);
  obj->Init();
  return obj;
}