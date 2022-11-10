#pragma once

#include <list>
#include <optional>
#include <vector>

template <typename Value, class Hash, class EqualsTo>
class HashTable {
 public:
  HashTable(size_t size);

  bool Insert(const Value& value);

  void Delete(const Value& value);

  bool Contains(const Value& value);

 private:
};