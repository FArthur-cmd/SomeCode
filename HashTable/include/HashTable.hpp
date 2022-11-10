#pragma once

#include <list>
#include <optional>
#include <vector>

template <typename Value, class Hash, class EqualsTo>
class HashTable {
 public:
  HashTable(size_t size) : table_(size), size_(size) {}

  bool Insert(const Value& value);

  void Delete(const Value& value);

  bool Contains(const Value& value);

 private:
  using Container = std::vector<std::list<Value> >;

  Container table_;
  Hash hash_;
  EqualsTo equals_to_;
  size_t size_;
};

template <typename Value, class Hash, class EqualsTo>
bool HashTable<Value, Hash, EqualsTo>::Insert(const Value& value) {
  size_t position = hash_(value) % size_;
  for (auto& element : table_[position]) {
    if (equals_to_(element, value)) {
      element = value;
      return false;
    }
  }

  table_[position].push_back(value);
  return true;
}

template <typename Value, class Hash, class EqualsTo>
void HashTable<Value, Hash, EqualsTo>::Delete(const Value& value) {
  size_t position = hash_(value) % size_;
  auto it = table_[position].begin();
  auto erase_element = it;
  while (it != table_[position].end()) {
    if (equals_to_(*it, value)) {
      erase_element = it;
      ++it;
      table_[position].erase(erase_element);
    }
    ++it;
  }
}

template <typename Value, class Hash, class EqualsTo>
bool HashTable<Value, Hash, EqualsTo>::Contains(const Value& value) {
  size_t position = hash_(value) % size_;
  for (const auto& element : table_[position]) {
    if (equals_to_(element, value)) {
      return true;
    }
  }
  return false;
}