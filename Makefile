CC = gcc
C_OPTS = -std=gnu11 -g -Wall -Wextra -Werror -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wno-unused-variable -Wno-implicit-int-float-conversion -I./src -I./test
DOXYGEN = doxygen
DOXYGEN_CONF = Doxyfile

clean:
	rm -rf dist

prep:
	mkdir -p dist

compile: prep dist/main.c dist/lib.o

dist/main.c: src/main.c
	cp $< $@

dist/lib.o: src/lib.c
	$(CC) $(C_OPTS) -c $< -o ./dist/lib.o

doxygen: $(DOXYGEN_CONF)
	$(DOXYGEN) $(DOXYGEN_CONF)

run: compile
	$(CC) $(C_OPTS) -o ./dist/main ./dist/main.c ./dist/lib.o
	./dist/main

all: clean prep compile doxygen run

check:
	clang-format --verbose --dry-run --Werror src/* test/*
	cppcheck --enable=all --inconclusive --addon=cert \
	--error-exitcode=1 -v --suppress=unreadVariable:*/main.c \
	--suppress=knownConditionTrueFalse:*/main.c --suppress=missingIncludeSystem \
	--check-config --suppress=*:*/main.c --suppress=unmatchedSuppression:*/main.c .
	rm -rf src/*.dump

test.bin: test/test.c dist/lib.o
	$(CC) $(C_OPTS) $< dist/lib.o -o ./dist/$@ -lcheck -lm -lsubunit

test: test.bin
	./dist/test.bin
