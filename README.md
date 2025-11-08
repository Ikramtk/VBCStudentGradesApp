# Student Points Calculator — Release v0.2

This version extends v0.1 with:
- Code refactoring into multiple translation units (`Student`, `FileIO`, `FileGenerator`, `ExceptionHelper`, `Timer`, `main`).
- Exception handling for file I/O and generic failures.
- Performance measurement: read, sort, split, write, total.
- Random generation of four datasets: 1k, 10k, 100k, 1M, 10M (`NameN SurnameN` with random HW/Exam 1..10).
- Sorting by Name/Surname, splitting into Passed (>=5.0) and Failed (<5.0).
- Outputs two files: `students_result_passed.txt` and `students_result_failed.txt`.

## Build
```bash
g++ main.cpp Student.cpp FileIO.cpp FileGenerator.cpp ExceptionHelper.cpp -o VBCStudentGradesApp```

## Run
1) Generate datasets:
```
./VBCStudentGradesApp
# answer: 1
```
2) Analyze a dataset:
```
./VBCStudentGradesApp
# answer: 0
# choose file and method
```
