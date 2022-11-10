#pragma once
#include <string>

struct User {
  size_t timestamp;
  std::string name;
  size_t id;
  int64_t balance;
};

namespace Hash {

template <typename T, size_t SIZE = 100000>
class IntSimpleHash {
 public:
  bool operator()(T value) { return value % SIZE; }
};

template <size_t SIZE = 100000>
class StringHash {
 public:
  bool operator()(std::string value) {
    size_t result = 0;
    for (char symbol : value) {
      result = (result * alphabet_size_ + symbol - 'a') % SIZE;
    }
    return result;
  }

 private:
  size_t alphabet_size_ = 28;
};

template <size_t SIZE = 100000>
class UserHash {
 public:
  bool operator()(const User& value) {
    return (string_hash(value.name) + size_t_hash(value.id)) % SIZE;
  }

 private:
  StringHash<SIZE> string_hash;
  IntSimpleHash<size_t, SIZE> size_t_hash;
};

}  // namespace Hash

namespace Equality {

template <typename T>
class SimpleEquality {
 public:
  bool operator()(const T& first, const T& second) { return first == second; }
};

class UserEquality {
 public:
  bool operator()(const User& first, const User& second) {
    return first.name == second.name && first.id == second.id;
  }
};

class UserEqualityWithTime {
 public:
  bool operator()(const User& first, const User& second) {
    return first.name == second.name && first.id == second.id &&
           first.timestamp == second.timestamp;
  }
};

}  // namespace Equality