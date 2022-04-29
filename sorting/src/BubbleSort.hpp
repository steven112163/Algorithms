#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <utility>
#include <vector>

class BubbleSort {
   public:
    static void sort(std::vector<int>& numbers) {
        bubble_sort(numbers, numbers.size());
    }

   private:
    static void bubble_sort(std::vector<int>& numbers, const int& len) {
        for (int round{0}; round < len - 1; round++)
            for (int idx{0}; idx < len - 1 - round; idx++)
                if (numbers[idx] > numbers[idx + 1])
                    std::swap(numbers[idx], numbers[idx + 1]);
    }
};

#endif