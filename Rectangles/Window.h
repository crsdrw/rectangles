#pragma once

#include "Vec.h"

namespace rec {

  struct Window {
    Vec pos;
    Vec size;
  };

  // inline non-member functions
  inline Vec getMax(const Window& window) { return window.pos + window.size; }
  inline float getMaxX(const Window& window) { return window.pos.x + window.size.x; }
  inline float getMaxY(const Window& window) { return window.pos.y + window.size.y; }
  inline Vec getCentre(const Window& window) { return window.pos + window.size / 2; }
  inline bool isColision(const Window& window, Vec p) { return p > window.pos && p < getMax(window); }
  inline bool areAlmostEqual(const Window& lhs, const Window& rhs, float eps) {
    return rec::areAlmostEqual(lhs.pos, rhs.pos, eps) && rec::areAlmostEqual(lhs.size, rhs.size, eps);
  }

  // non-member functions
  void growWindow(Window& window, const Window& sub);
}  // namespace rec
