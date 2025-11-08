#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <iomanip>

class Student {
public:
    Student();
    Student(std::string name, std::string surname,
            std::vector<int> hw, int exam);
    Student(const Student& other);
    Student& operator=(const Student& other);
    ~Student();

    const std::string& name() const { return name_; }
    const std::string& surname() const { return surname_; }

    double finalByAverage() const;
    double finalByMedian() const;

    static double average(const std::vector<int>& v);
    static double median(std::vector<int> v);

    friend std::ostream& operator<<(std::ostream& os, const Student& s);

private:
    std::string name_;
    std::string surname_;
    std::vector<int> homework_;
    int exam_;
};

#endif
