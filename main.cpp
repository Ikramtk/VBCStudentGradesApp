#include <iostream> 
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include "Person.h"

using namespace std;

void printHeader() {
    cout << left << setw(12) << "Name"
         << setw(14) << "Surname"
         << setw(14) << "Final (Avg.)"
         << setw(14) << "Final (Med.)" << endl;
    cout << string(54, '-') << endl;
}

int main() {
    vector<Person> students;
    int choice;

    cout << "Data source?\n";
    cout << "1) Manual input\n";
    cout << "2) Random generate\n";
    cout << "3) Read from Students.txt\n";
    cout << "Choose [1/2/3]: ";
    cin >> choice;
        if (choice == 1) {
        int n;
        cout << "Enter number of students: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            Person p;
            cin >> p;
            students.push_back(p);
        }

        printHeader();
        for (const auto& s : students) {
            cout << left << setw(12) << s.name()
                 << setw(14) << s.surname()
                 << setw(14) << fixed << setprecision(2) << s.finalByAverage()
                 << setw(14) << fixed << setprecision(2) << s.finalByMedian()
                 << endl;
        }
}

    else if (choice == 2) {
                int n;
        cout << "Enter number of students: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            string name = "Name" + to_string(i + 1);
            string surname = "Surname" + to_string(i + 1);
            vector<int> hw(5);
            for (int j = 0; j < 5; j++)
                hw[j] = rand() % 10 + 1;
            int exam = rand() % 10 + 1;
            students.emplace_back(name, surname, hw, exam);
        }

        printHeader();
        for (const auto& s : students) {
            cout << left << setw(12) << s.name()
                 << setw(14) << s.surname()
                 << setw(14) << fixed << setprecision(2) << s.finalByAverage()
                 << setw(14) << fixed << setprecision(2) << s.finalByMedian()
                 << endl;
        }
}

    else if (choice == 3) {
        ifstream file("Students.txt");
        if (!file) {
            cerr << "Error: Cannot open Students.txt file.\n";
            return 1;
        }

        string name, surname;
        int hw1, hw2, hw3, hw4, hw5, exam;
        vector<Person> studentsFromFile;

    
        string header;
        getline(file, header);

        while (file >> name >> surname >> hw1 >> hw2 >> hw3 >> hw4 >> hw5 >> exam) {
            vector<int> hw = {hw1, hw2, hw3, hw4, hw5};
            studentsFromFile.emplace_back(name, surname, hw, exam);
        }

        file.close();

        // Sort by surname then name
        sort(studentsFromFile.begin(), studentsFromFile.end(),
             [](const Person& a, const Person& b) {
                 if (a.surname() == b.surname())
                     return a.name() < b.name();
                 return a.surname() < b.surname();
             });

        printHeader();
        for (const auto& s : studentsFromFile) {
            cout << left << setw(12) << s.name()
                 << setw(14) << s.surname()
                 << setw(14) << fixed << setprecision(2) << s.finalByAverage()
                 << setw(14) << fixed << setprecision(2) << s.finalByMedian()
                 << endl;
        }
  }

    else {
        cout << "Invalid choice.\n";
    }

    cout << "Press any key to continue...";
    cin.ignore();
    cin.get();
    return 0;
}