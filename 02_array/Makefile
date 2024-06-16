SOURCES = $(shell find src -name "*.c")
SHELL = /bin/bash
.PHONY: default
default: run

dist/main: $(SOURCES)
	gcc $(SOURCES) -o dist/main

.PHONY: run
run: dist/main
	./dist/main

.PHONY: check-leaks
check-leaks: dist/main
	valgrind --leak-check=full --leak-resolution=high --show-reachable=yes ./dist/main

.PHONY: time
time: dist/main
	time ./dist/main

.PHONY: clean
clean:
	rm dist/main
