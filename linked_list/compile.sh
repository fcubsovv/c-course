g++ -g -Wall -Wextra -fsanitize=address,undefined main.cpp c/*.cpp unit-tests/c/*.cpp -I h -I unit-tests/h -o main
