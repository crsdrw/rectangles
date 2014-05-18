#pragma once

#include "Vec.h"

namespace rec {

  struct Window {
    Vec pos;
    Vec size;
  };

  // inline non-member functions
  inline Vec getMax(const Window& window) { return window.pos + window.size; }
  inline Vec getCentre(const Window& window) { return window.pos + window.size / 2; }
  inline bool isColision(const Window& window, Vec p) { return p > window.pos && p < getMax(window); }

  // non-member functions
  void growWindow(Window& window, const Window& sub);
}  // namespace rec
