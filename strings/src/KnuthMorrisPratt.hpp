#ifndef KNUTH_MORRIS_PRATT_H
#define KNUTH_MORRIS_PRATT_H

#include <string>
#include <vector>

namespace algo {
class KnuthMorrisPratt {
   public:
    static std::vector<int> search(const std::string& text,
                                   const std::string& pattern) {
        return std::move(KMP(text, pattern));
    }

   private:
    static std::vector<int> KMP(const std::string& text,
                                const std::string& pattern) {
        std::vector<int> indices{};

        int len_text{static_cast<int>(text.length())};
        int len_pattern{static_cast<int>(pattern.length())};

        if (len_text == 0 || len_pattern == 0 || len_pattern > len_text)
            return std::move(indices);

        std::vector<int> failure_function{
            compute_failure(pattern, len_pattern)};

        int text_idx{0}, pattern_idx{0};
        while (text_idx < len_text) {
            if (text[text_idx] == pattern[pattern_idx]) {
                text_idx++;
                pattern_idx++;

                if (pattern_idx == len_pattern) {
                    indices.push_back(text_idx - len_pattern);
                    pattern_idx = failure_function[pattern_idx - 1];
                }
            } else {
                if (pattern_idx == 0)
                    text_idx++;
                else
                    pattern_idx = failure_function[pattern_idx - 1];
            }
        }

        return std::move(indices);
    }

    static std::vector<int> compute_failure(const std::string& pattern,
                                            const int& len) {
        std::vector<int> failure_function(len, 0);

        // Find the longest prefix-suffix
        // Prefix starts at 0
        // Suffix ends at idx
        for (int idx{1}; idx < len; idx++) {
            int lps_len{failure_function[idx - 1]};

            // If the characters are different, then the prefix-suffix starts at
            // 0 and ends at idx is not the longest prefix-suffix.
            while (pattern[lps_len] != pattern[idx]) {
                if (lps_len == 0) break;

                // Find the longest prefix-suffix in the prefix
                lps_len = failure_function[lps_len - 1];
            }

            if (pattern[lps_len] == pattern[idx]) {
                // The characters are the same, so the longest prefix-suffix
                // will be longer.
                failure_function[idx] = lps_len + 1;
            } else {
                // There is still no matching character, so there is no longest
                // prefix-suffix.
                failure_function[idx] = 0;
            }
        }

        return std::move(failure_function);
    }
};
}  // namespace algo

#endif