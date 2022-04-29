#include <gtest/gtest.h>

#include <BubbleSort.hpp>
#include <InsertionSort.hpp>
#include <SelectionSort.hpp>
#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

std::vector<int> generate_rand_int(const int& start, const int& end,
                                   const int& num) {
    std::mt19937 rng{static_cast<unsigned int>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<int> distribution{start, end};

    std::vector<int> rand_int{};
    for (int count{0}; count < num; count++)
        rand_int.push_back(distribution(rng));

    return std::move(rand_int);
}

std::array<std::function<void(std::vector<int>&)>, 3> algorithms{
    &BubbleSort::sort, &SelectionSort::sort, &InsertionSort::sort};

namespace {
TEST(SortingTest, PositiveIntegersOnly) {
    for (int size{0}; size < 1000; size++) {
        for (auto algo : algorithms) {
            std::vector<int> rand_int{generate_rand_int(1, 100, size)};
            std::vector<int> copy_rand_int{rand_int};

            std::sort(rand_int.begin(), rand_int.end());
            algo(copy_rand_int);

            EXPECT_EQ(rand_int, copy_rand_int);
        }
    }
}

TEST(SortingTest, NegativeIntegersOnly) {
    for (int size{0}; size < 1000; size++) {
        for (auto algo : algorithms) {
            std::vector<int> rand_int{generate_rand_int(-100, 1, size)};
            std::vector<int> copy_rand_int{rand_int};

            std::sort(rand_int.begin(), rand_int.end());
            algo(copy_rand_int);

            EXPECT_EQ(rand_int, copy_rand_int);
        }
    }
}

TEST(SortingTest, MixedIntegers) {
    for (int size{0}; size < 1000; size++) {
        for (auto algo : algorithms) {
            std::vector<int> rand_int{generate_rand_int(-100, 100, size)};
            std::vector<int> copy_rand_int{rand_int};

            std::sort(rand_int.begin(), rand_int.end());
            algo(copy_rand_int);

            EXPECT_EQ(rand_int, copy_rand_int);
        }
    }
}
}  // namespace

int main(int argc, char* argv[]) {
    std::cout << "Running tests for sorting algorithms" << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}