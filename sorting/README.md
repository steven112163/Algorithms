# Sorting Algorithms



## Complexity
| Algorithm      |   Best   |                 Worst                  |      Average       |  Space   |               Stable                | Note                                 |
| :------------- | :------: | :------------------------------------: | :----------------: | :------: | :---------------------------------: | :----------------------------------- |
| Bubble Sort    |   O(n)   |                 O(n^2)                 |       O(n^2)       |   O(1)   |                  ✅                  |
| Selection Sort |  O(n^2)  |                 O(n^2)                 |       O(n^2)       |   O(1)   |                  ❌                  |
| Insertion Sort |   O(n)   |                 O(n^2)                 |       O(n^2)       |   O(1)   |                  ✅                  |
| Merge Sort     | O(nlogn) |                O(nlogn)                |      O(nlogn)      |   O(n)   |                  ✅                  |
| Heap Sort      | O(nlogn) |                O(nlogn)                |      O(nlogn)      |   O(1)   |                  ❌                  |
| Quick Sort     | O(nlogn) |                 O(n^2)                 |      O(nlogn)      |   O(1)   |                  ❌                  |
| Bucket Sort    | O(n + k) | The same as the used sorting algorithm | O(n + n^2 / k + k) | O(n + k) | Based on the used sorting algorithm |
| Count Sort     | O(n + k) |                O(n + k)                |      O(n + k)      | O(n + k) |                  ✅                  | It can only be used to sort integers |