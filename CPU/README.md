# 🚀 CPU

Project consists of two separate parts:
    1. DESCRIPTOR - creates from text commands to int commands
    2. PERFORMER - performs commands from int file

brief:

    About DESCRIPTOR:
        Using onege-reader, получает из каждой строки команду-тип аргумента-аргумент и записывает это в бинарный файл в соответствии со структурой CommandEntrails. Для обработки меток была выбрана двупроходная система, в первом прохоже формируется массив меток, во втором подставляется их значения.

        Метки оформляются двоеточием в конце aka:
        example {
            loop:
            JE loop
        }

        Комментарии оформляются ;
        После ; команда больше не читается.
        При успешном выполнении выводит "description finished successfully." иначе - ErrorDump

    About PERFORMER
        Читает из бинарного файла команда-тип аргумента команды-аргумент.
        Работа performer по сути является state machine, так как исполнитель (Handler) команды возвращает следующее состояние процессора. На данный момент так как нету вложенных команд это только ошибки и чтение следующей команды.
        Благодаря этому добавление команд является очень простым - надо создать функцию handler и добавить объявление команды в массив команд.
        При успешном выполнении выводит "performance finished successfully." иначе - ErrorDump

Features:

    Одной из наиболее важных в проекте вещей являются состояния. На данный момент это состояния allright, состояния исполнения команд, и ошибки.

    Массив команд имеет вид {"COMMAND NAME", command_number_cpu, CommandHandler}

    В файле tricks можно найти кодогенерацию для всяких приколов, чтобы их посмотреть нужно добавлять в descript.cpp нужные функции - которые генерируют код в test-data для реализации тех самых tricks


About file structure:

```text
├── c/                  #
│   └── handlers.cpp    # Handlers functions
│   └── errors.cpp      # Error dump
│   └── tricks.cpp      # Tricks
│   └── descriptor.cpp  #
│   └── performer.cpp   #
├── h/                  # headers
│   └── _FILES_.h       # тут пути к файлам из которых рисуют, читают
│   └── commands.h      # commands array
│   └── cpu.h           # states, cpu initialisation
├── test-data/
│   └── test-pics/      #
├── descript.cpp        #
├── perform.cpp         #
```


Compiling:
    set -e

    SRC="c/*.cpp ../global_utils/*.cpp"
    INC="-I h -I ../stack/h -I ../global_utils"
    LIBS="-L ../stack/c -lstack $(pkg-config --cflags --libs raylib)"

    g++ descript.cpp $SRC $INC $LIBS -o assembler
    g++ perform.cpp       $SRC $INC $LIBS -o cpu

Start:
    ./compile.sh && ./assembler && ./cpu
