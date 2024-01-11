CC = gcc
FLAG_C = -c
FLAG_O = -o
# ASAN = -g -fsanitize=address
FLAG_COV = --coverage
FLAG_ER = -Wall -Werror -Wextra

all: clean gcov_report

arithm.a:
	$(CC) $(FLAG_ER) $(FLAG_C) arithm.c
	ar rc arithm.a arithm.o
	ranlib arithm.a

tests: arithm.a
	$(CC) $(FLAG_ER) $(FLAG_C) test.c main.c 
	ar rc suite.a test.o
	ranlib suite.a
	$(CC) $(FLAG_ER) $(FLAG_COV) $(FLAG_O) tests arithm.a suite.a arithm.c main.o test.o -lcheck -lrt -lm -lsubunit -lpthread
	./tests

gcov_report: tests
	gcov tests-arithm*.gcda	
	gcovr -b 
	gcovr
	gcovr --html-details -o report.html

check:
	cppcheck --enable=all --force *.h *.c
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	CK_FORK=no leaks --atExit -- ./tests
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./tests

clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt
	-rm -f tests
	-rm -f report
	find . -type d -name 'tests.dSYM' -exec rm -r {} +