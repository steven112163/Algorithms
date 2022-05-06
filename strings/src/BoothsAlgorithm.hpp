#ifndef BOOTHS_ALGORITHM_H
#define BOOTHS_ALGORITHM_H

#include <string>
#include <vector>

namespace algo {
class BoothsAlgorithm {
   public:
    static std::string rotate(const std::string& text) {
        return std::move(booths_algorithm(text));
    }

   private:
    static std::string booths_algorithm(const std::string& text) {
        std::string concate_text{text + text};
        std::vector<int> failure_function(concate_text.length(), -1);

        int rotation{0};

        // If we romove all lines which modify rotation (i.e. rotation remains
        // 0), the loop will result in the KMP preprocessing function.
        for (int j{1}; j < concate_text.length(); j++) {
            int i{failure_function[j - 1 - rotation]};

            while (i != -1 &&
                   concate_text[i + 1 + rotation] != concate_text[j]) {
                if (concate_text[j] < concate_text[i + 1 + rotation])
                    rotation = j - i - 1;
                i = failure_function[i];
            }

            if (concate_text[i + 1 + rotation] != concate_text[j]) {
                // i == -1
                if (concate_text[j] < concate_text[rotation]) rotation = j;
                failure_function[j - rotation] = -1;
            } else {
                failure_function[j - rotation] = i + 1;
            }
        }

        return std::move(text.substr(rotation) + text.substr(0, rotation));
    }
};
}  // namespace algo

#endif