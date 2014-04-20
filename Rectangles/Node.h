#pragma once

#include <memory>
#include <vector>
#include "Vec.h"

namespace rec {

  class Node;

  class Node {
  private:
    Vec pos;
    Vec sz;
    std::unique_ptr<Node> first;
    std::unique_ptr<Node> second;

    bool isLeaf() const { return !(first || second); }
    void findLeavesInternal(std::vector<const Node*>& leaves, const Vec* p) const;

  public:
    Node(Vec pos, Vec sz) : pos(pos), sz(sz) {};
    Node(Node&& in) : pos(in.pos), sz(in.sz), first(std::move(in.first)), second(std::move(in.second)) {}
    ~Node() {}
    Node(const Node&) = delete; // Copying not allowed
    Node& operator=(const Node&) = delete; // Copying not allowed

    void setFirst(Vec pos, Vec sz) { first.reset(new Node(pos, sz)); }
    void setSecond(Vec pos, Vec sz) { second.reset(new Node(pos, sz)); }
    
    std::vector<const Node*>     findIntersectingLeaves(Vec p) const;
    std::vector<const Node*>     findLeaves() const;
    Vec                          getPos() const { return pos; }
    Vec                          getSize() const { return sz; }
  };

  inline bool isColision(const Node& node, Vec p) { return p > node.getPos() && p < node.getPos() + node.getSize(); }
}

