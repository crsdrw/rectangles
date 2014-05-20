#include "stdafx.h"
#include "StringTools.h"

#include <string>
#include <sstream>
#include "Vec.h"
#include "Window.h"
#include <wstring>

namespace rec {

  std::wstring getWString(float number) {
    std::wstringstream s;
    s << number;
    return s.str();
  }

  std::string getString(float number) {
    std::stringstream s;
    s << number;
    return s.str();
  }

  std::string getString(Vec vec) {
    return "{ x=" + getString(vec.x) + ", y=" + getString(vec.y) + "}";
  }

  std::wstring getWString(Vec vec) {
    return L"{ x=" + getWString(vec.x) + L", y=" + getWString(vec.y) + L"}";
  }

  std::string getString(Window window) {
    return "{ pos=" + getString(window.pos) + ", size=" + getString(window.size) + "}";
  }

  std::wstring getWString(Window window) {
    return L"{ pos=" + getWString(window.pos) + L", size=" + getWString(window.size) + L"}";
  }

}  // namespace rec
