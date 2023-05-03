HOST_CC=gcc
CC=$(HOST_CC) -pthread
CFLAGS=-W -Wall
LDFLAGS=-lm -ldl
EXEC= Exec
INCLUDE=-I./inc -I./lib/inc/KalimaCUtil -I./lib/inc/MQ2/netlib -I./lib/inc/MQ2/message -I./lib/inc/MQ2/nodelib -I./lib/inc/NodeLib -I./lib/inc/ContractManager
LIBRARY=libKalimaNodeLib.a

all: $(EXEC)

Exec:
	$(CC) $(INCLUDE) -o LuaFunctions.o -c src/LuaFunctions.c $(CFLAGS)
	$(CC) $(INCLUDE) -o callback.o -c src/callback.c $(CFLAGS)
	$(CC) $(INCLUDE) -o main.o -c src/main.c $(CFLAGS)
	$(CC) -o main.run *.o -L. lib/$(LIBRARY) $(LDFLAGS)
	rm -rf *.o

clean:
	rm -rf *.o
	rm -rf main.run
	if [ -d Files/log ]; then rm -rf Files/log; fi

mrproper: clean
	rm -rf $(EXEC)

