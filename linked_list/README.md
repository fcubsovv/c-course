# 📜 LINKED LISTS

# REPO STRUCTURE

```text
├── с/                    # исходники
├── h/                    # исходники
├── unit-tests/           # случайные тесты
│   └── c/
│   └── h/
├── compile.sh             # скрипт компиляции
├── main.cpp               # пример использования, run тестов
├── result.html            # графический дамп работы тестов
```

# BRIEF

Реализована структура данных связный список на индексах, тесты к ней, а также графический dump с использованием graph_phys.
Ошибки выводятся терминал согласно их кодам.

# FUNCTIONS

```text
├── HandleListConstruct_list_handlers  (list_struct * list)                                     #конструктор
├── HandleDestruct_list_handlers       (list_struct * list)                                     #деструктор
├── HandleListPush_list_handlers       (list_struct * list, int value)                          #добавление элемента в конец списка
├── HandleListPop_list_handlers        (list_struct * list, int * gotten_val)                   #удаление элемента из конца списка
├── HandleInsertByIndex_list_handlers  (list_struct * list, size_t index, int value)            #вставка элемента по индексу
├── HandlePullElByIndex_list_handles   (list_struct * list, size_t index, int * gotten_val)     #удаление+получение элемента по индексу
```

смотри /c/list_handlers

# LAUNCH

```text
./compile.sh && ./main
```
