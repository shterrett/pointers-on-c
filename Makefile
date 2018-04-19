all:
	cc -std=c99 -Wall test.c minunit.h dbg.h -o bin/test

.PHONY: run
run: all
	./bin/test
