CC=clang

all: 
	${CC} -W -Wall -O3 -pedantic -std=c99 -o bin/hlisp src/*.c

.PHONY: clean
clean:
	rm bin/*
