#pragma once
#include <cstdint>

class Font {
 public:
  static const uint8_t* get(char c);
 private:
  static const uint8_t _data[38][7];
};

