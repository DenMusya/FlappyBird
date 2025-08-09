#pragma once

#include <cstdint>

#include "../core/Component.h"
#include "../utils/Utils.h"

class Sprite : public Component {
 public:
  void Draw();

  void Init() override;

  ~Sprite();

 protected:
  Sprite(Vector2u size, const uint32_t* sprite);

 private:
  Sprite() = delete;
  Vector2u _size;
  const uint32_t* _sprite;
};