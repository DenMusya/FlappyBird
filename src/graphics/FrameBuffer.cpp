#include "FrameBuffer.h"

#include <algorithm>

#include "../core/Engine.h"

void FrameBuffer::PutPixel(uint32_t x, uint32_t y, Color c) {
  if (x >= _width || y >= _height) return;
  _buffer[x + y * _width] = c.GetARGB();
}

void FrameBuffer::BlendPixel(uint32_t x, uint32_t y, Color src) {
  if (x >= _width || y >= _height) return;
  Color curColor(_buffer[x + y * _width], ColorFormat::ARGB);

  float alpha = src.a / 255.0f;

  curColor.r = static_cast<uint8_t>((1 - alpha) * curColor.r + alpha * src.r);
  curColor.g = static_cast<uint8_t>((1 - alpha) * curColor.g + alpha * src.g);
  curColor.b = static_cast<uint8_t>((1 - alpha) * curColor.b + alpha * src.b);
  curColor.a =
      static_cast<uint8_t>(((1 - alpha) * curColor.a + alpha * src.a * 255.0f));

  _buffer[x + y * _width] = curColor.GetARGB();
}

void FrameBuffer::Clear(Color c) {
  std::fill(_buffer, _buffer + _width * _height, c.GetARGB());
}

uint32_t FrameBuffer::GetWidth() { return _width; }
uint32_t FrameBuffer::GetHeight() { return _height; }