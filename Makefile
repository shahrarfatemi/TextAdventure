CC = gcc
CFLAGS = -c -g -Wall

all: adventure

adventure: rooms.o items.o adventure.o
	$(CC) -o adventure rooms.o items.o adventure.o

rooms.o: rooms.c rooms.h
	$(CC) $(CFLAGS) rooms.c

items.o: items.c items.h
	$(CC) $(CFLAGS) items.c

adventure.o: adventure.c
	$(CC) $(CFLAGS) adventure.c

clean:
	rm *.o