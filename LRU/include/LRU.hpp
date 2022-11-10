#pragma once
#include <iostream>
#include <list>
#include <optional>
#include <unordered_map>

template <typename Key, typename Value>
class LruCache {
 public:
  explicit LruCache(size_t size);

  std::optional<Value> GetValue(const Key& key);
  /// GetValue(const Key& key, Value& return_value);

  void InsertValue(const Key& key, const Value& value);

 private:
};
