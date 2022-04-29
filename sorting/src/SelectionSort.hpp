#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <utility>
#include <vector>

class SelectionSort {
   public:
    static void sort(std::vector<int>& numbers) {
        selection_sort(numbers, numbers.size());
    }

   private:
    static void selection_sort(std::vector<int>& numbers, const int& len) {
        for (int tail{0}; tail < len - 1; tail++) {
            int min_idx{tail};
            for (int idx{tail + 1}; idx < len; idx++)
                if (numbers[idx] < numbers[min_idx]) min_idx = idx;

            if (min_idx != tail) std::swap(numbers[tail], numbers[min_idx]);
        }
    }
};

#endif