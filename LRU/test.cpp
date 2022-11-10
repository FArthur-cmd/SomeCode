#include <gtest/gtest.h>

#include <random>
#include <vector>

#include "include/LRU.hpp"

TEST(Basic, INSERT) {
  LruCache<int, int> cache(2);
  cache.InsertValue(1, 2);
  cache.InsertValue(2, 3);
  cache.InsertValue(1, 3);
  ASSERT_EQ(3, cache.GetValue(1));

  cache.InsertValue(1, 2);
  ASSERT_EQ(2, cache.GetValue(1).value());

  cache.InsertValue(3, 2);
  ASSERT_EQ(false, cache.GetValue(2).has_value());
}

TEST(Basic, EmptyCheck) {
  LruCache<int, int> cache(2);
  ASSERT_EQ(false, cache.GetValue(2).has_value());
  ASSERT_EQ(false, cache.GetValue(3).has_value());
}

TEST(HeavyStructures, HugeCache) {
  LruCache<std::string, std::string> cache(10);

  cache.InsertValue("a", "1");
  cache.InsertValue("b", "2");
  cache.InsertValue("c", "3");

  ASSERT_EQ(true, cache.GetValue("a").has_value());
  ASSERT_EQ("1", cache.GetValue("a"));
  ASSERT_EQ("2", cache.GetValue("b"));
  ASSERT_EQ("3", cache.GetValue("c"));

  ASSERT_EQ(false, cache.GetValue("d").has_value());

  cache.InsertValue("c", "4");
  ASSERT_EQ("4", cache.GetValue("c"));
}

TEST(HeavyStructures, SmallCache) {
  LruCache<std::string, std::string> cache(2);

  cache.InsertValue("b", "4");
  cache.InsertValue("c", "5");
  cache.InsertValue("b", "6");

  cache.InsertValue("e", "7");
  ASSERT_EQ(false, cache.GetValue("c").has_value());
  ASSERT_EQ(true, cache.GetValue("b").has_value());
  ASSERT_EQ(true, cache.GetValue("e").has_value());

  ASSERT_EQ(true, cache.GetValue("b").has_value());
  cache.InsertValue("f", "8");
  ASSERT_EQ(false, cache.GetValue("e").has_value());
  ASSERT_EQ(true, cache.GetValue("b").has_value());
  ASSERT_EQ(true, cache.GetValue("f").has_value());
}

TEST(STRESS, Strings) {
  LruCache<uint32_t, std::string> cache(100);
  std::random_device rand_dev;
  std::mt19937 gen(rand_dev());
  std::uniform_int_distribution<uint32_t> distrib(
      0, std::numeric_limits<uint32_t>::max());

  for (size_t i = 0; i < 100000; ++i) {
    if (distrib(gen) % 2 == 0) {
      cache.InsertValue(distrib(gen) % 500, "foo");
    } else {
      cache.GetValue(distrib(gen) % 500);
    }
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
