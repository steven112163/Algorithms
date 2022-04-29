#include <BubbleSort.hpp>
#include <InsertionSort.hpp>
#include <SelectionSort.hpp>
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
#define NUM_INT 10000

std::vector<int> generate_rand_int(const int& start, const int& end,
                                   const int& num);

void display_progress_bar(const int& round);

int main(int argc, char* argv[]) {
    // Sorting algorithms
    std::unordered_map<std::string, std::function<void(std::vector<int>&)>>
        algorithms{{"Bubble Sort", &BubbleSort::sort},
                   {"Selection Sort", &SelectionSort::sort},
                   {"Insertion Sort", &InsertionSort::sort}};

    // Execution time
    std::unordered_map<std::string, std::vector<double>> records{};

    for (int round{0}; round < ROUND; round++) {
        // Display progress
        display_progress_bar(round);

        using namespace std::chrono;

        // Get vector of random integers
        std::vector<int> rand_int{generate_rand_int(-1000, 1000, NUM_INT)};

        for (auto& algo : algorithms) {
            // Copy the vector of random integers
            std::vector<int> copy_rand_int{rand_int};

            // Record the start time
            high_resolution_clock::time_point start{
                high_resolution_clock::now()};

            // Sort the vector of random integers
            algo.second(copy_rand_int);

            // Record the end time
            high_resolution_clock::time_point end{high_resolution_clock::now()};

            // Compute the elaped time
            duration<double> time_span{
                duration_cast<duration<double>>(end - start)};

            // Record the elapsed time
            records[algo.first].push_back(time_span.count());
        }

        // Record the start time
        high_resolution_clock::time_point start{high_resolution_clock::now()};

        // Sort the vector of random integers
        std::sort(rand_int.begin(), rand_int.end());

        // Record the end time
        high_resolution_clock::time_point end{high_resolution_clock::now()};

        // Compute the elaped time
        duration<double> time_span{
            duration_cast<duration<double>>(end - start)};

        // Record the elapsed time
        records["C++ Sort"].push_back(time_span.count());
    }

    // Display the results
    std::cout << "\r=============== Results ===============\n";
    for (auto& r : records)
        std::cout << r.first << "\t" << std::setprecision(8)
                  << r.second[static_cast<int>(ROUND / 2)] << "\tseconds\n";
    std::cout << "=======================================" << std::endl;
}

std::vector<int> generate_rand_int(const int& start, const int& end,
                                   const int& num) {
    std::mt19937 rng{static_cast<unsigned int>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<int> distribution{start, end};

    std::vector<int> rand_int{};
    for (int count{0}; count < num; count++)
        rand_int.push_back(distribution(rng));

    return std::move(rand_int);
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