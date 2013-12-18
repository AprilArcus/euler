CC=gcc
 
all: euler
 
euler: libEuler.o
	$(CC) -o euler euler.c libEuler.o
 
libEuler.o: libEuler.c libEuler.h
	$(CC) -c -o libEuler.o libEuler.c
 
clean:
	rm -f *.o euler

run: euler
	./euler
