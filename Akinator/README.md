# 📜 LINKED LISTS

# REPO STRUCTURE

```text
├── c/                    # исходники
├── h/                    # исходники
├── unit-tests/           # случайные тесты
│   └── c/
│   └── h/
├── compile.sh             # скрипт компиляции
├── main.cpp               # пример использования, run тестов
├── results.html           # графический дамп работы тестов
```

# BRIEF

Реализована структура данных связный список на индексах, тесты к ней, а также графический dump с использованием Graphviz.
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

# ERRORS

├── 0   allright_list                  # ошибок нет
├── 1   cannot_open_file               # не удалось открыть файл дампа
├── 2   pop_empty_list                 # pop из пустого списка
├── 3   tryind_insert_beyond_limits    # вставка по индексу больше длины
├── 4   error_getting_memory           # не удалось выделить память
├── 5   pulling_beyond_limits          # удаление по индексу >= длины
├── 6   extra_el_in_list               # число элементов не совпадает с length
├── 7   prev_next_error                # prev и next не согласованы
├── 8   tail_error                     # tail не указывает на последний элемент
├── 9   error_prev_in_free_el          # у свободного слота prev не равен FREE
├── 10  error_capacity                 # свободные + занятые + 1 != capacity
├── 11  head_val_error                 # нулевой слот потерял POISON_VAL

Ошибки выводятся в терминал, ошибки можно найти в

```text
├── h
│   └── errors.h
├── c
│   └── errors.c
```

# VERIFICATION

Верификация происходит в функции ListVerify. Проверяются POISON_VAL, FREE_VAL, а также наличие циклов, ошибок в несовпадении или просто ошибок в length, capacity. Подробнее см.

```text
├── h
│   └── list_declaration.h
├── c
│   └── list_declaration.c
```

# ADDITIONAL

Список имеет следующий вид:
```text
list_elem {
    int el_value;
    int prev_index;
    size_t next_index;
};

list_struct {
    size_t length;
    size_t capacity;
    size_t tail;
    size_t empty_head;
    list_elem * buffer;
};
```

Доступ к подсписку пустых элементов по empty_head

При недостатке места в списке capacity удваивается.

# ABOUT TESTING
```text
├── unit-tests
│   └── tests.c
```

```text
├── RunRundomPushPopTest      # случайные push/pop, pop при 0 или числе, кратном 3, остальное push
├── RunRandomInsertByIdxTest  # случайный список, затем случайные insert/pull по индексу
```
# LAUNCH

Зависимости:
```text
brew install graphviz
```

Запуск:
```text
./compile.sh && ./main
```
