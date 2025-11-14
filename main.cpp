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

// Table header
static void printHeader() {
    std::cout << std::left << std::setw(12) << "Name"
              << std::setw(14) << "Surname"
              << std::right << std::setw(12) << "Final (Avg.)"
              << std::right << std::setw(12) << "Final (Med.)" << "\n"
              << std::string(50, '=') << "\n";
}

// Select final grade (avg/median)
static double finalPoints(const Student& s, int method) {
    return (method == 2) ? s.finalByMedian() : s.finalByAverage();
}

int main() {
    try {
        std::cout << "Generate test files now? (1=Yes, 0=No): ";
        int gen;
        if (!(std::cin >> gen)) throw std::invalid_argument("Invalid input.");

        if (gen == 1) {
            generateFiles();
            std::cout << "Test files generated.\n";
            return 0;
        }

        // Choose file
        std::cout << "\nChoose dataset:\n"
                  << " 1) students1000.txt\n"
                  << " 2) students10000.txt\n"
                  << " 3) students100000.txt\n"
                  << " 4) students1000000.txt\n"
                  << " 5) students10000000.txt\n"
                  << "Enter choice [1-5]: ";

        int ch;
        std::cin >> ch;
        if (ch < 1 || ch > 5) throw std::out_of_range("Choice must be 1..5");

        std::string file = (ch==1) ? "students1000.txt" :
                           (ch==2) ? "students10000.txt" :
                           (ch==3) ? "students100000.txt" :
                           (ch==4) ? "students1000000.txt" : "students10000000.txt";

        std::cout << "Method (1=Average, 2=Median): ";
        int method;
        std::cin >> method;

        std::cout << "Choose container (1=vector, 2=list, 3=deque): ";
        int ctype;
        std::cin >> ctype;

        std::cout << "Choose strategy (1=copy, 2=move/remove): ";
        int strategy;
        std::cin >> strategy;

        // Read data
        auto t_read1 = clock_type::now();
        std::vector<Student> base = readStudentsFromFile(file);
        auto t_read2 = clock_type::now();

        long long read_ms = ms(t_read1, t_read2);
        long long sort_ms = 0, split_ms = 0, write_ms = 0;

        auto isPassed = [method](const Student& s) {
            return finalPoints(s, method) >= 5.0;
        };

        // =====================================================================
        // VECTOR
        // =====================================================================
        if (ctype == 1) {
            std::cout << "\n[Container: vector]\n";
            std::vector<Student> students = base;

            // Sort
            auto s1 = clock_type::now();
            std::stable_sort(students.begin(), students.end(),
                [](const Student& a, const Student& b) {
                    return (a.name()==b.name()) ? (a.surname()<b.surname())
                                                : (a.name()<b.name());
                });
            auto s2 = clock_type::now();

            std::vector<Student> passed, failed;

            // STRATEGY 1 – COPY TO TWO CONTAINERS
            if (strategy == 1) {
                auto s3 = clock_type::now();

                std::copy_if(students.begin(), students.end(),
                             std::back_inserter(passed), isPassed);

                std::copy_if(students.begin(), students.end(),
                             std::back_inserter(failed),
                             [isPassed](const Student& s){ return !isPassed(s); });

                auto s4 = clock_type::now();
                split_ms = ms(s3, s4);
            }

            // STRATEGY 2 – MOVE/ERASE (MORE MEMORY EFFICIENT)
            else {
                auto s3 = clock_type::now();

                auto middle = std::stable_partition(students.begin(), students.end(), isPassed);
                failed.assign(middle, students.end());
                students.erase(middle, students.end());
                passed = students;

                auto s4 = clock_type::now();
                split_ms = ms(s3, s4);
            }

            // Write output
            auto w1 = clock_type::now();
            std::string pref = (strategy == 1)
                ? "students_result_vector_s1"
                : "students_result_vector_s2";
            writeStudentsToFiles(passed, failed, pref);
            auto w2 = clock_type::now();

            sort_ms  = ms(s1, s2);
            write_ms = ms(w1, w2);

            printHeader();
            for (int i = 0; i < std::min(10, (int)passed.size()); i++)
                std::cout << passed[i] << "\n";
        }

        // =====================================================================
        // LIST
        // =====================================================================
        else if (ctype == 2) {
            std::cout << "\n[Container: list]\n";

            std::list<Student> students(base.begin(), base.end());

            auto s1 = clock_type::now();
            students.sort([](const Student& a, const Student& b){
                return (a.name()==b.name()) ? (a.surname()<b.surname())
                                            : (a.name()<b.name());
            });
            auto s2 = clock_type::now();

            std::list<Student> passed, failed;

            if (strategy == 1) {
                // copy
                auto s3 = clock_type::now();

                std::copy_if(students.begin(), students.end(),
                             std::back_inserter(passed), isPassed);

                std::copy_if(students.begin(), students.end(),
                             std::back_inserter(failed),
                             [isPassed](const Student& s){ return !isPassed(s); });

                auto s4 = clock_type::now();
                split_ms = ms(s3,s4);
            }
            else {
                // move/remove
                auto s3 = clock_type::now();
                for (auto it = students.begin(); it != students.end();) {
                    if (!isPassed(*it)) {
                        failed.push_back(*it);
                        it = students.erase(it);
                    } else {
                        ++it;
                    }
                }
                passed = students;
                auto s4 = clock_type::now();
                split_ms = ms(s3,s4);
            }

            auto w1 = clock_type::now();
            std::string pref = (strategy==1)
                ? "students_result_list_s1"
                : "students_result_list_s2";
            writeStudentsToFiles(
                std::vector<Student>(passed.begin(), passed.end()),
                std::vector<Student>(failed.begin(), failed.end()),
                pref
            );
            auto w2 = clock_type::now();

            sort_ms = ms(s1,s2);
            write_ms = ms(w1,w2);
        }

        // =====================================================================
        // DEQUE
        // =====================================================================
        else if (ctype == 3) {
            std::cout << "\n[Container: deque]\n";
            std::deque<Student> students(base.begin(), base.end());

            auto s1 = clock_type::now();
            std::sort(students.begin(), students.end(),
                [](const Student& a, const Student& b){
                    return (a.name()==b.name()) ? (a.surname()<b.surname())
                                                : (a.name()<b.name());
                });
            auto s2 = clock_type::now();

            std::deque<Student> passed, failed;

            if (strategy == 1) {
                auto s3 = clock_type::now();
                for (const auto& s : students)
                    (isPassed(s) ? passed : failed).push_back(s);
                auto s4 = clock_type::now();
                split_ms = ms(s3,s4);
            } else {
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
            std::string pref = (strategy==1)
                ? "students_result_deque_s1"
                : "students_result_deque_s2";

            writeStudentsToFiles(
                std::vector<Student>(passed.begin(), passed.end()),
                std::vector<Student>(failed.begin(), failed.end()),
                pref
            );
            auto w2 = clock_type::now();

            sort_ms = ms(s1,s2);
            write_ms = ms(w1,w2);
        }

        // =====================================================================
        // Performance results
        // =====================================================================
        std::cout << "\n--- Performance (ms) ---\n";
        std::cout << "Read:   " << read_ms << "\n";
        std::cout << "Sort:   " << sort_ms << "\n";
        std::cout << "Split:  " << split_ms << "\n";
        std::cout << "Write:  " << write_ms << "\n";
        std::cout << "TOTAL:  " << (read_ms + sort_ms + split_ms + write_ms) << "\n";

        std::cout << "\nPress Enter to exit...";
        std::cin.ignore();
        std::cin.get();

    } catch (...) {
        processException();
        return 1;
    }
}