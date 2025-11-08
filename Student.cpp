#include "Student.h"

static constexpr double HW_W = 0.4;
static constexpr double EX_W = 0.6;

Student::Student() : exam_(0) {}
Student::Student(std::string n, std::string s, std::vector<int> hw, int ex)
    : name_(std::move(n)), surname_(std::move(s)), homework_(std::move(hw)), exam_(ex) {}

Student::Student(const Student& o)
    : name_(o.name_), surname_(o.surname_), homework_(o.homework_), exam_(o.exam_) {}

Student& Student::operator=(const Student& o) {
    if (this != &o) {
        name_ = o.name_;
        surname_ = o.surname_;
        homework_ = o.homework_;
        exam_ = o.exam_;
    }
    return *this;
}

Student::~Student() = default;

double Student::average(const std::vector<int>& v) {
    if (v.empty()) return 0.0;
    long long sum = std::accumulate(v.begin(), v.end(), 0LL);
    return static_cast<double>(sum) / v.size();
}

double Student::median(std::vector<int> v) {
    if (v.empty()) return 0.0;
    std::sort(v.begin(), v.end());
    const size_t n = v.size();
    if (n % 2 == 0) return (v[n/2 - 1] + v[n/2]) / 2.0;
    return v[n/2];
}

double Student::finalByAverage() const {
    return HW_W * average(homework_) + EX_W * exam_;
}

double Student::finalByMedian() const {
    return HW_W * median(homework_) + EX_W * exam_;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << std::left  << std::setw(12) << s.name_
       << std::left  << std::setw(14) << s.surname_
       << std::right << std::setw(12) << std::fixed << std::setprecision(2) << s.finalByAverage()
       << std::right << std::setw(12) << std::fixed << std::setprecision(2) << s.finalByMedian();
    return os;
}
