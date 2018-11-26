#include <unistd.h> // for pipe
#include <stdlib.h>
#include <stdio.h>

int main() {
	int fd[2];
	char msg[] = "Hello World!!";
	char buffer[20];
	pid_t pid;
	
	if(pipe(fd) >0){
			// fd[0] : read, fd[1] : write
			perror("Pipe Failed");
			exit(1);
	}
	pid = fork();
	switch(pid){
		case -1:
			perror("Fork Failed");
			exit(1);
		case 0:
			// child process
			close(fd[1]); //close write fd 
			read(fd[0], buffer, sizeof(msg));
			printf("The message from parent : %s\n", buffer);
			break;
		default:
			close(fd[0]); // close read fd
			write(fd[1], msg, sizeof(msg)); 
			printf("message sent\n");
			break;
	}
	return 0;
}

