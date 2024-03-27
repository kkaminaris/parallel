CC=gcc
CFLAGS=-Wall -O3 -pthread -lm
LDFLAGS=-lm

all: integral_seq integral_threaded

clean:
	rm -f integral_seq integral_threaded

%: %.c
	$(CC) $(CFLAGS) -o $@ $< timer.c $(LDFLAGS)
