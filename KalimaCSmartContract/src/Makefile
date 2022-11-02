HOST_CC=gcc
CC=$(HOST_CC) -pthread
CFLAGS=-W -Wall
LDFLAGS=-lm -ldl
EXEC= Exec

LIBRARY=lib_KalimaNodeLib.a

all: $(EXEC)

callback.o: callback.c
	$(CC) -o callback.o -c callback.c $(CFLAGS)

main.o: main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

Exec: main.o callback.o
	$(CC) -o main.run main.o callback.o -L. ../libs/KalimaLib/$(LIBRARY) $(LDFLAGS)

clean:
	rm -rf *.o
	rm -rf main.run
	if [ -d log ]; then rm -rf log; fi

mrproper: clean
	rm -rf $(EXEC)
