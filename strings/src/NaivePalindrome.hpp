#ifndef NAIVE_PALINDROME_H
#define NAIVE_PALINDROME_H

#include <string>
#include <unordered_set>
#include <vector>

namespace algo {
class NaiveLPS {
   public:
    static std::string search(const std::string& text) {
        return std::move(find_longest_palindrome_substring(text));
    }

    static int is_palindrome(const std::string& text, int start, int end) {
        if (start < 0 || end >= text.length()) return 0;

        int length{0};
        while (start <= end) {
            if (text[start] == text[end]) {
                length += (start == end) ? 1 : 2;
                start++;
                end--;
            } else {
                return 0;
            }
        }
        return length;
    }

   private:
    static std::string find_longest_palindrome_substring(
        const std::string& text) {
        int length{static_cast<int>(text.length())};
        std::string longest_palindrome{};

        for (int start{0}; start < length; start++) {
            for (int end{start}; end < length; end++) {
                int len{NaiveLPS::is_palindrome(text, start, end)};
                if (len > 0 && len > longest_palindrome.length()) {
                    longest_palindrome = text.substr(start, len);
                }
            }
        }

        return std::move(longest_palindrome);
    }
};

class NaiveAPS {
   public:
    static std::unordered_set<std::string> search(const std::string& text) {
        return std::move(find_all_palindrome_substrings(text));
    }

   private:
    static std::unordered_set<std::string> find_all_palindrome_substrings(
        const std::string& text) {
        int length{static_cast<int>(text.length())};
        std::unordered_set<std::string> palindromes{};

        for (int start{0}; start < length; start++) {
            for (int end{start}; end < length; end++) {
                int len{NaiveLPS::is_palindrome(text, start, end)};
                if (len > 0) {
                    palindromes.insert(text.substr(start, len));
                }
            }
        }

        return std::move(palindromes);
    }
};
}  // namespace algo

#endif