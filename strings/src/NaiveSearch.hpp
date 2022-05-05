#ifndef NAIVE_SEARCH_H
#define NAIVE_SEARCH_H
#include <string>
#include <vector>

namespace algo {
class NaiveSearch {
   public:
    static std::vector<int> search(const std::string& text,
                                   const std::string& pattern) {
        return naive_search(text, pattern);
    }

   private:
    static std::vector<int> naive_search(const std::string& text,
                                         const std::string& pattern) {
        std::vector<int> indices{};

        int len_text{static_cast<int>(text.length())};
        int len_pattern{static_cast<int>(pattern.length())};

        if (len_text == 0 || len_pattern == 0 || len_pattern > len_text)
            return std::move(indices);

        for (int text_idx{0}; text_idx < len_text; text_idx++) {
            bool found = true;
            for (int pattern_idx{0}; pattern_idx < len_pattern; pattern_idx++) {
                if (text[text_idx + pattern_idx] != pattern[pattern_idx]) {
                    found = false;
                    break;
                }
            }

            if (found) indices.push_back(text_idx);
        }

        return std::move(indices);
    }
};
}  // namespace algo

#endif