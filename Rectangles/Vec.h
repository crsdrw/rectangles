#pragma once

namespace rec {

  struct Vec {
    float x;
    float y;
    Vec(float X, float Y) : x(X), y(Y) {}
  };

  Vec operator+(Vec lhs, Vec rhs) { return Vec(lhs.x + rhs.x, lhs.y + rhs.y); }
  bool operator>(Vec lhs, Vec rhs) { return lhs.x > rhs.x && lhs.y > rhs.y; }
  bool operator<(Vec lhs, Vec rhs) { return lhs.x < rhs.x && lhs.y < rhs.y; }

}