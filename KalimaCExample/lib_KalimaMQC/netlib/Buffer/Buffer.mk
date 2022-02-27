CC=gcc -pthread
CFLAGS=-W -Wall
LDFLAGS=
EXEC=Buffer

all: $(EXEC)

BufferChain: BufferChain.c
	$(CC) -o BufferChain.o -c BufferChain.c $(CFLAGS)

Buffer: BufferChain.o
	ar rcs Buffer.a BufferChain.o $(LDFLAGS)

clean:
	rm -rf *.o
	rm -rf Buffer.a

mrproper: clean
	rm -rf $(EXEC)