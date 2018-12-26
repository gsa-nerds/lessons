

hello: a.o b.o
	gcc a.o b.o -o hello

a.o: a.c
	gcc -c a.c
b.o: b.c:
	gcc -c b.c

