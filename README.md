# Student Grades Calculator — Final Project (v1.0)

This repository contains the full implementation and evolution of the *Student Grades Calculator* project.  
The goal of the project is to read student data, calculate final grades (average or median), sort students, and split them into "passed" and "failed" groups using different container types and strategies.

---

## 📌 Releases Included

### **🔹 v0.1 – Basic Version**
- Reads student data from a file.
- Calculates final grade using average or median.
- Basic sorting using vector.
- Writes passed/failed students to output files.

---

### **🔹 v0.2 – Improved Performance**
- Refactored code structure.
- Added robust error handling.
- Cleaner I/O operations.
- Added initial measurement of read/sort/split/write.

---

### **🔹 v0.25 – Container Performance Comparison**
- Added support for:
  - `std::vector`
  - `std::list`
  - `std::deque`
- Compared sorting and splitting performance for all containers.
- Implemented stable sorting for consistent outputs.
- Prepared data files: 1k, 10k, 100k, 1M, 10M students.

---

### **🔹 v1.0 – Final Optimized Version**
This is the final release of the project.  
Changes included:

#### ✔ Two splitting strategies implemented:
1. **Strategy 1 (Copy strategy):**  
   - Copies students into *two* new containers: `passed` and `failed`.  
   - Keeps original container intact.  
   - Easy but not memory efficient.

2. **Strategy 2 (Move/Erase strategy):**  
   - Moves failed students to a new container.  
   - Removes them from the original container.  
   - Only passed students remain.  
   - More memory efficient but may be slower for some containers.

#### ✔ Replaced manual loops with `<algorithm>` functions:
- `std::copy_if`
- `std::remove_if`
- `std::stable_partition`
- `std::sort`, `std::stable_sort`
- Lambdas for grade filtering

#### ✔ Performance measurement improved:
- Read time
- Sort time
- Split time
- Write time

#### ✔ Added Makefile + CMakeLists.txt for full portability.

---

## 🚀 Usage Guide

### **1. Generate test files **

Run program :
Enter 1 → Test files will be generated (students1000.txt, students10000.txt, …)
Enter 0 → Skip file generation and continue to dataset selection

### **2. Choose dataset**

1 = 1000 students<br>
2 = 10000 students<br>
3 = 100000 students<br>
4 = 1000000 students<br>
5 = 10000000 students<br>

### **3. Choose final grade method**

1 = Average<br>
2 = Median<br>

### **4. Choose container**

1 = vector<br>
2 = list<br>
3 = deque<br>

### **5. Choose strategy**

1 = Strategy 1 (copy)<br>
2 = Strategy 2 (move/remove)<br>

### **Output Files**
The program produces files such as:

students_result_vector_s1_passed.txt<br>
students_result_vector_s1_failed.txt<br>

students_result_list_s2_passed.txt<br>
students_result_list_s2_failed.txt<br>

---

## 🛠 Build Instructions

### **Using Makefile **

make
./VBCStudentGradesApp

### **Using CMake (cross-platform)**

mkdir build <br>
cd build <br>
cmake ..<br>
cmake –build <br>
./VBCStudentGradesApp<br>

---

## 📊 Performance Notes
- `vector` usually fastest for sorting + strategy 1.
- `list` performs slower due to non-contiguous memory, but efficient erasing.
- `deque` performs close to vector depending on data size.
- Strategy 2 is more memory efficient but may be slower on large datasets.

---
# 📊 Performance Comparison (Measured Results)

The performance of the program was tested on datasets of different sizes (1k, 10k, 100k, 1000k students).  
The following table summarizes the approximate execution times for each container and strategy:

| Container | Strategy | Read Time | Sort Time | Split Time | Write Time |
|----------|----------|-----------|-----------|-------------|-------------|
| **vector** | S1 | Fast | Fast | Medium | Fast |
| **vector** | S2 | Fast | Fast | **Very Fast** | Fast |
| **list** | S1 | Medium | **Slow** | Medium | Medium |
| **list** | S2 | Medium | Slow | Fast | Medium |
| **deque** | S1 | Fast | Medium | Medium | Fast |
| **deque** | S2 | Fast | Medium | Fast | Fast |


## ✔ Conclusions
- **Vector** is the fastest container overall because of contiguous memory layout.  
- **Strategy 1** is simpler but uses more memory because it creates two new containers.  
- **Strategy 2** is **more memory-efficient** because it removes failed students in-place.  
- **List** is significantly slower for sorting because list sorting requires element-by-element traversal.  
- **Deque** performs close to vector, but sometimes slower in sorting.  

Overall, the optimal combination is:  
👉 **vector + strategy 2** (best balance between speed and memory efficiency)


## 👩‍💻 Author
Ikram Outaik  
Vilnius Business College  
Programming & Internet Technologies

