#include "stdafx.h"
#include "NodePrint.h"
#include "Node.h"
#include "svgxml.h"
#include <iostream>
#include <string>
#include <vector>

namespace rec {
  void print(const Node& root, std::ostream& stream) {
    Svgxml::addSVGHeader(stream);
    Svgxml::Tag svg("svg", stream);
    svg.addAttribute("width", "5cm");
    svg.addAttribute("height", "4cm");
    svg.addAttribute("version", "1.1");
    svg.addAttribute("xmlns", "http://www.w3.org/2000/svg");
    svg.open();

    std::vector<const Node*> rectangles = root.findLeaves();
    for (auto& rectangle : rectangles) {
      Svgxml::Tag rect("rect", stream);
      rect.addAttribute("x", "0.5cm");
      rect.addAttribute("y", "0.5cm");
      rect.addAttribute("width", "2cm");
      rect.addAttribute("height", "1cm");
      rect.openSelfClosing();
    }
  }
}