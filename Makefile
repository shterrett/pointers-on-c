all:
	cc -std=c99 -Wall test.c bin/repl

.PHONY: run
run: all
	./bin/test
