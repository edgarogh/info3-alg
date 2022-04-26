all: a234 tests

OPTIONS_COMPIL=-Wall -g -c
LIBGTEST=/usr/lib/libgtest.so

tests: tests.o lire_affichage.o ajout_cle.o a234.o $(LIBGTEST)
	gcc $(CFLAGS) -Wall -o $@ $^ -L/usr/lib -lstdc++ -lgtest -lgtest_main -pthread

a234: a234.o lire_affichage.o ajout_cle.o
	gcc -o a234 a234.o lire_affichage.o ajout_cle.o

a234.o: a234.c a234.h
	gcc $(OPTIONS_COMPIL) a234.c

tests.o: tests.cc a234.h
	gcc $(CFLAGS) -Wall -c -o $@ $<

lire_affichage.o: lire_affichage.c a234.h
	gcc $(OPTIONS_COMPIL) lire_affichage.c

ajout_cle.o : ajout_cle.c a234.h
	gcc $(OPTIONS_COMPIL) ajout_cle.c

clean:
	rm -rf a234 tests *.o *~
