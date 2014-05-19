#include "stdafx.h"
#include "Window.h"

namespace {
  using rec::Window;
  using rec::Vec;

  void growWindowPos(Window& window, Vec p) {
    if (p.x < window.pos.x)
      window.pos.x = p.x;
    if (p.y < window.pos.y)
      window.pos.y = p.y;
  }

  void growWindowSize(Window& window, Vec p) {
    if (p.x > window.size.x)
      window.size.x = p.x;
    if (p.y > window.size.y)
      window.size.y = p.y;
  }
}  // namespace

namespace rec {
  void
  growWindow(Window& window, const Window& sub) {
    growWindowPos(window, sub.pos);
    Vec offset = getMax(sub) - window.pos;
    growWindowSize(window, offset);
  }
}  // namespace rec
