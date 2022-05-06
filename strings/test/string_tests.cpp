#include <gtest/gtest.h>

#include <BoyerMoore.hpp>
#include <KnuthMorrisPratt.hpp>
#include <NaiveSearch.hpp>
#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <string>

std::string generate_rand_char(const int& num);
std::vector<int> standard_search(const std::string& text,
                                 const std::string& pattern);

std::vector<
    std::function<std::vector<int>(const std::string&, const std::string&)>>
    search_algorithms{&algo::NaiveSearch::search,
                      &algo::KnuthMorrisPratt::search,
                      &algo::BoyerMoore::search};

namespace {
TEST(SearchingTest, SimpleTextPattern) {
    std::vector<std::pair<std::string, std::string>> text_and_pattern{
        {"abababa", "aba"},
        {"abc", "abcdef"},
        {"ABABAAABAABAB", "AA"},
        {"P@TTerNabcdefP@TTerNP@TTerNabcdefabcdefabcdefabcdefP@TTerN",
         "P@TTerN"}};

    for (auto& t_and_p : text_and_pattern) {
        std::string text{t_and_p.first}, pattern{t_and_p.second};
        std::vector<int> answer{standard_search(text, pattern)};

        for (auto& algorithm : search_algorithms) {
            std::vector<int> result{algorithm(text, pattern)};
            EXPECT_EQ(answer, result);
        }
    }
}

TEST(SearchingTest, RandomTextPattern) {
    for (int len_text{0}; len_text < 1000; len_text++) {
        for (int len_pattern{0}; len_pattern < 10; len_pattern++) {
            std::string text{generate_rand_char(len_text)};
            std::string pattern(generate_rand_char(len_pattern));

            std::vector<int> answer{standard_search(text, pattern)};

            for (auto& algorithm : search_algorithms) {
                std::vector<int> result{algorithm(text, pattern)};
                EXPECT_EQ(answer, result);
            }
        }
    }
}
}  // namespace

std::string generate_rand_char(const int& num) {
    std::mt19937 rng{static_cast<unsigned int>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<int> distribution{32, 126};

    std::string rand_char{};
    for (int count{0}; count < num; count++)
        rand_char += static_cast<char>(distribution(rng));

    return std::move(rand_char);
}

std::vector<int> standard_search(const std::string& text,
                                 const std::string& pattern) {
    std::vector<int> indices{};

    int len_text{static_cast<int>(text.length())};
    int len_pattern{static_cast<int>(pattern.length())};

    if (len_text == 0 || len_pattern == 0 || len_pattern > len_text)
        return std::move(indices);

    std::size_t found_idx{text.find(pattern)};
    while (found_idx != std::string::npos) {
        indices.push_back(found_idx);
        found_idx = text.find(pattern, found_idx + 1);
    }

    return std::move(indices);
}

int main(int argc, char* argv[]) {
    std::cout << "Running tests for string algorithms" << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}