all: server client

server: server.o hangman.o
	gcc -o server server.o hangman.o

client: client.o hangman.o
	gcc -o client client.o hangman.o

server.o: server.c hangman.c
	gcc -c server.c

client.o: client.c hangman.c
	gcc -c client.c

hangman.o: hangman.c hangman.h
	gcc -c hangman.c
clean:
	rm client.o server.o hangman.o server client
