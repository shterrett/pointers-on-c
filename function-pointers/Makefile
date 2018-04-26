all:
	cc -std=c99 -Wall test.c minunit.h dbg.h -o bin/test

debug:
	cc -std=c99 -Wall -g test.c minunit.h dbg.h -o bin/test
	gdb bin/test

.PHONY: run
run: all
	./bin/test
