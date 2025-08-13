#pragma once

#include <cstdint>
#include <string>

#include "../core/Component.h"
#include "../utils/Utils.h"

class Sprite : public Component {
 public:
  void Draw();
  Vector2u GetSize() const;

  void Init() override;

  ~Sprite();

 protected:
  Sprite(const std::string& path);

 private:
  void FastDraw();
  Color GetColor(int x, int y);
  Sprite() = delete;
  Vector2u _size = Vector2u::Zero;
  uint32_t* _sprite;
  // unsigned char* _sprite = nullptr;
};