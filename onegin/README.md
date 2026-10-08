# СЕКРЕТ о котором молчат СЕНЬOРЫ: как рвать туза ВСЕМ на реп баттлах:


## 🚀 ONEGIN: optimizing line sorting for huge textes
 First wholesome task of the course, sharps skills of working with string arrays, include complex work with pointers, void pointers, structures and working with files.

## 🗺️ PROJECT STRUCTURE

```text
├── test_data/           # test samples
├── comparators.cpp      # basically comp functions
├── main.cpp             # main script
├── output_file.txt      # resulting file
```
### Prerequisites
* `g++` compiler supporting C++17 / C11 standards.

### Example:
Navigate to the onegin folder and compile the source files directly:
```bash
cd onegin
g++ main.cpp main.cpp -o demo
```
#### Now you can sort various textes from files using flags:
* First flag - file location
* All following flags: sort modes: acc decc or straight
#### Example:

```bash
./demo test_data/eugene.txt decc acc decc acc straight
```
Will write to an output_file.txt decc, acc than decc, acc and than straight version of the text
Command rhyme creates Pushkin-like 14-line strophe from random Onegin lines

### Notes
* Eugene Oneging text is located in zheka_washed.txt file
* All the results may be found in file output_file.txt

