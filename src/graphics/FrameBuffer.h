#pragma once
#include <cstdint>

#include "Color.h"

class FrameBuffer {
 private:
  uint32_t* _buffer;
  const uint32_t _width;
  const uint32_t _height;

 public:
  void PutPixel(uint32_t x, uint32_t y, Color c);
  void BlendPixel(uint32_t x, uint32_t y, Color src);
  void Clear(Color c);

  uint32_t GetWidth();
  uint32_t GetHeight();
};
