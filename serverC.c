#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "soc.h"
#define  BUFL   100
int main (int argc, char *argv[]) {
        int err;
        int sSocket;
        int cSocket;
        struct sockaddr_in sAddr;
        struct sockaddr_in cAddr;
        int cSocLen;
        char Buf[BUFL];
        sSocket = socket( AF_INET, SOCK_STREAM, 0); // AF_INET
        if (sSocket == -1) {
                perror ("socServer:  socket creation failed");
                exit (1);
        }
        memset (&sAddr, 0, sizeof (struct sockaddr_in));
        sAddr.sin_family = AF_INET;
        sAddr.sin_port = htons (SERVERPORT);
        sAddr.sin_addr.s_addr = htonl (INADDR_ANY);
        err = bind(sSocket, (struct sockaddr*)&sAddr, sizeof (struct sockaddr_in));
        if (err == -1) {
                perror ("socServer:  bind address to socket failed");
                exit (2);
        }
        err = listen(sSocket, 5);
        if (err == -1) {
          perror ("socServer:  listen failed");
          exit (3);
        }
        cSocket = accept(sSocket, (struct sockaddr *)&cAddr, &cSocLen);

        if (cSocket == -1) {
                perror ("socServer:  accept failed");
                exit (4);
        }
        //  Read from client socket.
        err = recv(cSocket, Buf, BUFL, 0);
        if (err == -1) {
                perror ("socServer:  read failed");
                exit (5);
        }
        printf ("socServer:  msg from client:  %s\n", Buf);
        exit (0);
}
