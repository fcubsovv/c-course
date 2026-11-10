# 📜 LINKED LISTS

# REPO STRUCTURE

```text
├── global_utils/         # Tools and useful scripts used across the project
├── matrix/               # Training with printing matrixes of different shapes
├── onegin/               # ONEGIN: Optimizing line sorting for huge textes
│   └── test_data/        # Inner folder with test samples
├── sorting               # Self-written sorting functions, include qsort, bubsort, mergesort
```

# BRIEF

АА короче вот есть список и получается что на самом деле он не нулевой изначально а с головой на которой он закольцован, можно добавлять убирать элементы из конца и начала это реализуется просто вставкой после tail/head и котороче можно еще по индексу вставлять либо отдельные элементы без сдвига массива, но это даже не главная цель, можно вставлять целые подсписки которые вот так выглядят.

Есть папка с юнит тестами, в которых есть присетнутые юнит тесты а также рандомные, после каждого юнит теста выводится вывод в формате html
