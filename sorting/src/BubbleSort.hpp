#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <functional>
#include <utility>
#include <vector>

namespace algo {
template <typename T>
class BubbleSort {
   public:
    static void sort(
        std::vector<T>& numbers,
        const std::function<bool(const T&, const T&)> comp = std::less<T>()) {
        bubble_sort(numbers, numbers.size(), comp);
    }

   private:
    static void bubble_sort(
        std::vector<T>& numbers, const int& len,
        const std::function<bool(const T&, const T&)>& comp) {
        // Place the minimum/maximum at the tail of the subarray in each round
        for (int round{0}; round < len - 1; round++)
            for (int idx{0}; idx < len - 1 - round; idx++)
                if (comp(numbers[idx + 1], numbers[idx]))
                    std::swap(numbers[idx], numbers[idx + 1]);
    }
};
}  // namespace algo

#endif