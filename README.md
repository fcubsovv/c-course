# 📦 FIRST-SEMESTER DREC CS COURSE

C course made by DED, based on project-way thinking


## 🗺️ REPO STRUCTURE

```text
├── global_utils/         # Tools and useful scripts used across the project
├── matrix/               # Training with printing matrixes of different shapes
├── onegin/               # ONEGIN: Optimizing line sorting for huge textes
│   └── test_data/        # Inner folder with test samples
├── sorting               # Self-written sorting functions, include qsort, bubsort, mergesort
├── stack                 #
```

## 🚀 QUICK START

Since this repository does not use complex build systems, every project is compiled directly using `g++` from its respective directory.

### Prerequisites
* `g++` compiler supporting C++17 / C11 standards.

### Example 1: Compiling a single project (e.g., `sorting`)
Navigate to the project folder and compile the source files directly:
```bash
cd sorting
g++ main.cpp sorting.cpp -o sorting_demo
./sorting_demo
```
