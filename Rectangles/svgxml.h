#pragma once

#include <string>
#include <iostream>
#include <vector>

namespace Svgxml {

  class Attr {
    std::string name_;
    std::string value_;
  public:
    Attr(std::string name, std::string value) : name_(std::move(name)), value_(std::move(value)) {}
    void print(std::ostream& stream) { stream << " " << name_ << "=\"" << value_ << "\""; }
  };

  class Tag {
    std::string name_;
    std::vector<Attr> attr_;
    std::ostream& stream_;
    int indent_;

    void openStart() { stream_ << "<" << name_; }
    void attributes() { for (auto& attr : attr_) attr.print(stream_); }
    void openEnd() { stream_ << ">"; }
    void selfClosing() { stream_ << "/n"; }
    void indent() { stream_ << std::string(indent_, ' '); }
    void openMain() { indent(); openStart(); attributes(); }
  public:
    Tag(std::string name, std::ostream& stream) : name_(std::move(name)), stream_(stream) {}
    void addAttribute(std::string name, std::string value) { attr_.emplace_back(std::move(name), std::move(value)); }
    void open() { openMain();  openEnd(); }
    void openSelfClosing() { openMain(); selfClosing(); }
    void close();
    void setIndent(int indent) { indent_ = indent; }
  };

  void addSVGHeader(std::ostream& stream) {
    stream << "<\? xml version = \"1.0\" standalone = \"no\" \?>\n";
    stream << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
  }

}