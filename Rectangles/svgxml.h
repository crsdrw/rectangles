#pragma once

#include <string>
#include <iostream>
#include <vector>

namespace Svgxml {
  class Element {
    protected:
      std::string   name_;
      int           indent_;
      std::ostream& stream_;
      void indent() { stream_ << std::string(indent_, ' '); }
    public:
      Element(std::string name, std::ostream& stream) : name_(std::move(name)), stream_(stream), indent_(0) {}
      void setIndent(int indent) { indent_ = indent; }
      Element& operator=(const Element&) = delete;
  };

  class Attr : public Element {
    std::string value_;
    bool        newline_;
    public:
      Attr(std::string name, std::string value, std::ostream& stream) : Element(std::move(name), stream), value_(std::move(value)), newline_(false) {}
      void setNewLine() { newline_ = true; }
      void print();
  };

  void Attr::print() {
    if (newline_) {
      stream_ << "\n";
      indent();
    } else {
      stream_ << " ";
    }
    stream_ << name_ << "=\"" << value_ << "\"";
  }

  class Tag : public Element {
    std::vector<Attr> attr_;
    bool open_;
    void openStart() { stream_ << "<" << name_; }
    void attributes() { for (auto& attr : attr_) attr.print(); }
    void openEnd() { stream_ << ">\n"; }
    void selfClosing() { stream_ << "/>\n"; }
    void openMain() { indent(); openStart(); attributes(); }
  public:
    Tag(std::string name, std::ostream& stream) : Element(std::move(name), stream), open_(false) { }
    ~Tag() { if(open_) close(); }
    void addAttribute(std::string name, std::string value) { attr_.emplace_back(std::move(name), std::move(value), stream_); }
    void addAttributeOnNewline(std::string name, std::string value);
    void open();
    void openSelfClosing() { openMain(); selfClosing(); }
    void close();
  };

  void Tag::close() {
    if (!open_)
      throw std::logic_error("Can't close " + name_ + ". Tag not opened.");
    stream_ << "</" << name_ << ">\n";
    open_ = false;
  }

  void Tag::open() {
    if (open_)
      throw std::logic_error("Can't open " + name_ + ". Tag already opened.");
    openMain();
    openEnd();
    open_ = true;
  }

  void Tag::addAttributeOnNewline(std::string name, std::string value) {
    attr_.emplace_back(std::move(name), std::move(value), stream_);
    attr_.back().setNewLine();
    attr_.back().setIndent(indent_ + 2);
  }

  void addSVGHeader(std::ostream& stream) {
    stream << "<\?xml version=\"1.0\" standalone=\"no\" \?>\n";
    stream << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
  }

}