## 🎓 Student Points Calculator — Release v0.25

This version improves **v0.2** with better exception handling, user input validation, and cleaner code structure.

---

## 🆕 What's New in v0.25
- Added exception handling for:
  - `std::invalid_argument`
  - `std::out_of_range`
  - `std::runtime_error`
- Improved stability when user enters invalid input.
- Enhanced performance measurement output.
- Cleaned and organized project files.
- Support measuring performance on three containers: std::vector, std::list, std::deque.


---

## ⚙️ Build Command
```bash
g++ main.cpp Student.cpp FileIO.cpp FileGenerator.cpp ExceptionHelper.cpp -o VBCStudentGradesApp
```

---

## ▶️ Run Instructions

### 1️⃣ Generate Test Files
Run the program and choose:
```
Generate test files now? (1=Yes, 0=No): 1
```

➡️ This will create the test files:
```
students1000.txt
students10000.txt
students100000.txt
students1000000.txt
students10000000.txt
```

### 2️⃣ Analyze Dataset
Run the program again and choose:
```
Generate test files now? (1=Yes, 0=No): 0
```

Then select:
```
Choose [1-5] → dataset to analyze
Method (1=Average, 2=Median) → calculation method
```
Then select:
```
Container (1=vector, 2=list, 3=deque)
```
---

### Author

Ikram Outaik
Vilnius Business College — Programming and Internet Technologies
