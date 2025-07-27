#include "GameObject.h"

#include "Collider.h"

GameObject::GameObject(Vector2 pos, float width, float height,
                       std::unique_ptr<Collider::BaseCollider> collider)
    : _pos(pos),
      _width(width),
      _height(height),
      _collider(std::move(collider)) {}

void GameObject::Move(Vector2 vec) { _pos += vec; }

void GameObject::Rotate(float angle) { _angle += angle; }

void GameObject::Init() { _collider->SetGameObject(GetPtr()); }

std::shared_ptr<GameObject> GameObject::GetPtr() { return shared_from_this(); }

const std::unique_ptr<Collider::BaseCollider>& GameObject::GetCollider() const {
  return _collider;
}

Vector2 GameObject::GetPos() const { return _pos; }
float GameObject::GetWidth() const { return _width; }
float GameObject::GetHeight() const { return _height; }
float GameObject::GetRotation() const { return _angle; }

void GameObject::SetPos(Vector2 pos) { _pos = pos; }
void GameObject::SetWidth(float width) { _width = width; }
void GameObject::SetHeight(float height) { _height = height; }
void GameObject::SetRotation(float angle) { _angle = angle; }