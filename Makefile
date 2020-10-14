CC = g++ -std=c++11
CFLAGS = -Wall -g -fsyntax-only -fpermissive
all: serverC serverG client
serverC:  serverC.c soc.h
						$(CC) $(CFLAGS) -o serverC serverC.c soc.h
serverG:  serverG.c soc.h
						$(CC) $(CFLAGS) -o serverG serverG.c soc.h
client:		client.c soc.h
						$(CC) $(CFLAGS) -o client client.c soc.h

clean:
	rm -f serverC
	rm -f serverG
	rm -f client
