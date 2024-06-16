SOURCES = $(shell find src -name "*.c")

.PHONY: default
default: run

dist/main: $(SOURCES)
	gcc $(SOURCES) -o dist/main

.PHONY: run
run: dist/main
	./dist/main

.PHONY: clean
clean:
	rm dist/main
