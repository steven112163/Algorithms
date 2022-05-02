#ifndef COUNT_SORT_H
#define COUNT_SORT_H

#include <functional>
#include <limits>
#include <vector>

namespace algo {
class CountSort {
   public:
    static void sort(std::vector<int>& numbers,
                     const std::function<bool(const int&, const int&)> comp =
                         std::less<int>()) {
        count_sort(numbers, numbers.size(), comp);
    }

   private:
    static void count_sort(
        std::vector<int>& numbers, const int& len,
        const std::function<bool(const int&, const int&)>& comp) {
        std::vector<int> result(len);

        // Find minimum and maximum
        int minimum{std::numeric_limits<int>::max()};
        int maximum{std::numeric_limits<int>::min()};
        for (auto& n : numbers) {
            minimum = std::min(minimum, n);
            maximum = std::max(maximum, n);
        }
        if (minimum == maximum) return;

        std::vector<int> count(maximum - minimum + 1, 0);

        // Check if the sorting is increasing or decreasing
        if (comp(0, 1)) {
            // Increasing
            for (auto& n : numbers) count[n - minimum]++;

            for (int idx{1}; idx < maximum - minimum + 1; idx++)
                count[idx] += count[idx - 1];

            for (auto& n : numbers) {
                result[count[n - minimum] - 1] = n;
                count[n - minimum]--;
            }
        } else {
            // Decreasing
            for (auto& n : numbers) count[-(n - maximum)]++;

            for (int idx{1}; idx < maximum - minimum + 1; idx++)
                count[idx] += count[idx - 1];

            for (auto& n : numbers) {
                result[count[-(n - maximum)] - 1] = n;
                count[-(n - maximum)]--;
            }
        }

        numbers.swap(result);
    }
};
}  // namespace algo

#endif