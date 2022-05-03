#include <gtest/gtest.h>

#include <KnuthMorrisPratt.hpp>
#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <string>

std::string generate_rand_char(const int& num);
std::vector<int> naive_search(const std::string& text,
                              const std::string& pattern);

namespace {
TEST(StringTest, SearchPattern) {
    for (int len_text{0}; len_text < 1000; len_text++) {
        for (int len_pattern{0}; len_pattern < 100; len_pattern++) {
            std::string text{generate_rand_char(len_text)};
            std::string pattern(generate_rand_char(len_pattern));

            std::vector<int> answer{naive_search(text, pattern)};
            std::vector<int> result{
                algo::KnuthMorrisPratt::search(text, pattern)};

            EXPECT_EQ(answer, result);
        }
    }
}
}  // namespace

std::string generate_rand_char(const int& num) {
    std::mt19937 rng{static_cast<unsigned int>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<int> distribution{97, 122};

    std::string rand_char{};
    for (int count{0}; count < num; count++)
        rand_char += static_cast<char>(distribution(rng));

    return std::move(rand_char);
}

std::vector<int> naive_search(const std::string& text,
                              const std::string& pattern) {
    std::vector<int> indices{};

    if (text.length() == 0 || pattern.length() == 0) return std::move(indices);

    for (int text_idx{0}; text_idx < text.length(); text_idx++) {
        bool found = true;
        for (int pattern_idx{0}; pattern_idx < pattern.length();
             pattern_idx++) {
            if (text[text_idx + pattern_idx] != pattern[pattern_idx]) {
                found = false;
                break;
            }
        }

        if (found) indices.push_back(text_idx);
    }

    return std::move(indices);
}

int main(int argc, char* argv[]) {
    std::cout << "Running tests for string algorithms" << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}