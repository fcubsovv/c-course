g++ -O1 -g -Wall -Wextra -pedantic -fsanitize=address,undefined main.cpp c/*.cpp ../global_utils/*.cpp -I h -I ../global_utils -o main
