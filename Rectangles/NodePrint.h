#pragma once

#include <iosfwd>

namespace rec {
  class Node;

  void print(const Node& root, std::ostream& stream);
}
