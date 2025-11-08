#include "ExceptionHelper.h"
#include <iostream>
#include <stdexcept>

void processException() {
    try {
        throw; // rethrow current exception to identify its type

    } catch (const std::invalid_argument& e) {
        std::cerr << "\n[ERROR] Invalid argument: " << e.what() << std::endl;

    } catch (const std::out_of_range& e) {
        std::cerr << "\n[ERROR] Out of range error: " << e.what() << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << "\n[ERROR] Runtime error: " << e.what() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "\n[ERROR] General exception: " << e.what() << std::endl;

    } catch (...) {
        std::cerr << "\n[ERROR] Unknown exception occurred." << std::endl;
    }
}