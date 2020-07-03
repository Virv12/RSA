run: main
	./main

main: main.cpp
	clang++ -std=c++20 -Ofast -Wall -Wextra -Wpedantic -Wshadow -o $@ $^

clean:
	rm -rf main

.PHONY: run clean
