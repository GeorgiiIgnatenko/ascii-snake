all: main

main: main.cpp src/PageController.hpp src/GameController.hpp
	g++ main.cpp -o main -lncurses -L/lib/libncurses.a
