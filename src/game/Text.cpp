#include "Text.h"

#include "../core/Component.h"
#include "../graphics/Visuals.h"
#include "../utils/Utils.h"

Text::Text(const TextConfig& config, const std::string& str)
    : GameObject(Vector2::Zero, config.pos), _str(str), Config(config) {
  Scale(Config.scale);
}

Text& Text::operator=(const std::string& str) {
  _str = str;
  return *this;
}

void Text::DrawChar(Vector2 pos, char c, Vector2 scale) {
  for (int row = 0; row < Config.symbolSize.y; ++row) {
    uint8_t bits = GetCharSprite(c)[row];
    for (int col = 0; col < Config.symbolSize.x; ++col) {
      if (bits & (1 << (Config.symbolSize.x - 1 - col))) {
        for (int dy = 0; dy < scale.y; ++dy) {
          for (int dx = 0; dx < scale.x; ++dx) {
            ColorPixel(pos.x + col * scale.x + dx, pos.y + row * scale.y + dy,
                       Config.color.GetARGB());
          }
        }
      }
    }
  }
}

void Text::Draw() {
  Transform tranform = GetGlobalTransform();
  Vector2 pos = tranform.position;
  for (char c : _str) {
    DrawChar(pos, c, tranform.scale);
    if (c == ':' || c == ' ') {  // TODO
      pos += tranform.scale * Vector2{Config.symbolSize.x + 1.0f, 0} * 0.5f;
      continue;
    }
    pos += tranform.scale * Vector2{Config.symbolSize.x + 1.0f, 0};
  }
}

const uint8_t* Text::GetCharSprite(char c) const {
  if (c >= 'A' && c <= 'Z') {
    return Visuals::Symbols[c - 'A'];
  }
  if (c >= 'a' && c <= 'z') {
    return Visuals::Symbols[c - 'a'];
  }
  if (c >= '0' && c <= '9') {
    return Visuals::Symbols[26 + (c - '0')];
  }
  if (c == ' ') {
    return Visuals::Symbols[36];
  }

  if (c == ':') {
    return Visuals::Symbols[37];
  }
  return nullptr;
}