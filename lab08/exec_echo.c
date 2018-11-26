#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
	pid_t pid, wpid;
	int i;
	int status;
	char message[20];
	for(i=1; i<5; i++){
		if((pid = fork()) == 0){		
			sprintf(message,"This is Child %d (%d)\n My Parent is %d\n", i,getpid(),getppid());
			execl("/bin/echo","echo", message,(char*)0);
		}
	}
	// parent part
	if(pid!=0){
		printf("Parent: Waiting for children \n");		
		while((wpid=wait(&status))>0){ // wait 이 제대로 먹히면 pid 주니까 0보다 크고, 더이상 할게없으면 0나옴 
			printf("A Child Process Terminated (WPID : %d)\n", wpid); // 끝난 child pid
		}
	}
	printf("\nParent: All Children terminated\n");
	return 0;
}
