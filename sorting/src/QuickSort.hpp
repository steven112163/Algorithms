#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <functional>
#include <utility>
#include <vector>

namespace algo {
template <typename T>
class QuickSortLomuto {
   public:
    static void sort(
        std::vector<T>& numbers,
        const std::function<bool(const T&, const T&)> comp = std::less<T>()) {
        quick_sort(numbers, 0, numbers.size() - 1, comp);
    }

   private:
    static void quick_sort(
        std::vector<T>& numbers, const int& start, const int& end,
        const std::function<bool(const T&, const T&)>& comp) {
        if (start >= end) return;

        int pivot{partition(numbers, start, end, comp)};
        quick_sort(numbers, start, pivot - 1, comp);
        quick_sort(numbers, pivot + 1, end, comp);
    }

    static int partition(std::vector<T>& numbers, const int& start,
                         const int& end,
                         const std::function<bool(const T&, const T&)>& comp) {
        int pivot_idx{(start + end) / 2};
        int pivot{numbers[pivot_idx]};

        std::swap(numbers[pivot_idx], numbers[end]);
        pivot_idx = end;

        int swap_idx{start};
        for (int idx{start}; idx < end; idx++)
            if (comp(numbers[idx], pivot)) {
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
    static void sort(
        std::vector<T>& numbers,
        const std::function<bool(const T&, const T&)> comp = std::less<T>()) {
        quick_sort(numbers, 0, numbers.size() - 1, comp);
    }

   private:
    static void quick_sort(
        std::vector<T>& numbers, const int& start, const int& end,
        const std::function<bool(const T&, const T&)>& comp) {
        if (start >= end) return;

        int pivot{partition(numbers, start, end, comp)};
        quick_sort(numbers, start, pivot, comp);
        quick_sort(numbers, pivot + 1, end, comp);
    }

    static int partition(std::vector<T>& numbers, const int& start,
                         const int& end,
                         const std::function<bool(const T&, const T&)>& comp) {
        int pivot{numbers[(start + end) / 2]};

        int left{start - 1}, right{end + 1};
        while (true) {
            do {
                left++;
            } while (comp(numbers[left], pivot));

            do {
                right--;
            } while (comp(pivot, numbers[right]));

            if (left < right)
                std::swap(numbers[left], numbers[right]);
            else
                break;
        }

        return right;
    }
};
}  // namespace algo

#endif