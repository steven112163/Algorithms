#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <functional>
#include <utility>
#include <vector>

namespace algo {
template <typename T>
class SelectionSort {
   public:
    static void sort(
        std::vector<T>& numbers,
        const std::function<bool(const T&, const T&)> comp = std::less<T>()) {
        selection_sort(numbers, numbers.size(), comp);
    }

   private:
    static void selection_sort(
        std::vector<T>& numbers, const int& len,
        const std::function<bool(const T&, const T&)>& comp) {
        for (int tail{0}; tail < len - 1; tail++) {
            int target_idx{tail};
            for (int idx{tail + 1}; idx < len; idx++)
                if (comp(numbers[idx], numbers[target_idx])) target_idx = idx;

            if (target_idx != tail)
                std::swap(numbers[tail], numbers[target_idx]);
        }
    }
};
}  // namespace algo

#endif