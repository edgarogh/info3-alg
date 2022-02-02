CFLAGS=-g

all: test_abr

abr.o: abr.c abr.h pile.h file.h
	gcc $(CFLAGS) -Wall -c abr.c

pile.o: pile.h pile.c
	gcc $(CFLAGS) -Wall -c pile.c

file.o: file.h file.c abr.h
	gcc $(CFLAGS) -Wall -c file.c

test_file.o: test_file.c file.h abr.h
	gcc $(CFLAGS) -Wall -c test_file.c

test_file: test_file.o file.o file.h abr.h
	gcc $(CFLAGS) -o test_file test_file.o file.o

tests.o: tests.cc file.h pile.h abr.h
	gcc $(CFLAGS) -Wall -c -o $@ $<

LIBGTEST=/usr/lib/libgtest.a

tests: tests.o file.o pile.o abr.o $(LIBGTEST)
	gcc $(CFLAGS) -Wall -o $@ $^ -L/usr/lib -lstdc++ -lgtest -lgtest_main -pthread

$(LIBGTEST):
	@echo "libgtest n'est pas installé"
	@echo "sur Ubuntu, suivez ces instructions:"
	@echo "https://rationalcity.wordpress.com/2018/07/18/how-to-install-gtest-on-ubuntu/"
	@false

test_abr.o: test_abr.c abr.h
	gcc $(CFLAGS) -Wall -c test_abr.c

test_abr: test_abr.o pile.o file.o abr.o
	gcc $(CFLAGS) -o test_abr abr.o pile.o file.o test_abr.o

clean:
	rm -f *.o *~ test_abr test_file tests

.PHONY: run-tests
run-tests: tests
	./$<
