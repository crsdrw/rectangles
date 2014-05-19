#include "stdafx.h"
#include "StringTools.h"

#include <sstream>
#include "Vec.h"
#include "Window.h"

namespace rec {

  std::string getString(float number) {
    std::stringstream s;
    s << number;
    return s.str();
  }

  std::string getString(Vec vec) {
    return "{ x=" + getString(vec.x) + ", y=" + getString(vec.y) + "}";
  }

  std::string getString(Window window) {
    return "{ pos=" + getString(window.pos) + ", size=" + getString(window.size) + "}";
  }

}  // namespace rec
