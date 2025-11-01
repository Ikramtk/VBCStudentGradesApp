#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include "Person.h"

void printHeaderAvgOnly() {
    std::cout << std::left << std::setw(12) << "Name"
              << std::left << std::setw(14) << "Surname"
              << std::right << std::setw(12) << "Final(avg.)"
              << "\n" << std::string(38, '-') << "\n";
}
void printHeaderAvgMed() {
    std::cout << std::left << std::setw(12) << "Name"
              << std::left << std::setw(14) << "Surname"
              << std::right << std::setw(14) << "Final (Avg.)"
              << " | "
              << std::right << std::setw(12) << "Final (Med.)"
              << "\n" << std::string(12+14+1+14+3+12, '-') << "\n";
}

Person generateRandomStudent(const std::string& name,
                             const std::string& surname,
                             int minHW = 3, int maxHW = 8) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> hwCount(minHW, maxHW);
    std::uniform_int_distribution<int> score(0, 10);

    int n = hwCount(gen);
    std::vector<int> hw(n);
    for (int i = 0; i < n; ++i) hw[i] = score(gen);
    int exam = score(gen);
    return Person(name, surname, hw, exam);
}

std::vector<Person> readStudentsFile(const std::string& path) {
    std::vector<Person> out;
    std::ifstream in(path);
    if (!in) {
        std::cerr << "ERROR: Could not open file '" << path << "'.\n";
        return out;
    }
    std::string line;

    if (std::getline(in, line)) {
        if (line.find("Exam") == std::string::npos &&
            line.find("HW") == std::string::npos) {
            std::istringstream ss(line);
            std::string name, surname;
            if (ss >> name >> surname) {
                std::vector<int> nums; int x;
                while (ss >> x) nums.push_back(x);
                if (!nums.empty()) {
                    int exam = nums.back(); nums.pop_back();
                    out.emplace_back(name, surname, nums, exam);
                }
            }
        }
    }
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        std::string name, surname;
        if (!(ss >> name >> surname)) continue;
        std::vector<int> nums; int x;
        while (ss >> x) nums.push_back(x);
        if (nums.empty()) continue;
        int exam = nums.back(); nums.pop_back();
        out.emplace_back(name, surname, nums, exam);
    }
    return out;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<Person> students;

    std::cout << "Data source?\n"
              << "  1) Manual input\n"
              << "  2) Random generate\n"
              << "  3) Read from Students.txt\n"
              << "Choose [1/2/3]: ";
    int src = 0; if (!(std::cin >> src)) return 0;

    if (src == 1) {
        int count;
        std::cout << "How many students? ";
        std::cin >> count;
        for (int i = 0; i < count; ++i) {
            std::cout << "\n-- Student #" << (i+1) << " --\n";
            Person p;
            std::cin >> p;                 
            students.push_back(p);
        }
    } else if (src == 2) {
        int count;
        std::cout << "How many students to generate? ";
        std::cin >> count;
        for (int i = 1; i <= count; ++i) {
            students.push_back(generateRandomStudent("Name"+std::to_string(i),
                                                     "Surname"+std::to_string(i)));
        }
    } else if (src == 3) {
        students = readStudentsFile("Students.txt");
        if (students.empty()) {
            std::cerr << "No data loaded from Students.txt\n";
        }
    } else {
        std::cout << "Invalid choice.\n";
        return 0;
    }

    std::sort(students.begin(), students.end(),
              [](const Person& a, const Person& b) {
                  if (a.name() != b.name()) return a.name() < b.name();
                  return a.surname() < b.surname();
              });

    if (!students.empty()) {
        printHeaderAvgOnly();
        for (const auto& s : students) {
            std::cout << std::left << std::setw(12) << s.name()
                      << std::left << std::setw(14) << s.surname()
                      << std::right << std::fixed << std::setprecision(2)
                      << std::setw(12) << s.finalByAverage()
                      << "\n";
        }
    }

    if (!students.empty()) {
        std::cout << "\n=== Extended output (Avg. | Med.) ===\n";
        printHeaderAvgMed();
        for (const auto& s : students) {
            std::cout << std::left << std::setw(12) << s.name()
                      << std::left << std::setw(14) << s.surname()
                      << std::right << std::fixed << std::setprecision(2)
                      << std::setw(14) << s.finalByAverage() << " | "
                      << std::setw(12) << s.finalByMedian()
                      << "\n";
        }
    }
    return 0;
}