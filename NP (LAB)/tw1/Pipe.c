#include <stdio.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <errno.h>


int main(void) {
    int id,fd[2];
    char msg1[80],msg2[80];
    // fd[0] - Pipe-readend fd[1] - Pipe-writeend
    if (pipe(fd) == -1) {
        printf("An error ocurred with opening the pipe\n");
        return 1;
    }
    if ((id = fork())== -1) {
       printf("An Error occured with creating process\n"); 
       return 2;
       }
    if (id==0) {
       printf("Input the message:");
       fgets(msg1, sizeof(msg1),stdin);
       write(fd[1],msg1,sizeof(msg1));
       close(fd[1]);
    } else {
      read(fd[0],msg2,sizeof(msg2));
      printf("\nGot message from child process:%s\n",msg2);
      close(fd[0]);
      }
 return 0;
} 