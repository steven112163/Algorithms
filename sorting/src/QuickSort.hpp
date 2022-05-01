#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <utility>
#include <vector>

template <typename T>
class QuickSortLomuto {
   public:
    static void sort(std::vector<T>& numbers) {
        quick_sort(numbers, 0, numbers.size() - 1);
    }

   private:
    static void quick_sort(std::vector<T>& numbers, const int& start,
                           const int& end) {
        if (start >= end) return;

        int pivot{partition(numbers, start, end)};
        quick_sort(numbers, start, pivot - 1);
        quick_sort(numbers, pivot + 1, end);
    }

    static int partition(std::vector<T>& numbers, const int& start,
                         const int& end) {
        int pivot_idx{(start + end) / 2};
        int pivot{numbers[pivot_idx]};

        std::swap(numbers[pivot_idx], numbers[end]);
        pivot_idx = end;

        int swap_idx{start};
        for (int idx{start}; idx < end; idx++)
            if (numbers[idx] < pivot) {
                std::swap(numbers[idx], numbers[swap_idx]);
                swap_idx++;
            }
        std::swap(numbers[pivot_idx], numbers[swap_idx]);

        return swap_idx;
    }
};

template <typename T>
class QuickSortHoare {
   public:
    static void sort(std::vector<T>& numbers) {
        quick_sort(numbers, 0, numbers.size() - 1);
    }

   private:
    static void quick_sort(std::vector<T>& numbers, const int& start,
                           const int& end) {
        if (start >= end) return;

        int pivot{partition(numbers, start, end)};
        quick_sort(numbers, start, pivot);
        quick_sort(numbers, pivot + 1, end);
    }

    static int partition(std::vector<T>& numbers, const int& start,
                         const int& end) {
        int pivot{numbers[(start + end) / 2]};

        int left{start - 1}, right{end + 1};
        while (true) {
            do {
                left++;
            } while (numbers[left] < pivot);

            do {
                right--;
            } while (numbers[right] > pivot);

            if (left < right)
                std::swap(numbers[left], numbers[right]);
            else
                break;
        }

        return right;
    }
};

#endif