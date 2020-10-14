CC = g++ -std=c++11
CFLAGS = -Wall -g -fsyntax-only -fpermissive
all: socServer socClient
serverC:  serverC.c soc.h
						$(CC) $(CFLAGS) -o socClient socClient.c
serverG:  serverG.c soc.h
						$(CC) $(CFLAGS) -o socServer socServer.c
client:		client.c soc.h
						$(CC) $(CFLAGS) -o client client.c

clean:
	rm -f serverC
	rm -f serverG
	rm -f client
