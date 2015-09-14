CC=/usr/lib/llvm-3.5/bin/clang

all: 
	${CC} -W -Wall -g -O3 -pedantic -std=c99 -o bin/hlisp src/*.c src/*/*.c

.PHONY: clean
clean:
	rm bin/*
