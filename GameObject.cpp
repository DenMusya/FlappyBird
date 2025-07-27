#include "GameObject.h"

GameObject::GameObject(Vector2 pos, float width, float height)
    : _pos(pos), _width(width), _height(height), _angle(0.0f) {}

void GameObject::Move(Vector2 vec) { _pos += vec; }

void GameObject::Rotate(float angle) { _angle += angle; }

std::shared_ptr<GameObject> GameObject::GetPtr() { return shared_from_this(); }

void GameObject::AddChild(std::shared_ptr<GameObject> child) {
  _childs.push_back(child);
  child->SetParent(GetPtr());
}

void GameObject::SetParent(std::shared_ptr<GameObject> parent) {
  _parent = parent;
}

Vector2 GameObject::GetLocalPos() const { return _pos; }
float GameObject::GetLocalRotation() const { return _angle; }
float GameObject::GetWidth() const { return _width; }
float GameObject::GetHeight() const { return _height; }
const std::vector<std::shared_ptr<GameObject>>& GameObject::GetChilds() const {
  return _childs;
}

Vector2 GameObject::GetGlobalPos() const {
  if (_parent.expired()) {
    return _pos;
  }

  return _pos + _parent.lock()->GetGlobalPos();
}

float GameObject::GetGlobalRotation() const {
  if (_parent.expired()) {
    return _angle;
  }

  return _angle + _parent.lock()->GetGlobalRotation();
}

void GameObject::SetLocalPos(Vector2 pos) { _pos = pos; }
void GameObject::SetLocalRotation(float angle) { _angle = angle; }
void GameObject::SetWidth(float width) { _width = width; }
void GameObject::SetHeight(float height) { _height = height; }

template <typename T, typename... Args>
void GameObject::AddComponent(Args&&... args) {
  static_assert(std::is_base_of_v<Component, T>,
                "T must inherit from Component");

  if (GetComponent<T>()) {
    return;
  }

  _components.emplace_back(std::forward<Args>(args)...);
}

template <typename T>
T* GameObject::GetComponent() const {
  for (auto& comp : _components) {
    if (auto ptr = dynamic_cast<T*>(comp.get())) {
      return ptr;
    }
  }
  return nullptr;
}