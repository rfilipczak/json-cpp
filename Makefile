CC = g++
CFLAGS = -std=c++2a -pedantic -Wall -Wextra -Wconversion -O3

EXAMPLE_EXEC = ./example

all:

example: ./example.cpp ./json.hpp
	$(CC) $(CFLAGS) ./example.cpp -o $(EXAMPLE_EXEC)

clean:
	rm -rf $(EXAMPLE_EXEC)

.PHONY: clean
