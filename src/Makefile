CC = gcc
FLAG_C = -c
FLAG_O = -o
FLAG_COV = --coverage
FLAG_ER = -Wall -Werror -Wextra

all: clean s21_decimal.a

s21_decimal.a:
	$(CC) $(FLAG_ER) $(FLAG_C) s21_decimal.c arithm.c converters.c
	ar rc s21_decimal.a s21_decimal.o arithm.o converters.o
	ranlib s21_decimal.a

test: s21_decimal.a
	$(CC) $(FLAG_ER) $(FLAG_C) test.c main.c 
	ar rc suite.a test.o
	ranlib suite.a
	$(CC) $(FLAG_ER) $(FLAG_COV) $(FLAG_O) test s21_decimal.a  arithm.c converters.c  suite.a s21_decimal.c main.o test.o -lcheck -lm -lpthread
	./test

test_ubuntu: s21_decimal.a
	$(CC) $(FLAG_ER) $(FLAG_C) test.c main.c 
	ar rc suite.a test.o
	ranlib suite.a
	$(CC) $(FLAG_ER) $(FLAG_COV) $(FLAG_O) test s21_decimal.a suite.a arithm.c converters.c s21_decimal.c main.o test.o -lcheck -lsubunit -lm -lpthread
	./test


gcov_report: test_ubuntu
	gcov test-s21_*.gcda
	gcovr
	gcovr --html-details -o report.html

clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt
	-rm -f test
	-rm -f report

