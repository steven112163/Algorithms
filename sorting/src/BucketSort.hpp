#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H

#include <InsertionSort.hpp>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

namespace algo {
template <typename T>
class BucketSort {
   public:
    static void sort(
        std::vector<T>& numbers,
        const std::function<bool(const T&, const T&)> comp = std::less<T>()) {
        bucket_sort(numbers, numbers.size(), comp);
    }

   private:
    static void bucket_sort(
        std::vector<T>& numbers, const int& len,
        const std::function<bool(const T&, const T&)>& comp) {
        // Find minimum and maximum
        int minimum{std::numeric_limits<T>::max()};
        int maximum{std::numeric_limits<T>::min()};
        for (auto& n : numbers) {
            minimum = std::min(minimum, n);
            maximum = std::max(maximum, n);
        }

        if (len == 0 || minimum == maximum) return;

        // Put each number to its corresponding bucket
        int num_of_buckets{len / 100 + 1};
        int range_in_bucket{(maximum - minimum) / num_of_buckets + 1};
        std::vector<std::vector<T>> buckets(num_of_buckets, std::vector<T>());
        for (auto& n : numbers)
            buckets[(n - minimum) / range_in_bucket].push_back(n);

        // Check if the sorting is increasing or decreasing
        bool increasing{true};
        if (!comp(0, 1)) increasing = false;

        // Sort each bucket and concatenate the results
        int idx{0};
        if (increasing) {
            for (int bucket_idx{0}; bucket_idx < num_of_buckets; bucket_idx++)
                if (buckets[bucket_idx].size() != 0) {
                    algo::InsertionSort<T>::sort(buckets[bucket_idx], comp);
                    for (auto& n : buckets[bucket_idx]) numbers[idx++] = n;
                }
        } else {
            for (int bucket_idx{num_of_buckets - 1}; bucket_idx > -1;
                 bucket_idx--)
                if (buckets[bucket_idx].size() != 0) {
                    algo::InsertionSort<T>::sort(buckets[bucket_idx], comp);
                    for (auto& n : buckets[bucket_idx]) numbers[idx++] = n;
                }
        }
    }
};
}  // namespace algo

#endif