#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <functional>
#include <utility>
#include <vector>

namespace algo {
template <typename T>
class InsertionSort {
   public:
    static void sort(
        std::vector<T>& numbers,
        const std::function<bool(const T&, const T&)> comp = std::less<T>()) {
        insertion_sort(numbers, numbers.size(), comp);
    }

   private:
    static void insertion_sort(
        std::vector<T>& numbers, const int& len,
        const std::function<bool(const T&, const T&)>& comp) {
        for (int key_idx{1}; key_idx < len; key_idx++) {
            int sorted_idx{key_idx - 1}, key{numbers[key_idx]};
            while (sorted_idx > -1 && comp(key, numbers[sorted_idx])) {
                numbers[sorted_idx + 1] = numbers[sorted_idx];
                sorted_idx--;
            }
            numbers[sorted_idx + 1] = key;
        }
    }
};
}  // namespace algo

#endif