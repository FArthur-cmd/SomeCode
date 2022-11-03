#include <gtest/gtest.h>

#include <algorithm>

/// Only simple test cases are demonstrated,
/// because it is easier to use them for people,
/// who don't want to go deep in GTests

template <typename T>
class Less {
 public:
  bool operator()(const T& first, const T& second) { return first < second; }
};

template <typename T>
class Greater {
 public:
  bool operator()(const T& first, const T& second) { return second < first; }
};

/// Example with sort
// =============================================
TEST(Basic, Less) {
  std::vector<int> test_vec{1, 10, 3, 5, 2, 19, 0};
  std::vector<int> result{0, 1, 2, 3, 5, 10, 19};
  std::sort(test_vec.begin(), test_vec.end(), Less<int>());
  for (size_t i = 0; i < test_vec.size(); ++i) {
    ASSERT_EQ(test_vec[i], result[i]);
  }
}

TEST(Basic, Greater) {
  std::vector<int> test_vec{1, 10, 3, 5, 2, 19, 0};
  std::vector<int> result{19, 10, 5, 3, 2, 1, 0};
  std::sort(test_vec.begin(), test_vec.end(), Greater<int>());
  for (size_t i = 0; i < test_vec.size(); ++i) {
    ASSERT_EQ(test_vec[i], result[i]);
  }
}

// =============================================
TEST(Stress, Less) {
  /// TODO: make a lot of tests with generating different data
  /// more examples in other tasks
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
