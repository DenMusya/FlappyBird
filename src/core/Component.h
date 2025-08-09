#pragma once

#include <memory>

class GameObject;

class Component {
 public:
  virtual ~Component() = default;
  virtual void Init() = 0;

  std::shared_ptr<GameObject> GetOwner() const;
  void SetOwner(std::shared_ptr<GameObject> owner);

  template <typename Derived, typename... Args>
  static std::shared_ptr<Derived> Create(Args&&... args);

 private:
  std::weak_ptr<GameObject> _owner;
};

template <typename Derived, typename... Args>
std::shared_ptr<Derived> Component::Create(Args&&... args) {
  static_assert(std::is_base_of_v<Component, Derived>,
                "Must inherit from GameObject");

  struct DerivedImpl : public Derived {
    DerivedImpl(Args&&... args) : Derived(std::forward<Args>(args)...) {}
  };

  auto obj = std::make_shared<DerivedImpl>(std::forward<Args>(args)...);
  obj->Init();
  return obj;
}