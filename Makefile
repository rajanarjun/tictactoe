
all: program

program: main.cpp
	@g++ main.cpp -o program -lncurses

clean:
	@echo "Removing old binary"
	@rm program
