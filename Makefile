#This is the makefile for Project 3
CC = gcc
CFLAGS = -g 

all: Client Server Server2

Client: client.c
	$(CC) $(CFLAGS) client.c -o Client

Server: serverC.c
	$(CC) $(CFLAGS) serverC.c -o Server

Server2: serverG.c
	$(CC) $(CFLAGS) serverG.c -o Server2
clean:
	rm -f Client
	rm -f Server
	rm -f Server2
