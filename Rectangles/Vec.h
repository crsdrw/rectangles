#pragma once

namespace rec {

  struct Vec {
//    Vec(float X, float Y) : x(X), y(Y) {}
    float x;
    float y;
  };

  inline Vec operator+(Vec lhs, Vec rhs) { return Vec{ lhs.x + rhs.x, lhs.y + rhs.y }; }
  inline bool operator>(Vec lhs, Vec rhs) { return lhs.x > rhs.x && lhs.y > rhs.y; }
  inline bool operator<(Vec lhs, Vec rhs) { return lhs.x < rhs.x && lhs.y < rhs.y; }
  inline bool operator==(Vec lhs, Vec rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
}