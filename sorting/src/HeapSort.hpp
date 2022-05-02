#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <functional>
#include <utility>
#include <vector>

namespace algo {
template <typename T>
class HeapSort {
   public:
    static void sort(
        std::vector<T>& numbers,
        const std::function<bool(const T&, const T&)> comp = std::less<T>()) {
        heap_sort(numbers, numbers.size(), comp);
    }

   private:
    static void heap_sort(std::vector<T>& numbers, const int& len,
                          const std::function<bool(const T&, const T&)>& comp) {
        for (int parent{len / 2 - 1}; parent > -1; parent--)
            heapify(numbers, len, parent, comp);

        for (int idx{len - 1}; idx > -1; idx--) {
            std::swap(numbers[0], numbers[idx]);
            heapify(numbers, idx, 0, comp);
        }
    }

    static void heapify(std::vector<T>& numbers, const int& len, int parent,
                        const std::function<bool(const T&, const T&)>& comp) {
        while (true) {
            int left_child{parent * 2 + 1};
            int right_child{parent * 2 + 2};
            int target{parent};

            if (left_child < len && comp(numbers[target], numbers[left_child]))
                target = left_child;
            if (right_child < len &&
                comp(numbers[target], numbers[right_child]))
                target = right_child;

            if (target != parent) {
                std::swap(numbers[parent], numbers[target]);
                parent = target;
            } else {
                break;
            }
        }
    }
};
}  // namespace algo

#endif