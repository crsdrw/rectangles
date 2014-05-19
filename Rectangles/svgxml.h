#pragma once

#include <string>
#include <iostream>
#include <vector>

namespace Svgxml {

  /**
   * Base class for scoped objects for writing XML elements to an output stream 
   */
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
   protected:
    std::string   name_;
    unsigned int  indent_;
    std::ostream& stream_;
    void indent() { stream_ << std::string(indent_, ' '); }
   public:
    Element(std::string name, std::ostream& stream) : name_(std::move(name)), indent_(0), stream_(stream) {}
    void setIndent(unsigned int new_indent) { indent_ = new_indent; }
    Element& operator=(const Element&) = delete;
    protected:
      std::string   name_;    ///< Name of the XML element.
      unsigned int  indent_;  ///< Indent level of the element.
      std::ostream& stream_;  ///< Stream to output the XML element to.

      /**
      * Output the whitespace to indent the element.
      */
      void indent() { stream_ << std::string(indent_, ' '); }

     public:

      /**
      * Constructor 
      * Default is zero indent level.
      * @param name The name of XML element.
      * @param stream The output stream to write to.
      */
      Element(std::string name, std::ostream& stream) : name_(std::move(name)), indent_(0), stream_(stream) {}

      /**
      * Set the indent level.
      * @param new_indent the number of characters to indent.
      */
      void setIndent(unsigned int new_indent) { indent_ = new_indent; }

      /**
      * Assigment operator disabled. Class must be constructed with a const reference stream to output to.
      * @return Self.
      */
      Element& operator=(const Element&) = delete;
  };

  /**
  * Class to help write XML attributes to an output stream
  */
  class Attr : public Element {
    std::string value_;    ///< The content of the attribute
    bool        newline_;  ///< True if the attribute should be output to the stream on a new line, false otherwise
    public:
 
      /**
      * Constructor taking the name and content of the attribute and the stream to output to.
      * The default is to not put the attribute on a new line.
      */
      Attr(std::string name, std::string value, std::ostream& stream) : Element(std::move(name), stream), value_(std::move(value)), newline_(false) {}

      /**
      * Configure the attribute to be output on a new line.
      */

      /**
      * Output the attribute to the output stream.
      */
  };

  Attr::Attr(std::string name, std::string value, std::ostream& stream) :
    Element(std::move(name), stream),
    value_(std::move(value)),
    newline_(false) {
  }


  void Attr::print() {
    if (newline_) {
      stream_ << "\n";
      indent();
    } else {
      stream_ << " ";
    }
    stream_ << name_ << "=\"" << value_ << "\"";
  }
 
  /**
  * Scoped object to write an XML tag to an output stream.
  */
  class Tag : public Element {
    std::vector<Attr> attr_;  ///< Attributes on the tag.
    bool              open_;  ///< Flag to indicate the tag is open.

    /**
     * Start to open the tag including the name.
     */
    void openStart() { stream_ << "<" << name_; }        

    /**
     * Write out attributes for the tag to the output stream
     */
    void attributes() { for (auto& attr : attr_) attr.print(); }  

    /**
    * End of the tag opening
    */
    void openEnd() { stream_ << ">\n"; }  

    /**
    * End of a self closing tag
    */
    void selfClosing() { stream_ << "/>\n"; }         

    /**
    * Main part of the tag opening
    */
    void openMain() { indent(); openStart(); attributes(); }      
    bool              open_;

   public:
    /** Constructor, taking name of the tag and the stream to output to.
     *  @param name The name of the tag.
     *  @param stream The output stream to write to.
     */
    Tag(std::string name, std::ostream& stream) : Element(std::move(name), stream), open_(false) { }

    /** Destructor, that will automatically close the tag if it is open */
    ~Tag() { if(open_) close(); }

    /** Add an attribute to the list of attributes to be written to the stream 
     * @param name The name of the attribute.
     */
    void addAttribute(std::string name, std::string value) { attr_.emplace_back(std::move(name), std::move(value), stream_); }

    /** Add an attribute to the list of attributes to be written to the stream that will need to be put on a new line */
    void addAttributeOnNewline(std::string name, std::string value);
    
    /** Open the tag in the output stream */
    void open();

    /** Open the tag as a self closing tag in the output stream */
    void openSelfClosing() { openMain(); selfClosing(); }

    /** Close the tag in the output stream */
    void close();
  };

  void Tag::addAttribute(std::string name, std::string value) {
    attr_.emplace_back(std::move(name), std::move(value), stream_);
  }

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

  inline void addSVGHeader(std::ostream& stream) {
    stream << "<\?xml version=\"1.0\" standalone=\"no\" \?>\n";
    stream << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n";
    stream << "  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
  }

}  // namespace Svgxml
