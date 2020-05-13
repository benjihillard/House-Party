game: adventure.o rooms.o items.o
	gcc adventure.o rooms.o items.o -o game

adventure: adventure.c
	gcc -c adventure.o

rooms: rooms.o
	gcc -c rooms.c

items: items.o
	gcc -c items.c

clean:
	rm *.o game


