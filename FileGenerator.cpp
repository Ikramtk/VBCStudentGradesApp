#include "FileGenerator.h"
#include <fstream>
#include <iomanip>
#include <string>
#include <random>
#include <iostream>
#include <chrono>
#include <vector>

static void generateFile(const std::string& filename, long long count) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error: cannot create " << filename << "\n";
        return;
    }

    out << std::left << std::setw(12) << "Name"
        << std::setw(14) << "Surname"
        << std::setw(6)  << "HW1"
        << std::setw(6)  << "HW2"
        << std::setw(6)  << "HW3"
        << std::setw(6)  << "HW4"
        << std::setw(6)  << "HW5"
        << std::setw(6)  << "Exam" << "\n";

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 10);

    for (long long i = 1; i <= count; ++i) {
        out << std::left << std::setw(12) << ("Name" + std::to_string(i))
            << std::setw(14) << ("Surname" + std::to_string(i))
            << std::setw(6)  << dist(rng)
            << std::setw(6)  << dist(rng)
            << std::setw(6)  << dist(rng)
            << std::setw(6)  << dist(rng)
            << std::setw(6)  << dist(rng)
            << std::setw(6)  << dist(rng)
            << "\n";
    }
    out.close();
    std::cout << "Generated: " << filename << " (" << count << " records)\n";
}

void generateFiles() {
    using namespace std::chrono;
    auto t0 = steady_clock::now();

    std::vector<long long> sizes = {1000, 10000, 100000, 1000000, 10000000};

    for (auto s : sizes) {
        std::string name = "students" + std::to_string(s) + ".txt";
        generateFile(name, s);
    }

    auto t1 = steady_clock::now();
    auto sec = duration_cast<seconds>(t1 - t0).count();
    std::cout << "All files generated in " << sec << " s\n";
}