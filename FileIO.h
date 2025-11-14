#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <vector>
#include "Student.h"

std::vector<Student> readStudentsFromFile(const std::string& filename);
void writeStudentsToFiles(const std::vector<Student>& passed,
                          const std::vector<Student>& failed,
                          const std::string& prefix);

#endif
