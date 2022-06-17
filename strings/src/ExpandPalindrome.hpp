#ifndef EXPAND_AROUND_CENTER_PALINDROME_H
#define EXPAND_AROUND_CENTER_PALINDROME_H

#include <string>
#include <unordered_set>
#include <vector>

namespace algo {
class ExpandLPS {
   public:
    static std::string search(const std::string& text) {
        return std::move(find_longest_palindrome_substring(text));
    }

    static int expand_around_center(const std::string& text, const int& start,
                                    const int& end) {
        int left{start}, right{end};
        while (left > -1 && right < text.length() &&
               text[left] == text[right]) {
            left--;
            right++;
        }

        return right - left - 1;
    }

   private:
    static std::string find_longest_palindrome_substring(
        const std::string& text) {
        int length{static_cast<int>(text.length())};
        std::string longest_palindrome{};

        for (int idx{0}; idx < length; idx++) {
            int len_odd = ExpandLPS::expand_around_center(text, idx, idx);
            int len_even = ExpandLPS::expand_around_center(text, idx, idx + 1);
            int len = std::max(len_odd, len_even);

            if (len > longest_palindrome.length()) {
                longest_palindrome = text.substr(idx - (len - 1) / 2, len);
            }
        }

        return std::move(longest_palindrome);
    }
};

class ExpandAPS {
   public:
    static std::unordered_set<std::string> search(const std::string& text) {
        return std::move(find_all_palindrome_substrings(text));
    }

   private:
    static std::unordered_set<std::string> find_all_palindrome_substrings(
        const std::string& text) {
        int length{static_cast<int>(text.length())};
        std::unordered_set<std::string> all_palindromes{};

        for (int idx{0}; idx < length; idx++) {
            int len_odd = ExpandLPS::expand_around_center(text, idx, idx);
            int len_even = ExpandLPS::expand_around_center(text, idx, idx + 1);

            while (len_odd > 0) {
                all_palindromes.insert(
                    text.substr(idx - (len_odd - 1) / 2, len_odd));
                len_odd -= 2;
            }
            while (len_even > 0) {
                all_palindromes.insert(
                    text.substr(idx - (len_even - 1) / 2, len_even));
                len_even -= 2;
            }
        }

        return std::move(all_palindromes);
    }
};
}  // namespace algo

#endif