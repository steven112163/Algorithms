#ifndef MANACHERS_ALGORITHM_H
#define MANACHERS_ALGORITHM_H

#include <string>
#include <unordered_set>
#include <vector>

namespace algo {
class ManachersLPS {
   public:
    static std::string search(const std::string& text) {
        return std::move(find_longest_palindrome_substrings(text));
    }

    static std::vector<int> manacher(const std::string& text) {
        // Transform the text: "abba" -> "#a#b#b#a#"
        // '#' represents the center of the even length palindrome
        std::string transformed_text(text.length() * 2 + 1, ' ');
        transformed_text[0] = '#';
        for (int idx{0}; idx < text.length(); idx++) {
            transformed_text[idx * 2 + 1] = text[idx];
            transformed_text[idx * 2 + 2] = '#';
        }

        // A table represents the diameter of each palindrome centered at each
        // character
        int length{static_cast<int>(transformed_text.length())};
        std::vector<int> lps_table(length, 0);

        int center{1}, max_right{2};
        for (int idx{1}; idx < length; idx++) {
            int current_left{2 * center - idx};

            lps_table[idx] =
                (idx < max_right)
                    ? std::min(max_right - idx, lps_table[current_left])
                    : 0;

            // Update palindrome length
            while (idx - 1 - lps_table[idx] > -1 &&
                   idx + 1 + lps_table[idx] < length &&
                   transformed_text[idx - 1 - lps_table[idx]] ==
                       transformed_text[idx + 1 + lps_table[idx]])
                lps_table[idx]++;

            // Update center and max_right
            if (idx + lps_table[idx] > max_right) {
                center = idx;
                max_right = idx + lps_table[idx];
            }
        }

        return std::move(lps_table);
    }

   private:
    static std::string find_longest_palindrome_substrings(
        const std::string& text) {
        std::vector<int> diameters{manacher(text)};

        std::string longest_palindrome{};
        for (int idx{0}; idx < diameters.size(); idx++) {
            int d{diameters[idx]};
            if (d > longest_palindrome.length()) {
                longest_palindrome = text.substr((idx - d) / 2, d);
            }
        }

        return std::move(longest_palindrome);
    }
};
class ManachersAPS {
   public:
    static std::unordered_set<std::string> search(const std::string& text) {
        return std::move(find_all_palindrome_substrings(text));
    }

   private:
    static std::unordered_set<std::string> find_all_palindrome_substrings(
        const std::string& text) {
        std::vector<int> diameters{ManachersLPS::manacher(text)};

        std::unordered_set<std::string> all_palindromes{};
        for (int idx{0}; idx < diameters.size(); idx++) {
            int d{diameters[idx]};
            while (d > 0) {
                all_palindromes.insert(text.substr((idx - d) / 2, d));
                d -= 2;
            }
        }

        return std::move(all_palindromes);
    }
};
}  // namespace algo

#endif