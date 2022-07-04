CC=gcc -pthread
CFLAGS=
LDFLAGS=
EXEC= Exec

LIBRARY=lib_KalimaNodeLib.a

all: $(EXEC)

main.o: main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

Exec: main.o
	$(CC) -o main.run main.o -L. ../libs/KalimaLib/$(LIBRARY) $(LDFLAGS)

clean:
	rm -rf *.o
	rm -rf main.run
	if [ -d log ]; then rm -rf log; fi

mrproper: clean
	rm -rf $(EXEC)

