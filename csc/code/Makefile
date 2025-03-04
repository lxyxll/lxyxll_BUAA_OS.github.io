all:fibo.o main.o

fibo.o:fibo.c ../include/fibo.h 
	gcc -I../include  -c fibo.c -o fibo.o
main.o:main.c ../include/fibo.h
	gcc -I../include  -c main.c -o main.o
clean:
	rm -f fibo.o main.o
