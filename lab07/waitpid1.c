#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int i=0;
	int pid;
	int status;

	for(;i<10;i++){
		pid = fork();

		if(pid <0){
			perror("Fork Error\n");
			exit(0);
		}
		if(pid == 0){
			printf("I am Child %d!\n", i);
			return 0;
		}else{
			printf("Parent : wait(%d)\n", pid);
			waitpid(pid, &status,0);
			if(WIFEXITED(status)){
				printf("Child %d (%d) 정상 종료 \n",i,pid);

			}
		}
	}
}
