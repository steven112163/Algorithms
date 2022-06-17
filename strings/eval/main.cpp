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
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define ROUND 20
#define LEN_TEXT 100000000
#define LEN_PATTERN 1000
#define LEN_TEXT_FOR_ROTATION 100000
#define LEN_TEXT_FOR_PALINDROME 10000

std::string generate_rand_char(const int& num, const int& start,
                               const int& end);

std::vector<int> standard_search(const std::string& text,
                                 const std::string& pattern);

void display_results(
    const std::vector<std::pair<std::string, double>>& search_results,
    const std::vector<std::pair<std::string, double>>& rotate_results,
    const std::vector<std::pair<std::string, double>>& lps_results,
    const std::vector<std::pair<std::string, double>>& aps_results);
void display_progress_bar(const int& round);
std::vector<std::pair<std::string, double>> extract_results(
    const std::unordered_map<std::string, std::vector<double>>& records);

int main(int argc, char* argv[]) {
    // Pattern searching algorithms
    std::unordered_map<
        std::string,
        std::function<std::vector<int>(const std::string&, const std::string&)>>
        search_algorithms{
            {"C++ Find", &standard_search},
            {"Naive Pattern Searching", &algo::NaiveSearch::search},
            {"Knuth-Morris-Pratt Algorithm", &algo::KnuthMorrisPratt::search},
            {"Boyer-Moore Algorithm", &algo::BoyerMoore::search},
            {"Rabin-Karp Algorithm", &algo::RabinKarp::search}};

    // Lexicographically minimal string rotation algorithms
    std::unordered_map<std::string,
                       std::function<std::string(const std::string&)>>
        rotate_algorithms{
            {"Naive Rotation", &algo::NaiveRotate::rotate},
            {"Booth's Algorithm", &algo::BoothsAlgorithm::rotate}};

    // Palindrome searching algorithms
    std::unordered_map<std::string,
                       std::function<std::string(const std::string&)>>
        lps_algorithms{{"Naive Palindrome", &algo::NaiveLPS::search},
                       {"Expand Around Center", &algo::ExpandLPS::search},
                       {"Dynamic Programming", &algo::DynamicLPS::search},
                       {"Manacher's Algorithm", &algo::ManachersLPS::search}};
    std::unordered_map<
        std::string,
        std::function<std::unordered_set<std::string>(const std::string&)>>
        aps_algorithms{{"Naive Palindrome", &algo::NaiveAPS::search},
                       {"Expand Around Center", &algo::ExpandAPS::search},
                       {"Dynamic Programming", &algo::DynamicAPS::search},
                       {"Manacher's Algorithm", &algo::ManachersAPS::search}};

    // Execution time
    std::unordered_map<std::string, std::vector<double>> search_records{};
    std::unordered_map<std::string, std::vector<double>> rotate_records{};
    std::unordered_map<std::string, std::vector<double>> lps_records{};
    std::unordered_map<std::string, std::vector<double>> aps_records{};

    for (int round{0}; round < ROUND; round++) {
        // Display progress
        display_progress_bar(round);

        using namespace std::chrono;

        // Generate random text and pattern
        std::string text{generate_rand_char(LEN_TEXT, 32, 126)};
        std::string pattern{generate_rand_char(LEN_PATTERN, 32, 126)};

        // Pattern searching
        for (auto& algo : search_algorithms) {
            // Record the start time
            high_resolution_clock::time_point start{
                high_resolution_clock::now()};

            algo.second(text, pattern);

            // Record the end time
            high_resolution_clock::time_point end{high_resolution_clock::now()};

            // Compute the elaped time
            duration<double> time_span{
                duration_cast<duration<double>>(end - start)};

            // Record the elapsed time
            search_records[algo.first].push_back(time_span.count());
        }

        // Generate random lowercase text
        text = generate_rand_char(LEN_TEXT_FOR_ROTATION, static_cast<int>('a'),
                                  static_cast<int>('z'));

        // Minimal rotation
        for (auto& algo : rotate_algorithms) {
            // Record the start time
            high_resolution_clock::time_point start{
                high_resolution_clock::now()};

            algo.second(text);

            // Record the end time
            high_resolution_clock::time_point end{high_resolution_clock::now()};

            // Compute the elaped time
            duration<double> time_span{
                duration_cast<duration<double>>(end - start)};

            // Record the elapsed time
            rotate_records[algo.first].push_back(time_span.count());
        }

        // Generate random lowercase text
        text = generate_rand_char(LEN_TEXT_FOR_PALINDROME,
                                  static_cast<int>('a'), static_cast<int>('z'));

        // Longest palindrome searching
        for (auto& algo : lps_algorithms) {
            // Record the start time
            high_resolution_clock::time_point start{
                high_resolution_clock::now()};

            algo.second(text);

            // Record the end time
            high_resolution_clock::time_point end{high_resolution_clock::now()};

            // Compute the elaped time
            duration<double> time_span{
                duration_cast<duration<double>>(end - start)};

            // Record the elapsed time
            lps_records[algo.first].push_back(time_span.count());
        }

        // All palindromes searching
        for (auto& algo : aps_algorithms) {
            // Record the start time
            high_resolution_clock::time_point start{
                high_resolution_clock::now()};

            algo.second(text);

            // Record the end time
            high_resolution_clock::time_point end{high_resolution_clock::now()};

            // Compute the elaped time
            duration<double> time_span{
                duration_cast<duration<double>>(end - start)};

            // Record the elapsed time
            aps_records[algo.first].push_back(time_span.count());
        }
    }

    // Sort the algorithms by median searching time
    std::vector<std::pair<std::string, double>> search_results{
        extract_results(search_records)};
    std::vector<std::pair<std::string, double>> rotate_results{
        extract_results(rotate_records)};
    std::vector<std::pair<std::string, double>> lps_results{
        extract_results(lps_records)};
    std::vector<std::pair<std::string, double>> aps_results{
        extract_results(aps_records)};

    // Display the results
    display_results(search_results, rotate_results, lps_results, aps_results);
}

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

void display_results(
    const std::vector<std::pair<std::string, double>>& search_results,
    const std::vector<std::pair<std::string, double>>& rotate_results,
    const std::vector<std::pair<std::string, double>>& lps_results,
    const std::vector<std::pair<std::string, double>>& aps_results) {
    // Pattern searching
    std::cout << "\r============== Pattern Searching Results ==============\n";
    for (auto& r : search_results) {
        std::cout << r.first;

        if (r.first == "Knuth-Morris-Pratt Algorithm")
            std::cout << "\t";
        else if (r.first == "C++ Find")
            std::cout << "\t\t\t";
        else
            std::cout << "\t\t";

        std::cout << std::fixed << std::setprecision(8) << r.second
                  << "\tseconds\n";
    }
    std::cout << "=======================================================\n"
              << std::endl;

    // Lexicographically minimal string rotation
    std::cout << "\r========== Minimal Rotations Results ==========\n";
    for (auto& r : rotate_results) {
        std::cout << r.first;

        if (r.first == "Naive Rotation")
            std::cout << "\t\t";
        else
            std::cout << "\t";

        std::cout << std::fixed << std::setprecision(8) << r.second
                  << "\tseconds\n";
    }
    std::cout << "===============================================\n"
              << std::endl;

    // Longest palindrome searching
    std::cout << "\r===== Longest Palindrome Searching Results ====\n";
    for (auto& r : lps_results) {
        std::cout << r.first << "\t" << std::fixed << std::setprecision(8)
                  << r.second << "\tseconds\n";
    }
    std::cout << "===============================================\n"
              << std::endl;

    // All palindromes searching
    std::cout << "\r====== All Palindromes Searching Results ======\n";
    for (auto& r : aps_results) {
        std::cout << r.first << "\t" << std::fixed << std::setprecision(8)
                  << r.second << "\tseconds\n";
    }
    std::cout << "===============================================" << std::endl;
}

void display_progress_bar(const int& round) {
    std::cout << "\r" << round + 1 << "/" << ROUND;

    std::cout << " [";
    static int bar_width{20};
    double progress{static_cast<double>(round + 1) / ROUND};
    int pos = bar_width * progress;
    for (int i{0}; i < bar_width; i++) {
        if (i < pos)
            std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "] " << static_cast<int>(progress * 100.0) << " %";
    std::cout.flush();
}

std::vector<std::pair<std::string, double>> extract_results(
    const std::unordered_map<std::string, std::vector<double>>& records) {
    // Get median running time
    std::vector<std::pair<std::string, double>> results{};
    for (auto& r : records)
        results.emplace_back(r.first, r.second[static_cast<int>(ROUND / 2)]);

    // Sort the algorithms by running time
    auto comp = [](std::pair<std::string, double> x,
                   std::pair<std::string, double> y) -> bool {
        return x.second < y.second;
    };
    std::sort(results.begin(), results.end(), comp);

    return results;
}