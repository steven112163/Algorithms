#ifndef NAIVE_ROTATE_H
#define NAIVE_ROTATE_H

#include <string>

namespace algo {
class NaiveRotate {
   public:
    static std::string rotate(const std::string& text) {
        return std::move(naive_rotate(text));
    }

   private:
    static std::string naive_rotate(const std::string& text) {
        std::string minimal{text};

        for (int idx{1}; idx < text.length(); idx++) {
            std::string new_rotation{text.substr(idx) + text.substr(0, idx)};

            minimal = std::min(minimal, new_rotation);
        }

        return std::move(minimal);
    }
};
}  // namespace algo

#endif