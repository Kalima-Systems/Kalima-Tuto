
CC=gcc -pthread 
CFLAGS=-W -Wall
EXEC= Exec

all: $(EXEC)

NodesChatC.o: main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

Exec: main.o
	$(CC) -o main.run main.o -L. ../lib_KalimaMQC/lib_KalimaMQC.a $(CFLAGS)

clean:
	rm -rf *.o
	rm -r log/

mrproper: clean
	rm -rf $(EXEC)

