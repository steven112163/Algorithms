#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <utility>
#include <vector>

template <typename T>
class HeapSort {
   public:
    static void sort(std::vector<int>& numbers) {
        heap_sort(numbers, numbers.size());
    }

   private:
    static void heap_sort(std::vector<int>& numbers, const int& len) {
        for (int parent{len / 2 - 1}; parent > -1; parent--)
            heapify(numbers, len, parent);

        for (int idx{len - 1}; idx > -1; idx--) {
            std::swap(numbers[0], numbers[idx]);
            heapify(numbers, idx, 0);
        }
    }

    static void heapify(std::vector<int>& numbers, const int& len, int parent) {
        while (true) {
            int left_child{parent * 2 + 1};
            int right_child{parent * 2 + 2};
            int largest{parent};

            if (left_child < len && numbers[left_child] > numbers[largest])
                largest = left_child;
            if (right_child < len && numbers[right_child] > numbers[largest])
                largest = right_child;

            if (largest != parent) {
                std::swap(numbers[parent], numbers[largest]);
                parent = largest;
            } else {
                break;
            }
        }
    }
};

#endif