#pragma once
#include <iostream>
#include <list>
#include <optional>
#include <unordered_map>

template <typename Key, typename Value>
class LruCache {
 public:
  explicit LruCache(size_t size) : size_(size) {}

  std::optional<Value> GetValue(const Key& key);
  /// GetValue(const Key& key, Value& return_value);

  void InsertValue(const Key& key, const Value& value);

 private:
  using List = std::list<std::pair<Key, Value> >;
  using HashMap = std::unordered_map<Key, typename List::iterator>;

  List cache_list_;
  HashMap cache_hash_;
  size_t size_;
};

template <typename Key, typename Value>
std::optional<Value> LruCache<Key, Value>::GetValue(const Key& key) {
  std::optional<Value> result;
  if (cache_hash_.find(key) == cache_hash_.end()) {
    return result;
  }

  result.emplace(cache_hash_[key]->second);

  cache_list_.erase(cache_hash_[key]);

  // update reference
  cache_list_.push_back({key, result.value()});
  cache_hash_[key] = --cache_list_.end();

  return result;
}

template <typename Key, typename Value>
void LruCache<Key, Value>::InsertValue(const Key& key, const Value& value) {
  if (cache_hash_.find(key) != cache_hash_.end()) {
    cache_list_.erase(cache_hash_[key]);
  }

  cache_list_.push_back({key, value});
  cache_hash_[key] = --cache_list_.end();

  if (cache_list_.size() > size_) {
    cache_hash_.erase(cache_list_.begin()->first);
    cache_list_.pop_front();
  }
}
