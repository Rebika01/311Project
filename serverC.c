
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 8080
#define SA struct sockaddr 
  
// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    read(sockfd, buff, sizeof(buff)); 
    read(sockfd, buff, sizeof(buff)); 

    // infinite loop for chat 
    for (;;) {
        read(sockfd, buff, sizeof(buff));  
        bzero(buff, MAX); 
  
        // read the message from client and copy it in buffer 
        read(sockfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("From client: %s\t To client : ", buff); 
        bzero(buff, MAX); 
        n = 0; 
        // copy server message in the buffer 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
  
        // and send that buffer to client 
        write(sockfd, buff, sizeof(buff)); 
  
        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
} 
  
// Driver function 
int main() 
{ 
    int sockfd;
    int connfd, len; 
    int forkerror;
    //struct sockaddr_in servaddr, cli; 
  
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else{
        printf("Socket successfully created..\n"); 
    }
    printf("Socket INT: %d\n", sockfd);
    //Try here






    //Putting Experiments Below:

    int pid = fork();
    if (pid < 0) { //something went wrong
            printf("Error in forking. The program will exit");
            exit(1);
    }
    else if (pid == 0) { //this is the child process
            
           printf("\nWe passed %d and %d to Server2\n", sockfd, sockfd);
           char buffer[20];
            snprintf (buffer, sizeof(buffer), "%d",sockfd);
            forkerror =execl("./Server2", "Server2", buffer, (char *)0);
            if (forkerror == -1){
                printf("\nExecl failed.\n");
            }
    }
    else{ //this is the parent process
        int exitStatus;
        waitpid(pid, &exitStatus, 0);
        printf("From Parent: The child process pid = %d has completed.\n", pid);
        printf("From Parent: The child process had an exit status of %d\n", exitStatus);
        printf("Program now terminating.\n");
    }

    //END EXPERIMENT

    /*
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
    */
} 
