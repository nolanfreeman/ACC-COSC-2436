##
# ACC COSC 2436 Lab 2
#

CC=g++
CFLAGS=-pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -std=c++11 -Werror

all: main.o LinkedStack.o Node.o
	$(CC) -o output main.o LinkedStack.o Node.o $(CFLAGS)

%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o ./output

# end
