#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <string>

#include "Student.h"
#include "FileIO.h"
#include "FileGenerator.h"
#include "Timer.h"
#include "ExceptionHelper.h"

// Print table header
static void printHeader() {
    std::cout << std::left << std::setw(12) << "Name"
              << std::setw(14) << "Surname"
              << std::right << std::setw(12) << "Final (Avg.)"
              << std::right << std::setw(12) << "Final (Med.)" << "\n"
              << std::string(50, '=') << "\n";
}

// Compute final grade
static double finalPoints(const Student& s, int m) {
    return (m == 2) ? s.finalByMedian() : s.finalByAverage();
}

int main() {
    try {
        // Option to generate files
        std::cout << "Generate test files now? (1=Yes, 0=No): ";
        int gen;
        if (!(std::cin >> gen)) throw std::invalid_argument("Invalid input.");

        if (gen == 1) {
            generateFiles();
            std::cout << "Files generated.\n";
            return 0;
        }

        // Select file
        std::cout << "\nChoose dataset:\n"
                  << " 1) students1000.txt\n"
                  << " 2) students10000.txt\n"
                  << " 3) students100000.txt\n"
                  << " 4) students1000000.txt\n"
                  << " 5) students10000000.txt\n"
                  << "Enter choice [1-5]: ";

        int ch;
        std::cin >> ch;
        if (ch < 1 || ch > 5) throw std::out_of_range("Choice must be 1..5.");

        std::string file =
            (ch == 1) ? "students1000.txt" :
            (ch == 2) ? "students10000.txt" :
            (ch == 3) ? "students100000.txt" :
            (ch == 4) ? "students1000000.txt" :
                        "students10000000.txt";

        // Choose method
        std::cout << "Method (1=Average, 2=Median): ";
        int method;
        std::cin >> method;
        if (method != 1 && method != 2)
            throw std::invalid_argument("Method must be 1 or 2.");

        // Choose container
        std::cout << "Choose container (1=vector, 2=list, 3=deque): ";
        int ctype;
        std::cin >> ctype;

        // Choose strategy
        std::cout << "Choose strategy (1=copy, 2=move/remove): ";
        int strategy;
        std::cin >> strategy;

        // Load data into base vector
        auto tr1 = clock_type::now();
        std::vector<Student> base = readStudentsFromFile(file);
        auto tr2 = clock_type::now();

        long long read_ms = ms(tr1, tr2);
        long long sort_ms = 0, split_ms = 0, write_ms = 0;

        auto isPassed = [method](const Student& s) {
            return finalPoints(s, method) >= 5.0;
        };

        // ============================================================
        // VECTOR
        // ============================================================
        if (ctype == 1) {
            std::cout << "\n[Vector selected]\n";

            std::vector<Student> students = base;

            // Sort
            auto s1 = clock_type::now();
            std::stable_sort(students.begin(), students.end(),
                [](const Student& a, const Student& b) {
                    return (a.name()==b.name())
                        ? (a.surname() < b.surname())
                        : (a.name() < b.name());
                });
            auto s2 = clock_type::now();

            std::vector<Student> passed, failed;

            if (strategy == 1) {
                // Strategy 1 — COPY
                auto s3 = clock_type::now();

                std::copy_if(students.begin(), students.end(),
                             std::back_inserter(passed), isPassed);

                std::copy_if(students.begin(), students.end(),
                             std::back_inserter(failed),
                             [&](const Student& s){ return !isPassed(s); });

                auto s4 = clock_type::now();
                split_ms = ms(s3, s4);
            } 
            else {
                // Strategy 2 — MOVE/REMOVE
                auto s3 = clock_type::now();

                auto mid = std::stable_partition(students.begin(), students.end(), isPassed);

                passed.assign(students.begin(), mid);
                failed.assign(mid, students.end());
                students.erase(mid, students.end());

                auto s4 = clock_type::now();
                split_ms = ms(s3, s4);
            }

            auto w1 = clock_type::now();
            writeStudentsToFiles(passed, failed,
                (strategy==1 ? "students_vector_s1" : "students_vector_s2"));
            auto w2 = clock_type::now();

            sort_ms = ms(s1,s2);
            write_ms = ms(w1,w2);

            printHeader();
            for (int i = 0; i < std::min(10, (int)passed.size()); ++i)
                std::cout << passed[i] << "\n";
        }

        // ============================================================
        // LIST
        // ============================================================
        else if (ctype == 2) {
            std::cout << "\n[List selected]\n";
            std::list<Student> students(base.begin(), base.end());

            auto s1 = clock_type::now();
            students.sort([](const Student& a, const Student& b){
                return (a.name()==b.name())
                    ? (a.surname() < b.surname())
                    : (a.name() < b.name());
            });
            auto s2 = clock_type::now();

            std::list<Student> passed, failed;

            if (strategy == 1) {
                // COPY
                auto s3 = clock_type::now();

                std::copy_if(students.begin(), students.end(),
                             std::back_inserter(passed), isPassed);

                std::copy_if(students.begin(), students.end(),
                             std::back_inserter(failed),
                             [&](const Student& s){ return !isPassed(s); });

                auto s4 = clock_type::now();
                split_ms = ms(s3,s4);
            }
            else {
                // MOVE + ERASE
                auto s3 = clock_type::now();
                for (auto it = students.begin(); it != students.end();) {
                    if (!isPassed(*it)) {
                        failed.push_back(*it);
                        it = students.erase(it);
                    } else ++it;
                }
                passed = students;
                auto s4 = clock_type::now();
                split_ms = ms(s3,s4);
            }

            auto w1 = clock_type::now();
            writeStudentsToFiles(
                std::vector<Student>(passed.begin(), passed.end()),
                std::vector<Student>(failed.begin(), failed.end()),
                (strategy==1 ? "students_list_s1" : "students_list_s2")
            );
            auto w2 = clock_type::now();

            sort_ms = ms(s1,s2);
            write_ms = ms(w1,w2);
        }

        // ============================================================
        // DEQUE
        // ============================================================
        else if (ctype == 3) {
            std::cout << "\n[Deque selected]\n";

            std::deque<Student> students(base.begin(), base.end());

            auto s1 = clock_type::now();
            std::sort(students.begin(), students.end(),
                [](const Student& a, const Student& b){
                    return (a.name()==b.name())
                        ? (a.surname() < b.surname())
                        : (a.name() < b.name());
                });
            auto s2 = clock_type::now();

            std::deque<Student> passed, failed;

            if (strategy == 1) {
                // COPY
                auto s3 = clock_type::now();
                for (auto& st : students)
                    (isPassed(st) ? passed : failed).push_back(st);
                auto s4 = clock_type::now();
                split_ms = ms(s3,s4);
            } else {
                // MOVE/REMOVE
                auto s3 = clock_type::now();
                for (auto it = students.begin(); it != students.end();) {
                    if (!isPassed(*it)) {
                        failed.push_back(*it);
                        it = students.erase(it);
                    } else ++it;
                }
                passed = students;
                auto s4 = clock_type::now();
                split_ms = ms(s3,s4);
            }

            auto w1 = clock_type::now();
            writeStudentsToFiles(
                std::vector<Student>(passed.begin(), passed.end()),
                std::vector<Student>(failed.begin(), failed.end()),
                (strategy==1 ? "students_deque_s1" : "students_deque_s2")
            );
            auto w2 = clock_type::now();

            sort_ms = ms(s1,s2);
            write_ms = ms(w1,w2);
        }

        // ============================================================
        // RESULTS
        // ============================================================
        std::cout << "\n--- Performance (ms) ---\n";
        std::cout << "Read:   " << read_ms << "\n";
        std::cout << "Sort:   " << sort_ms << "\n";
        std::cout << "Split:  " << split_ms << "\n";
        std::cout << "Write:  " << write_ms << "\n";
        std::cout << "TOTAL:  " << (read_ms + sort_ms + split_ms + write_ms) << "\n";

        std::cout << "Press Enter to exit...";
        std::cin.ignore();
        std::cin.get();

    }
    catch (...) {
        processException();
        return 1;
    }
}