#pragma once

#include <cmath>

namespace rec {

  inline bool areAlmostEqual(float x, float y, float eps) { return std::abs(x - y) <= eps * std::abs(x); }

  struct Vec {
    float x;
    float y;
  };

  inline Vec operator+(Vec lhs, Vec rhs) { return Vec{ lhs.x + rhs.x, lhs.y + rhs.y }; }
  inline Vec operator-(Vec lhs, Vec rhs) { return Vec{ lhs.x - rhs.x, lhs.y - rhs.y }; }
  inline bool operator>(Vec lhs, Vec rhs) { return lhs.x > rhs.x && lhs.y > rhs.y; }
  inline bool operator<(Vec lhs, Vec rhs) { return lhs.x < rhs.x && lhs.y < rhs.y; }
  inline bool operator>=(Vec lhs, Vec rhs) { return lhs.x >= rhs.x && lhs.y >= rhs.y; }
  inline bool operator<=(Vec lhs, Vec rhs) { return lhs.x <= rhs.x && lhs.y <= rhs.y; }
  inline Vec operator/(Vec lhs, float rhs) { return Vec{ lhs.x / rhs, lhs.y / rhs }; }

  inline bool areAlmostEqual(Vec lhs, Vec rhs, float eps) {
    return areAlmostEqual(lhs.x, rhs.x, eps) && areAlmostEqual(lhs.y, rhs.y, eps);
  }

}  // namespace rec
