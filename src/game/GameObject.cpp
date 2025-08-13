#include "GameObject.h"

GameObject::GameObject(Vector2 size, Vector2 pos)
    : _size(size), _transform{pos} {}

void GameObject::Move(Vector2 vec) { _transform.position += vec; }

void GameObject::SetPosition(Vector2 pos, PivotType pivot) {
  _transform.position = pos + GetPivotOffset(pivot);
}

void GameObject::Rotate(float angle) { _transform.angle += angle; }

void GameObject::Scale(float scale) {
  Vector2 center = GetGlobalCenter();
  _transform.scale *= scale;
  SetPosition(center, PivotType::Center);
}

void GameObject::ScaleX(float scale) {
  Vector2 center = GetGlobalCenter();
  _transform.scale.x *= scale;
  SetPosition(center, PivotType::Center);
}

void GameObject::ScaleY(float scale) {
  Vector2 center = GetGlobalCenter();
  _transform.scale.y *= scale;
  SetPosition(center, PivotType::Center);
}

void GameObject::SetRotation(float angle) { _transform.angle = angle; }

void GameObject::AddChild(std::shared_ptr<GameObject> child) {
  _childs.push_back(child);
  _cacheValid = false;
}

Vector2 GameObject::GetSize() const {
  return Vector2{_size.x * _transform.scale.x, _size.y * _transform.scale.y};
}
Transform GameObject::GetLocalTransform() const { return _transform; }
Transform GameObject::GetGlobalTransform() const {
  if (_parent.expired()) {
    return GetLocalTransform();
  }

  return GetLocalTransform() + _parent.lock()->GetGlobalTransform();
}

std::span<GameObject*> GameObject::GetChilds() const {
  UpdateCache();
  return {_childsCache.data(), _childs.size()};
}

Vector2 GameObject::GetGlobalCenter() const {
  return GetGlobalTransform().position + 0.5f * GetSize();
}

Vector2 GameObject::GetLocalCenter() const { return 0.5f * GetSize(); }

GameObject* GameObject::GetRootParent() {
  if (_parent.expired()) return this;
  return _parent.lock()->GetRootParent();
}

void GameObject::SetLocalTransform(Transform transform) {
  _transform = transform;
}
void GameObject::SetSize(Vector2 size) { _size = size; }

void GameObject::UpdateCache() const {
  if (_cacheValid) return;

  _childsCache.clear();
  _childsCache.reserve(_childs.size());
  for (const auto& child : _childs) {
    _childsCache.push_back(child.get());
  }
  _cacheValid = true;
}

void GameObject::Init() {
  for (auto& child : _childs) {
    child->_parent = shared_from_this();
    child->Init();
  }

  for (auto& component : _components) {
    component->SetOwner(shared_from_this());
  }
}

Vector2 GameObject::GetPivotOffset(PivotType pivot) const {
  switch (pivot) {
    case PivotType::TopLeft:
      return Vector2(0, 0);
    case PivotType::TopCenter:
      return Vector2(-GetSize().x / 2, 0);
    case PivotType::TopRight:
      return Vector2(-GetSize().x, 0);
    case PivotType::CenterLeft:
      return Vector2(0, -GetSize().y / 2);
    case PivotType::Center:
      return Vector2(-GetSize().x / 2, -GetSize().y / 2);
    case PivotType::CenterRight:
      return Vector2(-GetSize().x, -GetSize().y / 2);
    case PivotType::BottomLeft:
      return Vector2(0, -GetSize().y);
    case PivotType::BottomCenter:
      return Vector2(-GetSize().x / 2, -GetSize().y);
    case PivotType::BottomRight:
      return Vector2(-GetSize().x, -GetSize().y);
    default:
      return Vector2(0, 0);
  }
}