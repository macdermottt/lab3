
CC=gcc
CFLAGS= -g -O1 -Wall

arrayList: main.o 

arrayList.o: arrayList.h

main.o:

clean: 
	rm -rf *.o 
