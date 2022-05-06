# Algorithms
Algorithms &amp; Data Structures



## Prerequisites
* cmake >= 3.16
* gtest >= 1.11.0
* c++ >= 17



## Sorting Algorithms
* [Bubble Sort](sorting/src/BubbleSort.hpp) --- **O(n<sup>2</sup>)**
* [Selection Sort](sorting/src/SelectionSort.hpp) --- **O(n<sup>2</sup>)**
* [Insertion Sort](sorting/src/InsertionSort.hpp) --- **O(n<sup>2</sup>)**
* [Merge Sort](sorting/src/MergeSort.hpp) --- **O(nlogn)**
* [Heap Sort](sorting/src/HeapSort.hpp) --- **O(nlogn)**
* [Quick Sort](sorting/src/QuickSort.hpp) --- **O(nlogn)**
* [Bucket Sort](sorting/src/BucketSort.hpp) --- **O(n + n<sup>2</sup> / k + k)**
* [Count Sort](sorting/src/CountSort.hpp) --- **O(n + k)**



## String Algorithms
### Pattern Searching
* [Naive Pattern Searching](strings/src/NaiveSearch.hpp) --- **O(nm)**
* [Knuth-Morris-Pratt Algorithm](strings/src/KnuthMorrisPratt.hpp) --- **O(n + m)**
* [Boyer-Moore Algorithm](strings/src/BoyerMoore.hpp) --- **O(n / m + m)**
* [Rabin-Karp Algorithm](strings/src/RabinKarp.hpp) --- **O(n + m)**

### Lexicographically Minimal String Rotation
* [Naive Lexicographically Minimal String Rotation](strings/src/NaiveRotate.hpp) --- **O(n<sup>2</sup>)**
* [Booth's Algorithm](strings/src/BoothsAlgorithm.hpp) --- **O(n)**