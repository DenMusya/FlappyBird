#pragma once

#include <memory>

class GameObject;

class Component {
 public:
  virtual ~Component() = default;

  std::shared_ptr<GameObject> GetOwner() const;
  void SetOwner(std::shared_ptr<GameObject> owner);

 private:
  std::weak_ptr<GameObject> _owner;
};
