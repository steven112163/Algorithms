#include <gtest/gtest.h>

#include <BoothsAlgorithm.hpp>
#include <BoyerMoore.hpp>
#include <DynamicPalindrome.hpp>
#include <ExpandPalindrome.hpp>
#include <KnuthMorrisPratt.hpp>
#include <ManachersAlgorithm.hpp>
#include <NaivePalindrome.hpp>
#include <NaiveRotate.hpp>
#include <NaiveSearch.hpp>
#include <RabinKarp.hpp>
#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>

std::string generate_rand_char(const int& num, const int& start,
                               const int& end);
std::vector<int> standard_search(const std::string& text,
                                 const std::string& pattern);

std::vector<
    std::function<std::vector<int>(const std::string&, const std::string&)>>
    search_algorithms{&algo::NaiveSearch::search,
                      &algo::KnuthMorrisPratt::search,
                      &algo::BoyerMoore::search, &algo::RabinKarp::search};

std::vector<std::function<std::string(const std::string&)>> rotate_algorithms{
    &algo::BoothsAlgorithm::rotate};

std::vector<std::function<std::string(const std::string&)>> lps_algorithms{
    &algo::ManachersLPS::search, &algo::DynamicLPS::search,
    &algo::ExpandLPS::search};

std::vector<std::function<std::unordered_set<std::string>(const std::string&)>>
    aps_algorithms{&algo::ManachersAPS::search, &algo::DynamicAPS::search,
                   &algo::ExpandAPS::search};

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
            std::string text{generate_rand_char(len_text, 32, 126)};
            std::string pattern(generate_rand_char(len_pattern, 32, 126));

            std::vector<int> answer{standard_search(text, pattern)};

            for (auto& algorithm : search_algorithms) {
                std::vector<int> result{algorithm(text, pattern)};
                EXPECT_EQ(answer, result);
            }
        }
    }
}

TEST(LexicographicallyMinimalTest, SimpleText) {
    std::vector<std::string> texts{"abcde", "cdeab", "bbaaccaadd"};

    for (auto& t : texts) {
        std::string answer{algo::NaiveRotate::rotate(t)};

        for (auto& algorithm : rotate_algorithms) {
            std::string result{algorithm(t)};
            EXPECT_EQ(answer, result);
        }
    }
}

TEST(LexicographicallyMinimalTest, RandomText) {
    for (int len_text{0}; len_text < 1000; len_text++) {
        std::string text{generate_rand_char(len_text, static_cast<int>('a'),
                                            static_cast<int>('z'))};

        std::string answer{algo::NaiveRotate::rotate(text)};

        for (auto& algorithm : rotate_algorithms) {
            std::string result{algorithm(text)};
            EXPECT_EQ(answer, result);
        }
    }
}

TEST(PalindromeTest, SimpleLPSText) {
    std::vector<std::pair<std::string, std::string>> tests{
        {"abbaabba", "abbaabba"},
        {"abba", "abba"},
        {"babad", "bab"},
        {"cbbd", "bb"}};

    lps_algorithms.push_back(&algo::NaiveLPS::search);

    for (auto& t : tests) {
        for (auto& algorithm : lps_algorithms) {
            std::string result{algorithm(t.first)};
            EXPECT_EQ(t.second, result);
        }
    }

    lps_algorithms.pop_back();
}

TEST(PalindromeTest, RandomLPSText) {
    for (int len_text{0}; len_text < 1000; len_text++) {
        std::string text{generate_rand_char(len_text, static_cast<int>('a'),
                                            static_cast<int>('z'))};

        std::string answer{algo::NaiveLPS::search(text)};

        for (auto& algorithm : lps_algorithms) {
            std::string result{algorithm(text)};
            EXPECT_EQ(answer, result);
        }
    }
}

TEST(PalindromeTest, SimpleAPSText) {
    std::vector<std::pair<std::string, std::unordered_set<std::string>>> tests{
        {"abbaabba",
         {"a", "aa", "abba", "abbaabba", "b", "baab", "bb", "bbaabb"}}};

    aps_algorithms.push_back(&algo::NaiveAPS::search);

    for (auto& t : tests) {
        for (auto& algorithm : aps_algorithms) {
            std::unordered_set<std::string> result{algorithm(t.first)};
            EXPECT_EQ(t.second, result);
        }
    }

    aps_algorithms.pop_back();
}

TEST(PalindromeTest, RandomAPSText) {
    for (int len_text{0}; len_text < 1000; len_text++) {
        std::string text{generate_rand_char(len_text, static_cast<int>('a'),
                                            static_cast<int>('z'))};

        std::unordered_set<std::string> answer{algo::NaiveAPS::search(text)};

        for (auto& algorithm : aps_algorithms) {
            std::unordered_set<std::string> result{algorithm(text)};
            EXPECT_EQ(answer, result);
        }
    }
}
}  // namespace

std::string generate_rand_char(const int& num, const int& start,
                               const int& end) {
    std::mt19937 rng{static_cast<unsigned int>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<int> distribution{start, end};

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