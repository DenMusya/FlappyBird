#pragma once
#include <numbers>

#include "../graphics/Sprite.h"
#include "../utils/Config.h"
#include "../utils/Utils.h"
#include "FeatherSpawner.h"
#include "GameObject.h"
#include "Pipe.h"

class Bird : public GameObject {
 private:
  Sprite* _baseSprite = nullptr;
  Sprite* _deadSprite = nullptr;

  const BirdConfig Config;
  float _velocityY = 0.0f;
  std::shared_ptr<FeatherSpawner> _featherSpawner = nullptr;
  bool _isDead = false;

 public:
  Bird(const BirdConfig& config);

  bool IsFinished(const Pipe& pipe) const;
  bool OutMap() const;

  void OnDead();
  void Reset();
  void Update(float dt);
  void Jump();
  bool IsDead() const;
};
