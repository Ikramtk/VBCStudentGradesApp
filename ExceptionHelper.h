#ifndef EXCEPTION_HELPER_H
#define EXCEPTION_HELPER_H

#include <iostream>
#include <system_error>
#include <future>
#include <new>
#include <ios>
#include <exception>

template <typename T>
inline void printCodeInfo(const T& e) {
    const auto c = e.code();
    std::cerr << "- category: " << c.category().name() << "\n"
              << "- value: "    << c.value()            << "\n"
              << "- message: "  << c.message()          << "\n";
}

void processException();  

#endif