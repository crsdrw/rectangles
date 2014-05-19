#include "stdafx.h"
#include "Window.h"

namespace {
  using rec::Window;
  using rec::Vec;

  void growWindowMin(Window& window, Vec p) {
    Vec offset = getMax(window) - p;
    if (offset.x > window.size.x) {
      window.size.x = offset.x;
      window.pos.x = p.x;
    }
    if (offset.y > window.size.y) {
      window.size.y = offset.y;
      window.pos.y = p.y;
    }
  }

  void growWindowMax(Window& window, Vec p) {
    Vec offset = p - window.pos;
    if (offset.x > window.size.x)
      window.size.x = offset.x;
    if (offset.y > window.size.y)
      window.size.y = offset.y;
  }
}  // namespace

namespace rec {
  void
  growWindow(Window& window, const Window& sub) {
    growWindowMin(window, sub.pos);
    growWindowMax(window, getMax(sub));
  }
}  // namespace rec
