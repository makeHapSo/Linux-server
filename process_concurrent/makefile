CC = gcc
server:server.c warp.o
	$(CC) server.c warp.o -o server
warp.o:warp.c
	$(CC) -c warp.c
clean:
	rm *.o server
