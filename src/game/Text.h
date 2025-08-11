#pragma once
#include <string>

#include "../graphics/Color.h"
#include "../utils/Config.h"
#include "../utils/Utils.h"
#include "GameObject.h"

class Text : public GameObject {
 public:
  void Draw();

  Text(const TextConfig& config, const std::string& str = "");
  Text& operator=(const std::string& str);

 private:
  void DrawChar(Vector2 pos, char c, Vector2 scale);

  const uint8_t* GetCharSprite(char c) const;
  Text() = default;
  const TextConfig Config;
  std::string _str;
};
