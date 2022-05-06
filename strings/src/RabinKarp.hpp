#ifndef RABIN_KARP_H
#define RABIN_KARP_H

#include <string>
#include <vector>

namespace algo {
class RabinKarp {
   public:
    static std::vector<int> search(const std::string& text,
                                   const std::string& pattern) {
        return rabin_karp(text, pattern);
    }

   private:
    static std::vector<int> rabin_karp(const std::string& text,
                                       const std::string& pattern) {
        std::vector<int> indices{};

        int len_text{static_cast<int>(text.length())};
        int len_pattern{static_cast<int>(pattern.length())};

        if (len_text == 0 || len_pattern == 0 || len_pattern > len_text)
            return std::move(indices);

        // Get the value at the highest digit (i.e. 256 ^ (len_pattern - 1))
        int prime{101};
        int highest_digit{1};
        for (int digit{0}; digit < len_pattern - 1; digit++)
            highest_digit = (256 * highest_digit) % prime;

        // Compute hashes of text and pattern
        int hash_text{0}, hash_pattern{0};
        for (int idx{0}; idx < len_pattern; idx++) {
            hash_text = (256 * hash_text + static_cast<int>(text[idx])) % prime;
            hash_pattern =
                (256 * hash_pattern + static_cast<int>(pattern[idx])) % prime;
        }

        for (int text_idx{0}; text_idx <= len_text - len_pattern; text_idx++) {
            if (hash_text == hash_pattern) {
                // Might be a pattern
                int pattern_idx{0};
                for (; pattern_idx < len_pattern; pattern_idx++)
                    if (text[text_idx + pattern_idx] != pattern[pattern_idx])
                        break;

                if (pattern_idx == len_pattern) {
                    // Found
                    indices.push_back(text_idx);
                }
            }

            // Compute next hash of the text
            if (text_idx < len_text - len_pattern) {
                hash_text =
                    (256 * (hash_text -
                            highest_digit * static_cast<int>(text[text_idx]))) %
                    prime;
                hash_text +=
                    static_cast<int>(text[text_idx + len_pattern]) % prime;

                if (hash_text < 0) hash_text += prime;
            }
        }

        return std::move(indices);
    }
};
}  // namespace algo

#endif