#pragma once
#include "Movable.h"
#include "Drawable.h"
#include "Utils.h"
#include <string>
// 
class Text : Drawable, Movable
{
public:
  void draw() override;
  void move(Vector2 delta) override;

  void DrawChar(Vector2 pos, char c);
  Text() = default;
  Text(const std::string& str, Vector2 pivot, uint32_t scale);
  Text& operator=(const std::string& str);
private:
  uint32_t _scale = 3;
  Vector2 _pivot;
  std::string _str;
  uint32_t color = Color::Black;
  
  static const uint32_t CharWidth = 5;
  static const uint32_t CharHeight = 7;
};



