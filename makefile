all: main

main: main.cpp src/PageController.hpp
	g++ main.cpp -lncurses -o main