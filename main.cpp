#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Person.h"

std::vector<Person> readStudentsFile(const std::string& path) {
    std::vector<Person> out;
    std::ifstream in(path);
    if (!in) {
        std::cerr << "ERROR: Could not open file '" << path << "'.\n";
        return out;
    }

    std::string line;
    std::getline(in, line); // Skip header line

    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        std::string name, surname;
        ss >> name >> surname;

        std::vector<int> hw;
        int score;
        while (ss >> score) hw.push_back(score);
        if (hw.empty()) continue;

        int exam = hw.back();
        hw.pop_back();

        out.emplace_back(name, surname, hw, exam);
    }
    return out;
}

void printHeaderAvgMed() {
    std::cout << "\n=== Extended output (Avg. | Med.) ===\n";
    std::cout << std::left << std::setw(12) << "Name"
              << std::left << std::setw(14) << "Surname"
              << std::right << std::setw(14) << "Final (Avg.) |"
              << std::setw(12) << "Final (Med.)" << "\n";
    std::cout << std::string(56, '-') << "\n";
}

void printHeaderAvgOnly() {
    std::cout << "\n=== Final grades by Average ===\n";
    std::cout << std::left << std::setw(12) << "Name"
              << std::left << std::setw(14) << "Surname"
              << std::right << std::setw(12) << "Final (Avg.)"
              << "\n";
    std::cout << std::string(38, '-') << "\n";
}

int main() {
    std::vector<Person> students;
    std::cout << "Data source?\n"
              << "  1) Manual input\n"
              << "  2) Random generate\n"
              << "  3) Read from Students.txt\n"
              << "Choose [1/2/3]: ";

    int src = 0;
    std::cin >> src;

    if (src == 3) {
        students = readStudentsFile("Students.txt");
        if (students.empty()) {
            std::cerr << "File is empty or unreadable!\n";
            return 1;
        }
    }
    else if (src == 1) {
        int n;
        std::cout << "Enter number of students: ";
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            Person p;
            std::cin >> p;
            students.push_back(p);
        }
    }
    else if (src == 2) {
        int n;
        std::cout << "Enter number of students to generate: ";
        std::cin >> n;

        for (int i = 0; i < n; ++i) {
            std::string name = "Student" + std::to_string(i + 1);
            std::string surname = "Random" + std::to_string(i + 1);

            std::vector<int> hw;
            int numHW = rand() % 5 + 3; // between 3 and 7
            for (int j = 0; j < numHW; ++j)
                hw.push_back(rand() % 10 + 1);

            int exam = rand() % 10 + 1;
            students.emplace_back(name, surname, hw, exam);
        }
    }

    if (students.empty()) {
        std::cerr << "No data found.\n";
        return 1;
    }

    // Sort by name
    std::sort(students.begin(), students.end(),
              [](const Person& a, const Person& b) { return a.name() < b.name(); });

    // Output results (Average + Median)
    printHeaderAvgMed();
    for (const auto& s : students) {
        std::cout << std::left << std::setw(12) << s.name()
                  << std::left << std::setw(14) << s.surname()
                  << std::right << std::fixed << std::setprecision(2)
                  << std::setw(14) << s.finalByAverage() << " | "
                  << std::setw(12) << s.finalByMedian()
                  << "\n";
    }

    return 0;
}