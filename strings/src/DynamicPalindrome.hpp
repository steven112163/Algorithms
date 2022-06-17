#ifndef DYNAMIC_PROGRAMMING_PALINDROME_H
#define DYNAMIC_PROGRAMMING_PALINDROME_H

#include <cstring>
#include <string>
#include <unordered_set>
#include <vector>

namespace algo {
class DynamicLPS {
   public:
    static std::string search(const std::string& text) {
        return std::move(find_longest_palindrome_substring(text));
    }

    static void establish_dp_table(
        const std::string& text,
        std::vector<std::vector<bool>>& is_palindrome) {
        int length{static_cast<int>(text.length())};
        is_palindrome = std::vector<std::vector<bool>>(
            length, std::vector<bool>(length, false));

        for (int idx{0}; idx < length; idx++) is_palindrome[idx][idx] = true;
        for (int idx{0}; idx < length - 1; idx++)
            if (text[idx] == text[idx + 1]) is_palindrome[idx][idx + 1] = true;

        for (int len{3}; len <= length; len++) {
            for (int start{0}; start < length - len + 1; start++) {
                int end{start + len - 1};
                if (is_palindrome[start + 1][end - 1] &&
                    (text[start] == text[end]))
                    is_palindrome[start][end] = true;
            }
        }
    }

   private:
    static std::string find_longest_palindrome_substring(
        const std::string& text) {
        int length{static_cast<int>(text.length())};
        std::vector<std::vector<bool>> is_palindrome{};
        DynamicLPS::establish_dp_table(text, is_palindrome);

        std::string longest_palindrome{};
        for (int start{0}; start < length; start++) {
            for (int end{0}; end < length; end++) {
                int len{end - start + 1};
                if (is_palindrome[start][end] &&
                    longest_palindrome.length() < len) {
                    longest_palindrome = text.substr(start, len);
                }
            }
        }

        return std::move(longest_palindrome);
    }
};

class DynamicAPS {
   public:
    static std::unordered_set<std::string> search(const std::string& text) {
        return std::move(find_all_palindrome_substrings(text));
    }

   private:
    static std::unordered_set<std::string> find_all_palindrome_substrings(
        const std::string& text) {
        int length{static_cast<int>(text.length())};
        std::vector<std::vector<bool>> is_palindrome{};
        DynamicLPS::establish_dp_table(text, is_palindrome);

        std::unordered_set<std::string> all_palindromes{};
        for (int start{0}; start < length; start++) {
            for (int end{0}; end < length; end++) {
                if (is_palindrome[start][end]) {
                    all_palindromes.insert(text.substr(start, end - start + 1));
                }
            }
        }

        return std::move(all_palindromes);
    }
};
}  // namespace algo

#endif