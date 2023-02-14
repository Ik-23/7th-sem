// Client side implementation of UDP client-server model
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

// Reciever code
int main(void) {
	int sockfd, len, n;
	char buffer[MAXLINE],msg[MAXLINE]="exit";
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	printf("[+]Client Socket is created.\n");

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	while(1) {
	        printf("Enter message to send to server:");
	        fgets(buffer, sizeof(buffer), stdin);        //gets(buffer);
	        n = strlen(buffer);
	        buffer[n-1]='\0';
	        sendto(sockfd, buffer, sizeof(buffer), MSG_CONFIRM, 
	              (const struct sockaddr *) &servaddr, sizeof(servaddr));
	        printf("Message sent.\n");
	        if (strcmp(buffer, msg) == 0) {
                   close(sockfd);
	           printf("[-]Closing server.\n");
	           exit(1);
	        } else
		recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		printf("Server:%s\n",buffer);
	}
	close(sockfd);
	return 0;
}




