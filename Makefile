# Makefile
# Reseni IJC-DU1, priklad A), B), 18. 3. 2020
# Autor: David Hurta, FIT
# Prelozeno: gcc 7.5.0
# Makefile soubor pro prekladani souboru.
# Poznamky:	make run:	- Zvetsi zasobnik v pustenem bashi na unlimited
#				- Vytvori soubory nutne pro primes a primes-k, nasledne je spusti
#		make clean:	- Smaze veskere soubory *.o a spustitelne soubory vytvorene prikazem make

CC = gcc
LDFLAGS = -lm
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra
CFLAGS_INLINE = -O2 -g -std=c11 -pedantic -Wall -Wextra -DUSE_INLINE

all: primes primes-i steg-decode

# Zadani A - makra
primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) primes.o eratosthenes.o error.o -o primes $(LDFLAGS)

primes.o: primes.c bitset.h eratosthenes.h
	$(CC) $(CFLAGS) -c primes.c -o primes.o

eratosthenes.o: eratosthenes.c eratosthenes.h error.h
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

# Zadani A - inline funkce
primes-i: primes-i.o eratosthenes-i.o bitset-i.o error.o bitset.h
	$(CC) $(CFLAGS_INLINE) primes-i.o eratosthenes-i.o bitset-i.o error.o -o primes-i $(LDFLAGS)

primes-i.o: primes.c bitset.h eratosthenes.h
	$(CC) $(CFLAGS_INLINE) -c primes.c -o primes-i.o

eratosthenes-i.o: eratosthenes.c eratosthenes.h error.h
	$(CC) $(CFLAGS_INLINE) -c eratosthenes.c -o eratosthenes-i.o

bitset-i.o: bitset-i.c bitset.h error.h
	$(CC) $(CFLAGS_INLINE) -c bitset-i.c -o bitset-i.o

# Zadani B
steg-decode: steg-decode.o ppm.o eratosthenes.o error.o bitset.h
	$(CC) $(CFLAGS) steg-decode.o ppm.o eratosthenes.o error.o -o steg-decode $(LDFLAGS)

steg-decode.o: steg-decode.c ppm.h
	$(CC) $(CFLAGS) -c steg-decode.c -o steg-decode.o

ppm.o: ppm.c ppm.h error.h
	$(CC) $(CFLAGS) -c ppm.c -o ppm.o

# Spousteni make s parametrem run
run: primes primes-i
	ulimit -s unlimited; ./primes; ./primes-i;

# Smazani souboru vytvorenych po make
clean:
	rm eratosthenes.o eratosthenes-i.o primes.o primes-i.o primes primes-i bitset-i.o error.o steg-decode steg-decode.o ppm.o
