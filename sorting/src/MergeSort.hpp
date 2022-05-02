#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <functional>
#include <limits>
#include <vector>

namespace algo {
template <typename T>
class MergeSortTopDown {
   public:
    static void sort(
        std::vector<T>& numbers,
        const std::function<bool(const T&, const T&)> comp = std::less<T>()) {
        merge_sort(numbers, 0, numbers.size() - 1, comp);
    }

   private:
    static void merge_sort(
        std::vector<T>& numbers, const int& start, const int& end,
        const std::function<bool(const T&, const T&)>& comp) {
        if (start >= end) return;

        int mid{(start + end) / 2};
        merge_sort(numbers, start, mid, comp);
        merge_sort(numbers, mid + 1, end, comp);
        merge(numbers, start, mid, end, comp);
    }

    static void merge(std::vector<T>& numbers, const int& start, const int& mid,
                      const int& end,
                      const std::function<bool(const T&, const T&)>& comp) {
        std::vector<int> left_numbers(numbers.begin() + start,
                                      numbers.begin() + mid + 1);
        std::vector<int> right_numbers(numbers.begin() + mid + 1,
                                       numbers.begin() + end + 1);

        // Check if the sorting is inceasing or decreasing
        if (comp(0, 1)) {
            // Increasing
            left_numbers.push_back(std::numeric_limits<T>::max());
            right_numbers.push_back(std::numeric_limits<T>::max());
        } else {
            // Decreasing
            left_numbers.push_back(std::numeric_limits<T>::min());
            right_numbers.push_back(std::numeric_limits<T>::min());
        }
        
        int left_idx{0}, right_idx{0};
        for (int idx{start}; idx <= end; idx++) {
            numbers[idx] =
                (comp(left_numbers[left_idx], right_numbers[right_idx]))
                    ? left_numbers[left_idx++]
                    : right_numbers[right_idx++];
        }
    }
};

template <typename T>
class MergeSortBottomUp {
   public:
    static void sort(
        std::vector<T>& numbers,
        const std::function<bool(const T&, const T&)> comp = std::less<T>()) {
        merge_sort(numbers, numbers.size(), comp);
    }

   private:
    static void merge_sort(
        std::vector<T>& numbers, const int& len,
        const std::function<bool(const T&, const T&)>& comp) {
        std::vector<int> temp_numbers(len);

        for (int seq_len{1}; seq_len < len; seq_len += seq_len) {
            for (int start{0}; start < len; start += seq_len * 2) {
                int mid{std::min(start + seq_len, len)},
                    end{std::min(start + seq_len * 2, len)};

                int left_idx{start}, left_end{mid};
                int right_idx{mid}, right_end{end};

                int idx{start};
                while (left_idx < left_end && right_idx < right_end) {
                    temp_numbers[idx++] =
                        (comp(numbers[left_idx], numbers[right_idx]))
                            ? numbers[left_idx++]
                            : numbers[right_idx++];
                }
                while (left_idx < left_end)
                    temp_numbers[idx++] = numbers[left_idx++];
                while (right_idx < right_end)
                    temp_numbers[idx++] = numbers[right_idx++];
            }

            numbers.swap(temp_numbers);
        }
    }
};
}  // namespace algo

#endif