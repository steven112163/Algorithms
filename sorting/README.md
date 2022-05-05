# Sorting Algorithms



## Complexity
| Algorithm                               |       Best       |                 Worst                  |           Average            |  Space   |               Stable                | Note                                 |
| :-------------------------------------- | :--------------: | :------------------------------------: | :--------------------------: | :------: | :---------------------------------: | :----------------------------------- |
| [Bubble Sort](src/BubbleSort.hpp)       |       O(n)       |            O(n<sup>2</sup>)            |       O(n<sup>2</sup>)       |   O(1)   |                  ✅                  |
| [Selection Sort](src/SelectionSort.hpp) | O(n<sup>2</sup>) |            O(n<sup>2</sup>)            |       O(n<sup>2</sup>)       |   O(1)   |                  ❌                  |
| [Insertion Sort](src/InsertionSort.hpp) |       O(n)       |            O(n<sup>2</sup>)            |       O(n<sup>2</sup>)       |   O(1)   |                  ✅                  |
| [Merge Sort](src/MergeSort.hpp)         |     O(nlogn)     |                O(nlogn)                |           O(nlogn)           |   O(n)   |                  ✅                  |
| [Heap Sort](src/HeapSort.hpp)           |     O(nlogn)     |                O(nlogn)                |           O(nlogn)           |   O(1)   |                  ❌                  |
| [Quick Sort](src/QuickSort.hpp)         |     O(nlogn)     |            O(n<sup>2</sup>)            |           O(nlogn)           |   O(1)   |                  ❌                  |
| [Bucket Sort](src/BucketSort.hpp)       |     O(n + k)     | The same as the used sorting algorithm | O(n + n<sup>2</sup> / k + k) | O(n + k) | Based on the used sorting algorithm |
| [Count Sort](src/CountSort.hpp)         |     O(n + k)     |                O(n + k)                |           O(n + k)           | O(n + k) |                  ✅                  | It can only be used to sort integers |