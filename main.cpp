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
        if (!(std::cin >> gen)) throw std::invalid_argument("Input must be numeric (1/0).");
        if (gen == 1) { generateFiles(); std::cout << "Files generated.\n"; return 0; }

        std::cout << "\nChoose dataset:\n"
                  << " 1) students1000.txt\n"
                  << " 2) students10000.txt\n"
                  << " 3) students100000.txt\n"
                  << " 4) students1000000.txt\n"
                  << " 5) students10000000.txt\n"
                  << "Enter choice [1-5]: ";
        int ch; 
        if (!(std::cin >> ch) || ch < 1 || ch > 5) throw std::out_of_range("Choice must be 1..5.");

        std::string file = (ch==1) ? "students1000.txt" :
                           (ch==2) ? "students10000.txt" :
                           (ch==3) ? "students100000.txt" :
                           (ch==4) ? "students1000000.txt" : "students10000000.txt";

        std::cout << "Method (1=Average, 2=Median): ";
        int method; 
        if (!(std::cin >> method) || (method != 1 && method != 2))
            throw std::invalid_argument("Method must be 1 or 2.");

        std::cout << "Container (1=vector, 2=list, 3=deque): ";
        int ctype;
        if (!(std::cin >> ctype) || ctype < 1 || ctype > 3)
            throw std::out_of_range("Container must be 1..3.");

        // Read as vector first (source of truth)
        auto t1 = clock_type::now();
        std::vector<Student> v = readStudentsFromFile(file);
        auto t2 = clock_type::now();

        long long read_ms = ms(t1, t2);
        long long sort_ms = 0, split_ms = 0, write_ms = 0;

        if (ctype == 1) {
            // vector
            std::vector<Student> students = v;
            auto s1 = clock_type::now();
            std::stable_sort(students.begin(), students.end(), [](const Student& a, const Student& b){
                return (a.name()==b.name()) ? (a.surname()<b.surname()) : (a.name()<b.name());
            });
            auto s2 = clock_type::now();

            std::vector<Student> passed, failed;
            passed.reserve(students.size());
            failed.reserve(students.size());
            for (const auto& s : students) {
                double f = (method==2) ? s.finalByMedian() : s.finalByAverage();
                (f>=5.0 ? passed : failed).push_back(s);
            }
            auto s3 = clock_type::now();

            writeStudentsToFiles(passed, failed, "students_result_vector");
            auto s4 = clock_type::now();

            sort_ms  = ms(s1, s2);
            split_ms = ms(s2, s3);
            write_ms = ms(s3, s4);

            printHeader();
            for (int i=0; i<std::min<int>(10,(int)students.size()); ++i) std::cout << students[i] << "\n";
            std::cout << "\n[Using std::vector]\n";

        } else if (ctype == 2) {
            // list
            std::list<Student> students(v.begin(), v.end());
            auto s1 = clock_type::now();
            students.sort([](const Student& a, const Student& b){
                return (a.name()==b.name()) ? (a.surname()<b.surname()) : (a.name()<b.name());
            });
            auto s2 = clock_type::now();

            std::list<Student> passed, failed;
            for (const auto& s : students) {
                double f = (method==2) ? s.finalByMedian() : s.finalByAverage();
                (f>=5.0 ? passed : failed).push_back(s);
            }
            auto s3 = clock_type::now();

            writeStudentsToFiles(
                std::vector<Student>(passed.begin(), passed.end()),
                std::vector<Student>(failed.begin(), failed.end()),
                "students_result_list"
            );
            auto s4 = clock_type::now();

            sort_ms  = ms(s1, s2);
            split_ms = ms(s2, s3);
            write_ms = ms(s3, s4);

            std::cout << "\n[Using std::list] (preview of first 10 after sort not printed for list)\n";

        } else {
            // deque
            std::deque<Student> students(v.begin(), v.end());
            auto s1 = clock_type::now();
            std::sort(students.begin(), students.end(), [](const Student& a, const Student& b){
                return (a.name()==b.name()) ? (a.surname()<b.surname()) : (a.name()<b.name());
            });
            auto s2 = clock_type::now();

            std::deque<Student> passed, failed;
            for (const auto& s : students) {
                double f = (method==2) ? s.finalByMedian() : s.finalByAverage();
                (f>=5.0 ? passed : failed).push_back(s);
            }
            auto s3 = clock_type::now();

            writeStudentsToFiles(
                std::vector<Student>(passed.begin(), passed.end()),
                std::vector<Student>(failed.begin(), failed.end()),
                "students_result_deque"
            );
            auto s4 = clock_type::now();

            sort_ms  = ms(s1, s2);
            split_ms = ms(s2, s3);
            write_ms = ms(s3, s4);

            std::cout << "\n[Using std::deque]\n";
        }

        std::cout << "\n--- Performance (ms) ---\n";
        std::cout << "Read:   " << read_ms << "\n";
        std::cout << "Sort:   " << sort_ms << "\n";
        std::cout << "Split:  " << split_ms << "\n";
        std::cout << "Write:  " << write_ms << "\n";
        std::cout << "TOTAL:  " << (read_ms + sort_ms + split_ms + write_ms) << "\n";

        std::cout << "\nOutput files (by container):\n"
                     " - students_result_vector_passed.txt / _failed.txt\n"
                     " - students_result_list_passed.txt   / _failed.txt\n"
                     " - students_result_deque_passed.txt  / _failed.txt\n";

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