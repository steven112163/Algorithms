#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#include <string>
#include <vector>

namespace algo {
class BoyerMoore {
   public:
    static std::vector<int> search(const std::string& text,
                                   const std::string& pattern) {
        return boyer_moore(text, pattern);
    }

   private:
    static std::vector<int> boyer_moore(const std::string& text,
                                        const std::string& pattern) {
        std::vector<int> indices{};

        int len_text{static_cast<int>(text.length())};
        int len_pattern{static_cast<int>(pattern.length())};

        if (len_text == 0 || len_pattern == 0 || len_pattern > len_text)
            return std::move(indices);

        std::vector<int> bad_char_table{bad_char(pattern, len_pattern)};
        std::vector<int> good_suffix_table{good_suffix(pattern, len_pattern)};

        int text_idx{0}, pattern_idx{};
        while (text_idx <= len_text - len_pattern) {
            pattern_idx = len_pattern - 1;

            // Compare the text with the pattern from right to left
            while (pattern_idx > -1 &&
                   pattern[pattern_idx] == text[text_idx + pattern_idx])
                pattern_idx--;

            if (pattern_idx < 0) {
                // Pattern found
                indices.push_back(text_idx);

                int bad_shift =
                    (text_idx + len_pattern < len_text)
                        ? len_pattern -
                              bad_char_table[text[text_idx + len_pattern]]
                        : 1;
                int good_shift{good_suffix_table[0]};

                text_idx += std::max(bad_shift, good_shift);
            } else {
                // Pattern not found
                int bad_shift{std::max(
                    1, pattern_idx -
                           bad_char_table[text[text_idx + pattern_idx]])};
                int good_shift{good_suffix_table[pattern_idx + 1]};
                text_idx += std::max(bad_shift, good_shift);
            }
        }

        return std::move(indices);
    }

    static std::vector<int> bad_char(const std::string& pattern,
                                     const int& len_pattern) {
        std::vector<int> bad_char_table(256, -1);

        // Record the last occurance of the char
        for (int idx{0}; idx < len_pattern; idx++)
            bad_char_table[static_cast<int>(pattern[idx])] = idx;

        return std::move(bad_char_table);
    }

    static std::vector<int> good_suffix(const std::string& pattern,
                                        const int& len_pattern) {
        int i{len_pattern}, j{len_pattern + 1};
        std::vector<int> suffix_border(j);
        std::vector<int> good_suffix_table(j, 0);

        suffix_border[i] = j;
        while (i > 0) {
            while (j <= len_pattern && pattern[i - 1] != pattern[j - 1]) {
                // The characters at i - 1 and j - 1 are different, but the
                // suffix starts at i and the suffix_border starts at j are the
                // same. Thus, we can shift the pattern from j to i. Only update
                // the good_suffix table once.
                if (good_suffix_table[j] == 0) good_suffix_table[j] = j - i;

                // Find the suffix_border in the suffix which starts at j.
                j = suffix_border[j];
            }
            // The characters at i - 1 and j - 1 are the same, so the
            // suffix_border starting at j in the suffix which starts at i will
            // become the suffix_border starting at j - 1 in the suffix which
            // starts at i - 1.
            i--;
            j--;
            suffix_border[i] = j;
        }

        // Until now the good_suffix_table contains the distance we have to
        // shift when characters at i - 1 and j - 1 are different (i.e. suffix
        // has a different preceeding character than suffix_border does.).

        // Fill the shift if the suffix matches the prefix of the pattern
        i = 0;
        j = suffix_border[0];
        for (; i <= len_pattern; i++) {
            if (good_suffix_table[i] == 0) good_suffix_table[i] = j;

            // Use smaller suffix_border
            if (i == j) j = suffix_border[j];
        }

        return std::move(good_suffix_table);
    }
};
}  // namespace algo

#endif