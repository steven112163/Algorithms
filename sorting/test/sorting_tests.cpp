#include <gtest/gtest.h>

#include <BubbleSort.hpp>
#include <BucketSort.hpp>
#include <CountSort.hpp>
#include <HeapSort.hpp>
#include <InsertionSort.hpp>
#include <MergeSort.hpp>
#include <QuickSort.hpp>
#include <SelectionSort.hpp>
#include <algorithm>
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

std::vector<std::function<void(
    std::vector<int>&, const std::function<bool(const int&, const int&)>)>>
    algorithms{
        &algo::BubbleSort<int>::sort,        &algo::SelectionSort<int>::sort,
        &algo::InsertionSort<int>::sort,     &algo::MergeSortTopDown<int>::sort,
        &algo::MergeSortBottomUp<int>::sort, &algo::HeapSort<int>::sort,
        &algo::QuickSortLomuto<int>::sort,   &algo::QuickSortHoare<int>::sort,
        &algo::BucketSort<int>::sort,        &algo::CountSort::sort};

namespace {
TEST(SortingTest, PositiveIntegersOnly) {
    for (int size{0}; size < 1000; size++) {
        for (auto algo : algorithms) {
            std::vector<int> rand_int{generate_rand_int(1, 100, size)};
            std::vector<int> copy_rand_int{rand_int};

            std::sort(rand_int.begin(), rand_int.end());
            algo(copy_rand_int, std::less<int>());

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
            algo(copy_rand_int, std::less<int>());

            EXPECT_EQ(rand_int, copy_rand_int);
        }
    }
}

TEST(SortingTest, Increasing) {
    for (int size{0}; size < 1000; size++) {
        for (auto algo : algorithms) {
            std::vector<int> rand_int{generate_rand_int(-100, 100, size)};
            std::vector<int> copy_rand_int{rand_int};

            std::sort(rand_int.begin(), rand_int.end());
            algo(copy_rand_int, std::less<int>());

            EXPECT_EQ(rand_int, copy_rand_int);
        }
    }
}

TEST(SortingTest, Decreasing) {
    for (int size{0}; size < 1000; size++) {
        for (auto& algo : algorithms) {
            std::vector<int> rand_int{generate_rand_int(-100, 100, size)};
            std::vector<int> copy_rand_int{rand_int};

            std::sort(rand_int.begin(), rand_int.end(), std::greater<int>());
            algo(copy_rand_int, std::greater<int>());

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