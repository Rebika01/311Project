
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <time.h> 
#define MAX 200
#define PORT 8080
#define SA struct sockaddr
#define ROCK 0
#define PAPER 1
#define SCISSORS 2 
#define SERVERWIN 1
#define CLIENTWIN 2
#define DRAW 0
  
// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n;
    char msg[10];
    int numWins;
    int clientScore, serverScore;
    int myChoice;
    int winnerCode;

    clientScore = 0;
    serverScore = 0;
    numWins = setGameValue();
    //WELCOME  or SM1
    welcomeMessage(sockfd, numWins);
    bzero(buff, MAX);

    while ((clientScore < numWins) && (serverScore < numWins)) {
        bzero(buff, MAX);
        read(sockfd, buff, sizeof(buff));
        myChoice = getMyChoice();
        winnerCode =updateScore(myChoice, buff);
        if (winnerCode == CLIENTWIN){
            clientScore++;
        }
        else if (winnerCode == SERVERWIN){
            serverScore++;
        }

        n = 0;
        bzero(msg, sizeof(msg));
        if (myChoice == 0){
            strcpy(msg,  "ROCK");
        }
        else if (myChoice == 1){
             strcpy(msg,  "PAPER");
        }
        else{
            strcpy(msg,  "SCISSORS");
        }

        if ((clientScore < numWins) && (serverScore < numWins))
            newRoundMessage(sockfd, clientScore, serverScore, msg);
        else
            endGameMessage(sockfd, clientScore, serverScore, msg);
    } 
}


int updateScore(int myChoice, char *buffer[]) {
    int theirChoice;
    if (strncmp(buffer, "ROCK", 4) == 0){
        theirChoice = 0;
    }
    else if (strncmp(buffer, "PAPER", 5) == 0){
        theirChoice = 1;
    }
    else{
        theirChoice = 2;
    }
    if (theirChoice == ROCK){
        switch(myChoice) {

            case PAPER  :
              return SERVERWIN;
              break; 

            case SCISSORS  :
              return CLIENTWIN;
              break; 

            
            default : 
                return DRAW;
                break;
             
        }
    }
     if (theirChoice == PAPER){
        switch(myChoice) {

            case ROCK  :
              return CLIENTWIN;
              break; 

            case SCISSORS  :
              return SERVERWIN;
              break; 

            
            default : 
                return DRAW;
                break;
             
        }
    }
     if (theirChoice == SCISSORS){
        switch(myChoice) {

            case ROCK  :
              return SERVERWIN;
              break; 

            case PAPER  :
              return CLIENTWIN;
              break; 

            
            default : 
                return DRAW;
                break;
             
        }
    }
}


int getMyChoice(){
    int random; 
    random = rand() % 3;
    return random;
}




void newRoundMessage(int sockfd, int clientScore, int serverScore, char *msg[]){
    char buff[MAX];
    bzero(buff, MAX);
    snprintf (buff, sizeof(buff), "\nTHE COMPUTER CHOSE %s.  YOU HAVE WON %d GAMES, THE COMPUTER HAS WON %d GAMES.\n", msg, clientScore, serverScore);
    write(sockfd, buff, sizeof(buff)); 
}

void endGameMessage(int sockfd, int clientScore, int serverScore, char *msg[]){
    char buff[MAX];
    bzero(buff, MAX);
    if (clientScore > serverScore){
        snprintf (buff, sizeof(buff), "GAME OVER.  THE COMPUTER CHOSE %s.  YOU BEAT THE COMPUTER %d to %d.  Server Disconnecting...\n", msg, clientScore, serverScore);
    }
    else{
        snprintf (buff, sizeof(buff), "GAME OVER.  THE COMPUTER CHOSE %s. THE COMPUTER BEAT YOU %d to %d.  Server Disconnecting...\n", msg, serverScore, clientScore);
    }
    write(sockfd, buff, sizeof(buff)); 
}

void welcomeMessage(int sockfd, int numWins){
    char buff[MAX];
    bzero(buff, MAX);
    snprintf (buff, sizeof(buff), "\nROCK PAPER SCISSORS, WIN %d OUT OF %d\n", numWins, numWins * 2 -1);
    write(sockfd, buff, sizeof(buff)); 
}

int setGameValue(){
    int random; 
    srand((unsigned)time(NULL));
    random = rand() % 4;
    random = random + 2;
    return random;
}
  
// Driver function 
int main(int argc, char **argv) 
{ 
    int sockfd, connfd, len;
    sockfd = atoi(argv[1]);
    struct sockaddr_in servaddr, cli;     
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n"); 
  
    // Function for chatting between client and server 
    func(connfd); 
  
    // After chatting close the socket 
    close(sockfd); 
    


} 
