#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <iostream>

class Person {
public:
    Person();
    Person(const std::string& name, const std::string& surname,
           const std::vector<int>& homework, int exam);
    Person(const Person& other);
    Person& operator=(const Person& other);
    ~Person();

    friend std::istream& operator>>(std::istream& is, Person& p);
    friend std::ostream& operator<<(std::ostream& os, const Person& p);

    double finalByAverage() const;
    double finalByMedian() const;

    static double average(const std::vector<int>& v);
    static double median(std::vector<int> v);

    const std::string& name() const { return name_; }
    const std::string& surname() const { return surname_; }

private:
    std::string name_;
    std::string surname_;
    std::vector<int> homework_;
    int exam_;
};

#endif