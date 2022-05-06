# String Algorithms



## Complexity
### Pattern Searching
| Algorithm                                                | Preprocessing |              Matching               |  Space   |
| :------------------------------------------------------- | :-----------: | :---------------------------------: | :------: |
| [Naive Algorithm](src/NaiveSearch.hpp)                   |     None      |                O(nm)                |   None   |
| [Knuth-Morris-Pratt Algorithm](src/KnuthMorrisPratt.hpp) |     O(m)      |                O(n)                 |   O(m)   |
| [Boyer-Moore Algorithm](src/BoyerMoore.hpp)              |     O(m)      | O(n / m) at best</br>O(nm) at worst | O(m + k) |