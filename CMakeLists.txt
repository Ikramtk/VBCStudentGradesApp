cmake_minimum_required(VERSION 3.10)

# Project name
project(VBCStudentGradesApp VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
set(SOURCES
    main.cpp
    Student.cpp
    FileIO.cpp
    FileGenerator.cpp
    ExceptionHelper.cpp
)

# Header-only file (Timer.h)
set(HEADERS
    Student.h
    FileIO.h
    FileGenerator.h
    ExceptionHelper.h
    Timer.h
)

# Create executable
add_executable(VBCStudentGradesApp ${SOURCES} ${HEADERS})

# Optimization flags
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()