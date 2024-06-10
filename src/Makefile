CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Werror
TEST_LIBS = -lgtest
TEST_SRC = tests/tests.cc app/model/parser/parser.cc app/model/affine/affine.cc
OBJECTS = test

all: install

install:
	mkdir release;
	cp -r app/ release
	cd release; qmake s21_3DViewer_v2.pro
	make -C release
	cd release; rm -rf *.o *.cpp *.h *.pro Makefile Model View Controller *.0ccebef 
	open release

uninstall:
	rm -rf release

dvi:
	open dox/dox.pdf

dist:
	mkdir archive; cd archive; mkdir src;
	cp -r app Makefile archive/src
	[ -d release ] && cp -r release archive/src || true
	tar czf s21_3DViewer_v1.tgz archive/
	rm -rf archive

test: $(TESTS)
	$(CC) $(CFLAGS) $(TEST_SRC) $(TEST_LIBS) -o $(OBJECTS) -L. --coverage
	./test

gcov_report: test
	$(CC) --coverage $(TEST_SRC) $(TEST_LIBS) -o gсov_report.o
	./gсov_report.o
	lcov --ignore-errors mismatch -t $(OBJECTS) -o s21_3DViewer_tests.info --no-external -c -d .
	genhtml -o report s21_3DViewer_tests.info
	open ./report/index.html

check:
	find . -name "*.h" -o -name "*.cc" -o -name "*.ccp" | xargs clang-format --style=google -n
clean:
	rm -rf test *.gcda  *.gcno *.o *.info *.tgz report qmake.stash release archive build* app/*.0ccebef

rebuild: clean all
