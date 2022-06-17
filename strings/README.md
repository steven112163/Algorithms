# String Algorithms



## Complexity
### Pattern Searching
| Algorithm                                                | Preprocessing |              Matching               |  Space   |
| :------------------------------------------------------- | :-----------: | :---------------------------------: | :------: |
| [Naive Pattern Searching](src/NaiveSearch.hpp)           |     None      |                O(nm)                |   None   |
| [Knuth-Morris-Pratt Algorithm](src/KnuthMorrisPratt.hpp) |     O(m)      |                O(n)                 |   O(m)   |
| [Boyer-Moore Algorithm](src/BoyerMoore.hpp)              |     O(m)      | O(n / m) at best</br>O(nm) at worst | O(m + k) |
| [Rabin-Karp Algorithm](src/RabinKarp.hpp)                |     O(m)      | O(n) in average</br>O(nm) at worst  |   O(1)   |

### Lexicographically Minimal String Rotation
| Algorithm                                                              |       Time       | Space |
| :--------------------------------------------------------------------- | :--------------: | :---: |
| [Naive Lexicographically Minimal String Rotation](src/NaiveRotate.hpp) | O(n<sup>2</sup>) | O(n)  |
| [Booth's Algorithm](src/BoothsAlgorithm.hpp)                           |       O(n)       | O(n)  |

### Palindrome Searching
| Algorithm                                             |       Time       |      Space       |
| :---------------------------------------------------- | :--------------: | :--------------: |
| [Naive Palindrome Searching](src/NaivePalindrome.hpp) | O(n<sup>3</sup>) |       O(1)       |
| [Expanding Around Center](src/ExpandPalindrome.hpp)   | O(n<sup>2</sup>) |       O(1)       |
| [Dynamic Programming](src/DynamicPalindrome.hpp)      | O(n<sup>2</sup>) | O(n<sup>2</sup>) |
| [Manacher's Algorithm](src/ManachersAlgorithm.hpp)    |       O(n)       |       O(n)       |