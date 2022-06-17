#ifndef MANACHERS_ALGORITHM_H
#define MANACHERS_ALGORITHM_H

#include <string>
#include <unordered_set>
#include <vector>

namespace algo {
class ManachersLPS {
   public:
    static std::string search(const std::string& text) {
        return std::move(find_longest_palindrome_substring(text));
    }

    static std::vector<int> manacher(const std::string& text) {
        // Transform the text: "abba" -> "#a#b#b#a#"
        std::string transformed_text{"#"};
        for (const char& ch : text) transformed_text += ch + std::string("#");

        // A table represents the radius of each palindrome centered at each
        // character
        int length{static_cast<int>(transformed_text.length())};
        std::vector<int> palindrome_radii(length, 0);

        // The idea is based on that palindrome is in another palindrome
        int center{0}, radius{0};
        while (center < length) {
            // Find the radius of the current center
            while ((center - (radius + 1) > -1) &&
                   (center + (radius + 1) < length) &&
                   (transformed_text[center - (radius + 1)] ==
                    transformed_text[center + (radius + 1)]))
                radius++;

            // Record the radius
            palindrome_radii[center] = radius;

            // Update the radii of the centers in the above palindrome
            int old_center{center};
            int old_radius{radius};
            center++;
            radius = 0;
            while (center <= old_center + old_radius) {
                int mirrored_center{old_center - (center - old_center)};
                int max_radius{old_center + old_radius - center};

                if (palindrome_radii[mirrored_center] < max_radius) {
                    // The palindrome centered at the mirrored_center is smaller
                    // than the above palindrome, so the palindrome at the
                    // center is the same as the palindrome centered at the
                    // mirrored_center
                    palindrome_radii[center] =
                        palindrome_radii[mirrored_center];
                    center++;
                } else if (palindrome_radii[mirrored_center] > max_radius) {
                    // If the palindrome centered at the center was the same as
                    // the palindrome centered at the mirrored_center, then the
                    // above palindrome should have been bigger. Thus, the
                    // palindrome centered at the center has the max_radius
                    palindrome_radii[center] = max_radius;
                    center++;
                } else {
                    // palindrome_radii[mirrored_center] == max_radius
                    // Because we don't know whether the character after the
                    // above palindrome will make the palindrome centered at the
                    // center bigger, we break the while loop to find the
                    // largest palindrome centered at the center
                    radius = max_radius;
                    break;
                }
            }
        }

        return std::move(palindrome_radii);
    }

   private:
    static std::string find_longest_palindrome_substring(
        const std::string& text) {
        std::vector<int> radii{manacher(text)};

        std::string longest_palindrome{};
        for (int idx{0}; idx < radii.size(); idx++) {
            int len{radii[idx]};
            if (len > longest_palindrome.length()) {
                longest_palindrome =
                    text.substr((idx - 1) / 2 - (len - 1) / 2, len);
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
        std::vector<int> radii{ManachersLPS::manacher(text)};

        std::unordered_set<std::string> all_palindromes{};
        for (int idx{0}; idx < radii.size(); idx++) {
            int len{radii[idx]};
            while (len > 0) {
                all_palindromes.insert(
                    text.substr((idx - 1) / 2 - (len - 1) / 2, len));
                len -= 2;
            }
        }

        return std::move(all_palindromes);
    }
};
}  // namespace algo

#endif