CC = gcc
all:server client
server:server.c warp.o 
	$(CC) -lpthread server.c warp.o -o server
client:client.c warp.o
	$(CC) client.c warp.o -o client
warp.o:warp.c
	$(CC) -c warp.c
clean:
	rm *.o server client
