#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <utility>
#include <vector>

template <typename T>
class InsertionSort {
   public:
    static void sort(std::vector<T>& numbers) {
        insertion_sort(numbers, numbers.size());
    }

   private:
    static void insertion_sort(std::vector<T>& numbers, const int& len) {
        for (int key_idx{1}; key_idx < len; key_idx++) {
            int sorted_idx{key_idx - 1}, key{numbers[key_idx]};
            while (sorted_idx > -1 && numbers[sorted_idx] > key) {
                numbers[sorted_idx + 1] = numbers[sorted_idx];
                sorted_idx--;
            }
            numbers[sorted_idx + 1] = key;
        }
    }
};

#endif