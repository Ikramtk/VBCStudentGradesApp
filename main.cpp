#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Person.h"

int main() {
    int n;
    std::cout << "Enter number of students: ";
    std::cin >> n;

    std::vector<Person> students;
    for (int i = 0; i < n; ++i) {
        Person p;
        std::cin >> p;
        students.push_back(p);
    }

    std::sort(students.begin(), students.end(),
              [](const Person& a, const Person& b) {
                  if (a.name() != b.name()) return a.name() < b.name();
                  return a.surname() < b.surname();
              });

    std::cout << "\nName        Surname       Final(Avg.)\n";
    std::cout << "--------------------------------------\n";
    for (const auto& s : students)
        std::cout << s << "\n";

    return 0;
}