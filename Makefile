CC=gcc
CFLAGS=-Wall

all:
	$(CC) $(CFLAGS) *.c -o scheduler

clean:
	rm -f scheduler
