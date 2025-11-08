#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>

#include "Student.h"
#include "FileIO.h"
#include "FileGenerator.h"
#include "Timer.h"
#include "ExceptionHelper.h"

static void printHeader() {
    std::cout << std::left << std::setw(12) << "Name"
              << std::setw(14) << "Surname"
              << std::right << std::setw(12) << "Final (Avg.)"
              << std::right << std::setw(12) << "Final (Med.)" << "\n";
    std::cout << std::string(50, '=') << "\n";
}

int main() {
    try {
        std::cout << "Generate test files now? (1=Yes, 0=No): ";
        int gen; 
        if (!(std::cin >> gen)) return 0;
        
        if (gen == 1) {
            generateFiles();
            std::cout << "Run again to analyze files.\n";
            return 0;
        }

        std::cout << "Data source:\n";
        std::cout << " 1) students1000.txt\n";
        std::cout << " 2) students10000.txt\n";
        std::cout << " 3) students100000.txt\n";
        std::cout << " 4) students1000000.txt\n";
        std::cout << " 5) students10000000.txt\n";
        std::cout << "Choose [1/2/3/4/5]: ";

        int ch; 
        std::cin >> ch;

        std::string file;
        if      (ch == 1) file = "students1000.txt";
        else if (ch == 2) file = "students10000.txt";
        else if (ch == 3) file = "students100000.txt";
        else if (ch == 4) file = "students1000000.txt";
        else              file = "students10000000.txt";

        std::cout << "Method (1=Average, 2=Median): ";
        int method; 
        std::cin >> method;

        auto t1 = clock_type::now();
        auto students = readStudentsFromFile(file);
        auto t2 = clock_type::now();

        std::stable_sort(students.begin(), students.end(),
            [](const Student& a, const Student& b){
                if (a.name() == b.name()) return a.surname() < b.surname();
                return a.name() < b.name();
            });

        auto t3 = clock_type::now();

        std::vector<Student> passed, failed;
        passed.reserve(students.size());
        failed.reserve(students.size());

        for (const auto& s : students) {
            const double f = (method == 2) ? s.finalByMedian() : s.finalByAverage();
            if (f >= 5.0) passed.push_back(s);
            else failed.push_back(s);
        }

        auto t4 = clock_type::now();
        writeStudentsToFiles(passed, failed, "students_result");
        auto t5 = clock_type::now();

        printHeader();
        const int show = std::min<int>(10, static_cast<int>(students.size()));
        for (int i = 0; i < show; ++i) std::cout << students[i] << "\n";

        std::cout << "\n--- Performance (ms) ---\n";
        std::cout << "Read:  " << ms(t1, t2) << "\n";
        std::cout << "Sort:  " << ms(t2, t3) << "\n";
        std::cout << "Split: " << ms(t3, t4) << "\n";
        std::cout << "Write: " << ms(t4, t5) << "\n";
        std::cout << "TOTAL: " << ms(t1, t5) << "\n";

        std::cout << "\nFiles created: students_result_passed.txt / students_result_failed.txt\n";
        std::cout << "Press Enter to exit...";
        std::cin.ignore(); 
        std::cin.get();

    } catch (...) {
        processException();
        std::cout << "Press Enter to exit...";
        std::cin.ignore(); 
        std::cin.get();
        return 1;
    }

    return 0;
}