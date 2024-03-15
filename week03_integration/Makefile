CC=gcc-11
CFLAGS=-Wall -O3 -pthread

all: integral_seq integral_pthread1 integral_pthread2 integral_pthread3 integral_pthread4 integral_pthread5 \
	integral_pthread6 integral_pthread7 integral_pthread8 integral_pthread9


clean:
	rm -f integral_seq integral_pthread1 integral_pthread2 integral_pthread3 integral_pthread4 integral_pthread5 \
	integral_pthread6 integral_pthread7 integral_pthread8 integral_pthread9


%: %.c
	$(CC) $(CFLAGS) -o $@ $< timer.c
