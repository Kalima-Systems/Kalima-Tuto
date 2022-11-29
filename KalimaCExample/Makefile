CC=gcc -pthread 
CFLAGS=-W -Wall
LDFLAGS=
EXEC= Exec
INCLUDE=-I./lib/inc/KalimaCUtil -I./lib/inc/MQ2/netlib -I./lib/inc/MQ2/message -I./lib/inc/MQ2/nodelib -I./lib/inc/NodeLib
LIBRARY=libKalimaNodeLib.a

all: $(EXEC)

Exec: 
	$(CC) $(INCLUDE) -o main.o -c src/main.c $(CFLAGS)
	$(CC) $(INCLUDE) -o main.run main.o -L. lib/$(LIBRARY) $(LDFLAGS)
	rm -rf main.o

clean:
	rm -rf *.o
	rm -rf main.run
	if [ -d log ]; then rm -rf log; fi

mrproper: clean
	rm -rf $(EXEC)