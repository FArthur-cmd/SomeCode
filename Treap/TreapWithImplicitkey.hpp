#pragma once
#include <cstddef>
#include <iostream>
#include <limits>
#include <random>

/// THERE IS AN ERROR IN THIS CODE. TRY TO FIX IT :)

namespace Trees {

struct Node {
  /// TODO: should be private?
  std::random_device rand_dev;
  std::mt19937 gen;
  std::uniform_int_distribution<size_t> distrib;

  size_t sum_of_children;
  size_t y;
  Node* left;
  Node* right;

  /// size_t sum_in_tree;
  int64_t value;

  Node() = default;

  Node(const size_t& sum_of_children_, const int64_t& value_)
      : gen(rand_dev()),
        distrib(0, std::numeric_limits<size_t>::max()),
        sum_of_children(sum_of_children_),
        y(distrib(gen)),
        value(value_){};

  ~Node();
};

/**
 * @brief very simple treap with implicit key will store number of elements
 * in children to speed up some operations.
 * This structure can be adapted to other tasks.
 */
class TreapWithImplicitkey {
 public:
  TreapWithImplicitkey() = default;
  explicit TreapWithImplicitkey(Node* root) : root_(root){};

  std::pair<Node*, Node*> Split(const size_t& pos);

  /// NOTE: both trees will be destroyed after operation to prevent memory leaks
  /// (smart pointers can fix this problem)
  /// return type can be also changed to TreapWithImplicitkey
  static Node* Merge(TreapWithImplicitkey& first, TreapWithImplicitkey& second);

  void Insert(size_t pos, const int64_t& value);

  void Remove(const size_t& pos);

  /// pos < all_children_number
  int64_t Find(size_t pos);

  bool Empty() const { return root_ == nullptr; }

  ~TreapWithImplicitkey();

 private:
  static Node* MergeNodes(Node* first, Node* second);
  static std::pair<Node*, Node*> SplitNode(Node* current, const size_t& pos);

  Node* root_ = nullptr;
};

}  // namespace Trees
