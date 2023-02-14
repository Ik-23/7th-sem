// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 8080
#define MAXLINE  1024

// Sender code
int main(void) {
	int sockfd,len,n;
	char buffer[MAXLINE], msg[MAXLINE]="exit";
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	printf("[+]Server Socket is created.\n");
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if (bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 ) {
	   perror("bind failed");
	   exit(EXIT_FAILURE);
	}
	printf("[+]Bind to port %d\n", 8080);
	
	len = sizeof(cliaddr); //len is value/result
    while(1) {
	        recvfrom(sockfd, (char *)buffer, MAXLINE,
	 		  MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);
	        printf("Client : %s\n", buffer);
	        printf("Enter the message to reply to client:");
	        fgets(buffer, sizeof(buffer),stdin);
	        n = strlen(buffer);
	        buffer[n-1]='\0';
	        if (strcmp(buffer, msg)==0) {
                   printf("Disconnected from %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                   break;
                } else {
	              sendto(sockfd, buffer, sizeof(buffer),
		            MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
	              printf("Message sent.\n");
	               }
        } 
        close(sockfd);
	return 0;
}




