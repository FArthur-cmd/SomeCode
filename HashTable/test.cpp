#include <gtest/gtest.h>

#include <random>
#include <string>
#include <unordered_set>

#include "include/HashTable.hpp"
#include "include/HashUtils.hpp"

TEST(Basic, INT) {
  
}

TEST(Basic, String) {
  
}

TEST(Basic, UserTest) {
  HashTable<User, Hash::UserHash<1000>, Equality::UserEquality> hash_table(
      1000);

  HashTable<User, Hash::UserHash<1000>, Equality::UserEqualityWithTime>
      hash_table_with_time(1000);

  User first_user{.name = "Test", .id = 5, .balance = 0, .timestamp = 0};
  User second_user{.name = "Other", .id = 2, .balance = 100, .timestamp = 1};
  hash_table.Insert(first_user);
  hash_table_with_time.Insert(first_user);
  hash_table.Insert(second_user);
  hash_table_with_time.Insert(second_user);

  User modified_first = first_user;
  modified_first.timestamp += 2;

  hash_table.Insert(modified_first);
  hash_table_with_time.Insert(modified_first);

  ASSERT_EQ(true, hash_table.Contains(modified_first));
  /// TODO: add check for timestamp
  ASSERT_EQ(true, hash_table.Contains(first_user));
  ASSERT_EQ(true, hash_table.Contains(second_user));

  ASSERT_EQ(true, hash_table_with_time.Contains(modified_first));
  ASSERT_EQ(true, hash_table_with_time.Contains(first_user));
  ASSERT_EQ(true, hash_table_with_time.Contains(second_user));
}

TEST(Stress, INT) {
  const size_t size = 100000;
  HashTable<int, Hash::IntSimpleHash<int, size>, Equality::SimpleEquality<int> >
      hash_table(size);
  std::unordered_set<int> res;
  std::random_device rand_dev;
  std::mt19937 gen(rand_dev());
  std::uniform_int_distribution<int32_t> distrib(
      0, std::numeric_limits<int32_t>::max());
  int32_t generator_choice;
  int32_t value;

  for (size_t i = 0; i < 100000; ++i) {
    generator_choice = distrib(gen);
    if (generator_choice % 3 == 0) {
      value = distrib(gen);
      hash_table.Insert(value);
      res.insert(value);
    } else if (generator_choice % 3 == 1) {
      value = distrib(gen);
      ASSERT_EQ(hash_table.Contains(value), res.contains(value));
    } else {
      value = distrib(gen);
      if (hash_table.Contains(value)) {
        hash_table.Delete(value);
        res.erase(value);
      }
      ASSERT_EQ(hash_table.Contains(value), res.contains(value));
    }
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
