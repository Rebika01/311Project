
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX 200 
#define PORT 8080 
#define SA struct sockaddr 

void func(int sockfd) 
{ 

    char buff[MAX]; 
    char temp[MAX];
    int n;
    int error;

    //WELCOME OR SM1
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    printf("\nServer: %s\n", buff); 

    for (;;) { 
        printf("\nEnter your selection of ROCK, PAPER, OR SCISSORS :\n "); 
        do {
            n = 0; 
            bzero(buff, sizeof(buff));
            bzero(temp, sizeof(temp));
            while ((temp[n++] = getchar()) != '\n') 
            ;
            error = checkInput(temp);
        } while (error == -1);
        strcpy(buff, temp);

        //send to server
       
        write(sockfd, buff, sizeof(buff)); 
        //bzero(buff, sizeof(buff));

        read(sockfd, buff, sizeof(buff)); 
        printf("From Server : %s", buff); 
        if ((strncmp(buff, "GAME", 4)) == 0) { 
            //printf("Client Exit...\n"); 
            break; 
        } 

    }

} 
int checkInput(char *buffer[]){
    int result = -1;
    if (strncmp(buffer, "ROCK", 4) == 0){
        result = 0;
    }
    else if (strncmp(buffer, "PAPER", 5) == 0){
        result = 0;
    }
    else if (strncmp(buffer, "SCISSORS", 8) == 0){
        result = 0;
    }

    if (result == -1){
        printf("\nBad Input. Try again: \n");
    }
    return result;

}

  
int main() 
{ 
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.42"); 
    servaddr.sin_port = htons(PORT); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for chat 
    func(sockfd);
    printf("\nGood Game.  Program is closing...\n"); 
  
    // close the socket 
    close(sockfd); 
} 
