CC = clang
CFLAGS = -g
BINS = server
OBBJS = server.o myqueue.o


all: $(BINS)
	$(CC) $(CFLAGS) -o $@ S^

%: %.c
	$(CC) $(CFLAGS) -c -o $@ $^


clean:
	rm -rf *.dbSM $(BINS)
