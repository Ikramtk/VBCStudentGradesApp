#include "FileIO.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

std::vector<Student> readStudentsFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) throw std::ios_base::failure("Cannot open: " + filename);

    std::vector<Student> out;
    std::string header;
    std::getline(in, header); // skip header if present

    std::string name, surname;
    int hw1, hw2, hw3, hw4, hw5, exam;
    while (in >> name >> surname >> hw1 >> hw2 >> hw3 >> hw4 >> hw5 >> exam) {
        out.emplace_back(name, surname, std::vector<int>{hw1, hw2, hw3, hw4, hw5}, exam);
    }
    return out;
}

void writeStudentsToFiles(const std::vector<Student>& passed,
                          const std::vector<Student>& failed,
                          const std::string& prefix) {
    auto writeOne = [](const std::vector<Student>& vec, const std::string& path){
        std::ofstream out(path);
        if (!out) throw std::ios_base::failure("Cannot create: " + path);
        out << std::left  << std::setw(12) << "Name"
            << std::left  << std::setw(14) << "Surname"
            << std::right << std::setw(12) << "Final(Avg.)"
            << std::right << std::setw(12) << "Final(Med.)" << "\n";
        out << std::string(50, '=') << "\n";
        for (const auto& s : vec) out << s << "\n";
    };

    writeOne(passed, prefix + "_passed.txt");
    writeOne(failed, prefix + "_failed.txt");
}
