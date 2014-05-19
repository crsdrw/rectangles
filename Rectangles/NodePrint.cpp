#include "stdafx.h"
#include "NodePrint.h"
#include "Node.h"
#include "svgxml.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

namespace {
  const float PRINT_SIZE = 500.0f;

  // local helper functions
  std::string getString(float number) {
    std::stringstream s;
    s << number;
    return s.str();
  }

  std::string getWidth(const rec::Window& window) {
    return getString(window.size.x);
  }

  std::string getHeight(const rec::Window& window) {
    return getString(window.size.y);
  }

  std::string getX(const rec::Window& window) {
    return getString(window.pos.x);
  }

  std::string getY(const rec::Window& window) {
    return getString(window.pos.y);
  }

  float getAspectRation(const rec::Window& window) {
    float width = window.size.x;
    return width > 0 ? window.size.y / width : 1.0f;
  }

  std::string getViewBox(const rec::Window& window) {
    return "0 0 " + getWidth(window) + " " + getHeight(window);
  }

  float getScale(const rec::Window& window) {
    return window.size.x / PRINT_SIZE;
  }

  void
  fillSvgTag(Svgxml::Tag& svg, const rec::Window& rectangle) {
    svg.addAttribute("width", getString(PRINT_SIZE * getAspectRation(rectangle)) + "px");
    svg.addAttribute("height", getString(PRINT_SIZE) + "px");
    svg.addAttribute("viewBox", getViewBox(rectangle));
    svg.addAttribute("version", "1.1");
    svg.addAttributeOnNewline("xmlns", "http://www.w3.org/2000/svg");
    svg.open();
  }

  void
  fillRectTag(Svgxml::Tag &rect, const rec::Window& rectangle, float scale) {
    rect.addAttribute("x", getX(rectangle));
    rect.addAttribute("y", getY(rectangle));
    rect.addAttribute("width", getWidth(rectangle));
    rect.addAttribute("height", getHeight(rectangle));
    rect.addAttribute("fill", "none");
    rect.addAttribute("stroke-width", getString(scale * 1.5f));
    rect.addAttribute("stroke", "black");
    rect.setIndent(2);
    rect.openSelfClosing();
  }

}  // namespace

namespace rec {

  // public non-member functions
  void print(const Node& root, std::ostream& stream) {
    Svgxml::addSVGHeader(stream);
    { // <svg>
      Svgxml::Tag svg("svg", stream);
      const Window bounding_box = root.getWindow();
      fillSvgTag(svg, bounding_box);

      float scale = getScale(bounding_box);

      std::vector<Window> rectangles = root.findLeaves();
      for (auto rectangle : rectangles) {  // <rect/>
        Svgxml::Tag rect("rect", stream);
        fillRectTag(rect, rectangle, scale);
      }
    }  // </svg>
  }
}  // namespace rec
