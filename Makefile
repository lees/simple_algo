
SANIT = -fsanitize=address,undefined -fno-sanitize-recover=all -g
# SANIT = 
BUILD = clang++ ${SANIT} -std=c++17 -O2 -Wall -Werror -Wsign-compare

vec.out: vec.cpp
	${BUILD} vec.cpp -o vec.out

run-vec: vec.out
	./vec.out

knapsack.out: knapsack.cpp
	${BUILD} knapsack.cpp -o knapsack.out

run-knapsack: knapsack.out
	./knapsack.out

# https://lldb.llvm.org/use/map.html#examining-variables
# lldb vec
# b main
# r
