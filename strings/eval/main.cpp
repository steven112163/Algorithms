#include <BoyerMoore.hpp>
#include <KnuthMorrisPratt.hpp>
#include <NaiveSearch.hpp>
#include <algorithm>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#define ROUND 20
#define LEN_TEXT 100000000
#define LEN_PATTERN 1000

std::string generate_rand_char(const int& num);
std::vector<int> standard_search(const std::string& text,
                                 const std::string& pattern);
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
            {"Naive Algorithm", &algo::NaiveSearch::search},
            {"Knuth-Morris-Pratt Algorithm", &algo::KnuthMorrisPratt::search},
            {"Boyer-Moore Algorithm", &algo::BoyerMoore::search}};

    // Execution time
    std::unordered_map<std::string, std::vector<double>> search_records{};

    for (int round{0}; round < ROUND; round++) {
        // Display progress
        display_progress_bar(round);

        using namespace std::chrono;

        // Generate random text and pattern
        std::string text{generate_rand_char(LEN_TEXT)};
        std::string pattern{generate_rand_char(LEN_PATTERN)};

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
    }

    // Sort the algorithms by median searching time
    std::vector<std::pair<std::string, double>> search_results{
        extract_results(search_records)};

    // Display the results
    std::cout << "\r======================= Results =======================\n";
    for (auto& r : search_results) {
        std::cout << r.first;

        if (r.first == "Knuth-Morris-Pratt Algorithm")
            std::cout << "\t";
        else if (r.first == "Boyer-Moore Algorithm")
            std::cout << "\t\t";
        else
            std::cout << "\t\t\t";

        std::cout << std::fixed << std::setprecision(8) << r.second
                  << "\tseconds\n";
    }
    std::cout << "======================================================="
              << std::endl;
}

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