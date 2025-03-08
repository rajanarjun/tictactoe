
all: program

program: main.cpp
	@g++ main.cpp -o program -lncurses
