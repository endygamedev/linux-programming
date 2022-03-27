CC = gcc
FO = -Wall -c -fPIC
FSO = -Wall -shared


all: libsolution.so


libsolution.so: solution.o
	${CC} ${FSO} solution.o -o libsolution.so


solution.o: solution.c
	${CC} ${FO} solution.c
