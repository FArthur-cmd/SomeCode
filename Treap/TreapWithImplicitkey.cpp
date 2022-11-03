#include "TreapWithImplicitkey.hpp"

namespace Trees {

Node::~Node() {
  if (left != nullptr) {
    delete left;
    left = nullptr;
  }
  if (right != nullptr) {
    delete right;
    right = nullptr;
  }
}

namespace {
void UpdateChildren(Node* current) {
  current->sum_of_children = 1;
  if (current->left != nullptr) {
    current->sum_of_children += current->left->sum_of_children;
  }
  if (current->right != nullptr) {
    current->sum_of_children += current->right->sum_of_children;
  }
}

size_t FindPos(Node* current) {
  size_t cur_pos = current->sum_of_children - 1;
  if (current->right != nullptr) {
    cur_pos -= current->right->sum_of_children;
  }
  return cur_pos;
}
}  // namespace

Node* TreapWithImplicitkey::MergeNodes(Node* first, Node* second) {
  if (first == nullptr) {
    return second;
  }
  if (second == nullptr) {
    return first;
  }

  if (first->y < second->y) {
    second->left = MergeNodes(first, second->left);
    UpdateChildren(second);
    return second;
  }
  first->right = MergeNodes(first->right, second);
  UpdateChildren(first);
  return first;
}

std::pair<Node*, Node*> TreapWithImplicitkey::SplitNode(Node* current,
                                                        const size_t& pos) {
  if (current == nullptr) {
    return std::make_pair(nullptr, nullptr);
  }

  size_t current_pos = FindPos(current);
  if (pos < current_pos) {
    auto [left, right] = SplitNode(current->left, pos);
    current->left = right;
    UpdateChildren(current);
    return std::make_pair(left, current);
  }
  if (current_pos > pos) {
    auto [left, right] = SplitNode(current->right, pos - current_pos - 1);
    current->right = left;
    UpdateChildren(current);
    return std::make_pair(current, right);
  }

  Node * res_left = current->left;
  current->left = nullptr;
  return std::make_pair(current->left, current);
}

Node* TreapWithImplicitkey::Merge(TreapWithImplicitkey& first,
                                  TreapWithImplicitkey& second) {
  Node* res = MergeNodes(first.root_, second.root_);
  first.root_ = nullptr;
  second.root_ = nullptr;
  return res;
}

std::pair<Node*, Node*> TreapWithImplicitkey::Split(const size_t& pos) {
  return SplitNode(root_, pos);
}

void TreapWithImplicitkey::Insert(size_t pos, const int64_t& value) {
  auto [left, right] = Split(pos);
  Node* new_node = new Node(1, value);
  root_ = MergeNodes(left, MergeNodes(new_node, right));
}

void TreapWithImplicitkey::Remove(const size_t& pos) {
  auto [left, right_with_eq] = Split(pos);
  auto [equal, right] = SplitNode(right_with_eq, 1);
  root_ = MergeNodes(left, right);
}

int64_t TreapWithImplicitkey::Find(size_t pos) {
  Node* current_ptr = root_;
  size_t current_pos = FindPos(current_ptr);
  while (current_pos != pos) {
    if (current_pos < pos) {
      pos -= current_pos;
      current_ptr = current_ptr->right;
      current_pos = FindPos(current_ptr);
    } else {
      current_ptr = current_ptr->left;
      current_pos = FindPos(current_ptr);
    }
  }
  return current_ptr->value;
}

TreapWithImplicitkey::~TreapWithImplicitkey() { delete root_; }

}  // namespace Trees
