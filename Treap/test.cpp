#include <gtest/gtest.h>

#include "include/TreapWithImplicitkey.hpp"

/// Only simple test cases are demonstrated,
/// because it is easier to use them for people,
/// who don't want to go deep in GTests

TEST(Basic, SmallInserts) {
  Trees::TreapWithImplicitkey treap;
  treap.Insert(0, 1);
  treap.Insert(1, 2);
  treap.Insert(0, 3);

  ASSERT_EQ(treap.Find(0), 3);
  treap.Remove(0);
  ASSERT_EQ(treap.Find(0), 1);
  treap.Remove(0);
  ASSERT_EQ(treap.Find(0), 2);
  treap.Remove(0);
}

TEST(Basic, ManyInserts) {
  Trees::TreapWithImplicitkey treap;
  for (int64_t i = -1000; i < 1000; ++i) {
    treap.Insert(0, i);
  }

  for (size_t i = 0; i < 2000; ++i) {
    ASSERT_EQ(treap.Find(i), 999 - static_cast<int64_t>(i));
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
