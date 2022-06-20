CC=gcc -pthread
CFLAGS=
LDFLAGS=-lcrypto -lm
EXEC= Exec

LIBRARY=lib_KalimaNodeLib32.a

all: $(EXEC)

main.o: main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

Exec: main.o
	cd ../libs/KalimaLib; if [ -d objects ]; then rm -rf objects; fi; mkdir objects; cd objects; ar -x ../$(LIBRARY)
	$(CC) -o main.run main.o ../libs/KalimaLib/objects/*.o $(LDFLAGS)
	cd ../libs/KalimaLib; if [ -d objects ]; then rm -rf objects; fi

clean:
	rm -rf *.o
	rm -rf main.run
	if [ -d log ]; then rm -rf log; fi
	cd ../libs/KalimaLib; if [ -d objects ]; then rm -rf objects; fi

mrproper: clean
	rm -rf $(EXEC)

