#pragma once
#include <string>

namespace rec {

  struct Vec;
  struct Window;

  // non-member functions

  std::string getString(float number);
  std::string getString(Vec vec);
  std::string getString(Window window);

}  // namespace rec