#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int pid;
	int status;
	pid = fork();

	if(pid < 0){
		perror("Fork Error : ");
		exit(0);
	}
	if(pid == 0){
		printf("I am Child\n");
		sleep(2);
		return 2;
	}else{
		printf("Parent : wait ( %d ) \n",pid);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)){
			printf("정상 종료 \n");
			printf("Return value : %d \n",WEXITSTATUS(status));
		}else if(WIFSIGNALED(status)){
			printf("신호받았음 \n");
			printf("신호번호 %d\n", WTERMSIG(status));
		}
	}
	exit(0);
}
