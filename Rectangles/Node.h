#pragma once

#include <memory>
#include <vector>
#include "Vec.h"

namespace rec {

  class Node;

  class Node {
  private:
    Vec pos;
    Vec size;
    std::unique_ptr<Node> first;
    std::unique_ptr<Node> second;

    bool isLeaf() const { return !(first || second); }
    void findLeavesInternal(std::vector<const Node*>& leaves, const Vec* p) const;

  public:
    Node(Vec pos, Vec size) : pos(pos), size(size) {};
    Node(Node&& in) : pos(in.pos), size(in.size), first(std::move(in.first)), second(std::move(in.second)) {}
    ~Node() {}
    Node(const Node&) = delete; // Copying not allowed
    Node& operator=(const Node&) = delete; // Copying not allowed

    void setFirst(Vec pos, Vec size) { first.reset(new Node(pos, size)); }
    void setSecond(Vec pos, Vec size) { second.reset(new Node(pos, size)); }
    
    std::vector<const Node*>     findIntersectingLeaves(Vec p) const;
    std::vector<const Node*>     findLeaves() const;
    Vec                          getPos() const { return pos; }
    Vec                          getSize() const { return size; }
    void                         growNode(Vec p);
  };
  inline Vec getMax(const Node& node) { return node.getPos() + node.getSize(); }
  inline bool isColision(const Node& node, Vec p) { return p > node.getPos() && p < getMax(node); }
  
  Node merge(const std::vector<Node>& nodes);
}