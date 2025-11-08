#include "ExceptionHelper.h"
#include <iostream>
#include <exception>

void processException() {
    try {
        throw;
    } catch (const std::exception& e) {
        std::cerr << "\n[ERROR] Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "\n[ERROR] Unknown exception occurred." << std::endl;
    }
}