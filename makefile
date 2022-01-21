all: server client

server: forking_server.c networking.c
	gcc -o server forking_server.c networking.c networking.h

client: client.c networking.c
	gcc -o client client.c networking.c networking.h

clean:
	rm *.o
