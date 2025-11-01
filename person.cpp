#include "Person.h"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>

static constexpr double HW_WEIGHT = 0.4;
static constexpr double EX_WEIGHT = 0.6;

Person::Person() : exam_(0) {}

Person::Person(const std::string& name, const std::string& surname,
               const std::vector<int>& homework, int exam)
    : name_(name), surname_(surname), homework_(homework), exam_(exam) {}

Person::Person(const Person& other)
    : name_(other.name_), surname_(other.surname_),
      homework_(other.homework_), exam_(other.exam_) {}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        name_ = other.name_;
        surname_ = other.surname_;
        homework_ = other.homework_;
        exam_ = other.exam_;
    }
    return *this;
}

Person::~Person() = default;

double Person::average(const std::vector<int>& v) {
    if (v.empty()) return 0.0;
    long long sum = std::accumulate(v.begin(), v.end(), 0LL);
    return static_cast<double>(sum) / v.size();
}

double Person::median(std::vector<int> v) {
    if (v.empty()) return 0.0;
    std::sort(v.begin(), v.end());
    size_t n = v.size();
    if (n % 2 == 0) return (v[n/2 - 1] + v[n/2]) / 2.0;
    else return v[n/2];
}

double Person::finalByAverage() const {
    return HW_WEIGHT * average(homework_) + EX_WEIGHT * exam_;
}

double Person::finalByMedian() const {
    return HW_WEIGHT * median(homework_) + EX_WEIGHT * exam_;
}

std::istream& operator>>(std::istream& is, Person& p) {
    std::cout << "Enter first name: ";
    is >> p.name_;
    std::cout << "Enter surname: ";
    is >> p.surname_;
    std::cout << "Enter homework results (q to stop): ";

    p.homework_.clear();
    std::string input;
    while (true) {
        is >> input;
        if (input == "q") break;
        int val;
        std::istringstream ss(input);
        if (ss >> val && val >= 0 && val <= 10)
            p.homework_.push_back(val);
        else
            std::cout << "Invalid. Try again: ";
    }
    std::cout << "Enter exam result: ";
    is >> p.exam_;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << std::left << std::setw(12) << p.name_
       << std::left << std::setw(14) << p.surname_
       << std::right << std::setw(10) << std::fixed << std::setprecision(2)
       << p.finalByAverage();
    return os;
}