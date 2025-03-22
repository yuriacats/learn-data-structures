SHELL= /bin/bash
SOURCES = $(shell find src -name "*.cpp")

.PHONY: default
default: run

dist/main: $(SOURCES)
	g++ $(SOURCES) -std=c++20 -o dist/main

.PHONY: run
run: dist/main
	./dist/main

.PHONY: check-leaks
check-leaks: dist/main
	valgrind --leak-check=full --leak-resolution=high --show-reachable=yes ./dist/main

.PHONY: time
time: dist/main
	time ./dist/main

.PHONY: test-performance
test-performance: dist/main
	./test-performance.sh

.PHONY: clean
clean:
	rm dist/main
