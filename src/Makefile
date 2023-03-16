CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
CHECK_FLAGS=-lcheck -lm -lpthread
GCOV_FLAGS=--coverage
ALL_FLAGS=$(CFLAGS) $(GCOV_FLAGS) $(CHECK_FLAGS)

SRCS = backend/affineTransformations.c backend/parser.c
OBJS = $(SRCS:.c=.o)

TEST_FILE = tests/test_affine.c
TEST_EXEC = test_affine

PRO_FILE = ../front/front.pro
EXEC_FILE = build/front.app/Contents/MacOS/front

.PHONY: all install uninstall tests leaks s21_viewer.a gcov_report clean rebuild

all: tests install

install:
	mkdir -p build
	cd build; qmake $(PRO_FILE); make
	./$(EXEC_FILE)

uninstall:
	rm -rf build/*

check:
	checkmk clean_mode=1 tests/test_affine.check > tests/test_affine.c

tests: $(OBJS) $(TEST_FILE) 
	$(CC) $(CFLAGS) $(CHECK_FLAGS) $(TEST_FILE) $(OBJS) -o $(TEST_EXEC)
	./$(TEST_EXEC)

leaks:
	leaks -atExit -- ./$(TEST_EXEC)

dvi:
	doxygen
	open ./documents/html/index.html

s21_viewer.a: $(OBJS)
	ar rc s21_viewer.a $(OBJS) 
	ranlib s21_viewer.a

gcov_report: $(TEST_FILE)
	$(CC) -o $(TEST_EXEC) $(SRCS) $(TEST_FILE) $(ALL_FLAGS) 
	./$(TEST_EXEC)
	geninfo *.gcda *.gcno -b . -o check_res 
	genhtml check_res -o report
	open ./report/index.html

lint:
	clang-format -n ./backend/*.c ./front/*.cpp

clean:
	rm -rf report/*
	rm -rf *.a *.out *.o test
	rm -rf backend/*o backend/*a
	rm -rf *.gcda *.gcno *.gcov check_res
	rm -rf test_affine
	rm -rf backend/a.out
	rm -rf ./documents/html

rebuild: uninstall clean all
