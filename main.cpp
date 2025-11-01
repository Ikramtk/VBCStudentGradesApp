#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <random>
#include "Person.h"

using namespace std;

void printHeader() {
    cout << left << setw(12) << "Name"
         << setw(14) << "Surname"
         << setw(14) << "Final (Avg.)"
         << setw(14) << "Final (Med.)" << "\n";
    cout << "------------------------------------------------------\n";
}

int main() {
    int choice;
    cout << "Data source?\n";
    cout << "1) Manual input\n";
    cout << "2) Random generate\n";
    cout << "3) Read from Students.txt\n";
    cout << "Choose [1/2/3]: ";
    cin >> choice;

    vector<Person> students;

    if (choice == 1) {
        // Manual input
        int n;
        cout << "Enter number of students: ";
        cin >> n;

        for (int i = 0; i < n; ++i) {
            cout << "\n--- Student " << i + 1 << " ---\n";
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
                 << '\n';
        }

        system("pause");
    }

    else if (choice == 2) {
        // Random generate
        int n;
        cout << "Enter number of students to generate: ";
        cin >> n;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 10);

        for (int i = 0; i < n; ++i) {
            string name = "Name" + to_string(i + 1);
            string surname = "Surname" + to_string(i + 1);
            vector<int> hw(5);
            for (int& h : hw) h = dist(gen);
            int exam = dist(gen);

            students.emplace_back(name, surname, hw, exam);
        }

        printHeader();
        for (const auto& s : students) {
            cout << left << setw(12) << s.name()
                 << setw(14) << s.surname()
                 << setw(14) << fixed << setprecision(2) << s.finalByAverage()
                 << setw(14) << fixed << setprecision(2) << s.finalByMedian()
                 << '\n';
        }

        system("pause");
    }

    else if (choice == 3) {
        // Read from file
        ifstream input("Students.txt");
        if (!input.is_open()) {
            cerr << "❌ Error: Cannot open Students.txt! Make sure it’s in the same folder.\n";
            system("pause");
            return 1;
        }

        vector<Person> studentsFromFile;
        string name, surname;
        vector<int> hw(5);
        int exam;

        string headerLine;
        getline(input, headerLine); // skip header line

        while (input >> name >> surname >> hw[0] >> hw[1] >> hw[2] >> hw[3] >> hw[4] >> exam) {
            studentsFromFile.emplace_back(name, surname, hw, exam);
        }

        if (studentsFromFile.empty()) {
            cout << "⚠️ No student data found in Students.txt.\n";
            system("pause");
            return 0;
        }

        printHeader();
        for (const auto& s : studentsFromFile) {
            cout << left << setw(12) << s.name()
                 << setw(14) << s.surname()
                 << setw(14) << fixed << setprecision(2) << s.finalByAverage()
                 << setw(14) << fixed << setprecision(2) << s.finalByMedian()
                 << '\n';
        }

        system("pause");
    }

    else {
        cout << "Invalid choice!\n";
        system("pause");
    }

    return 0;
}