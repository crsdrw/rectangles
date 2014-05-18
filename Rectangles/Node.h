#pragma once

#include <memory>
#include <vector>
#include <list>
#include "Window.h"

namespace rec {

  class Node {
   private:
    Window window;
    std::unique_ptr<Node> first;
    std::unique_ptr<Node> second;

    bool isLeaf() const { return !(first || second); }
    void findLeavesInternal(std::vector<const Node*>& leaves, const Vec* p) const;

   public:
    explicit Node(Window w) : window(std::move(w)), first(), second() {}
    Node(Node&& in) : window(std::move(in.window)), first(std::move(in.first)), second(std::move(in.second)) {}
    ~Node() {}
    Node(const Node&) = delete;  // Copying not allowed
    Node& operator=(const Node&) = delete;  // Copying not allowed

    void setFirst(Window sub_window) { first.reset(new Node(sub_window)); }
    void setSecond(Window sub_window) { second.reset(new Node(sub_window)); }

    std::vector<const Node*>     findIntersectingLeaves(Vec p) const;
    std::vector<const Node*>     findLeaves() const;
    Window                       getWindow() const { return window; }
  };
}  // namespace rec
