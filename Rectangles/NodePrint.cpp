#include "stdafx.h"
#include "NodePrint.h"
#include "Node.h"
#include "svgxml.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

namespace {
  static const float PRINT_SIZE = 500.0f;

  std::string getString(float number) {
    std::stringstream s;
    s << number;
    return s.str();
  }

  std::string getWidth(const rec::Node& rectangle) {
    return getString(rectangle.getSize().x);
  }

  std::string getHeight(const rec::Node& rectangle) {
    return getString(rectangle.getSize().y);
  }

  std::string getX(const rec::Node& rectangle) {
    return getString(rectangle.getPos().x);
  }
  
  std::string getY(const rec::Node& rectangle) {
    return getString(rectangle.getPos().y);
  }

  float getAspectRation(const rec::Node& root) {
    float width = root.getSize().x;
    return width > 0 ? root.getSize().y / width : 1.0f;
  }

  std::string getViewBox(const rec::Node& root) {
    return "0 0 " + getWidth(root) + " " + getHeight(root);
  }

  float getScale(const rec::Node& root) {
    return root.getSize().x / PRINT_SIZE;
  }

}

namespace rec {
  void print(const Node& root, std::ostream& stream) {
    Svgxml::addSVGHeader(stream);
    { // <svg>
      Svgxml::Tag svg("svg", stream);
      svg.addAttribute("width", getString(PRINT_SIZE * getAspectRation(root)) + "px");
      svg.addAttribute("height", getString(PRINT_SIZE) + "px");
      svg.addAttribute("viewBox", getViewBox(root));
      svg.addAttribute("version", "1.1");
      svg.addAttributeOnNewline("xmlns", "http://www.w3.org/2000/svg");
      svg.open();

      float scale = getScale(root);

      std::vector<const Node*> rectangles = root.findLeaves();
      for (auto rectangle : rectangles) { // <rect/>
        Svgxml::Tag rect("rect", stream);
        rect.addAttribute("x", getX(*rectangle));
        rect.addAttribute("y", getY(*rectangle));
        rect.addAttribute("width", getWidth(*rectangle));
        rect.addAttribute("height", getHeight(*rectangle));
        rect.addAttribute("fill", "none");
        rect.addAttribute("stroke-width", getString(scale * 1.5f));
        rect.addAttribute("stroke", "black");
        rect.setIndent(2);
        rect.openSelfClosing();
      }
    } // </svg> 
  }
}