#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
	pid_t pid[2];
	int i;
	int status;
	char message[20];
	for(i=1; i<3; i++){
		if((pid[i-1] = fork()) == 0){		
			sprintf(message,"This is Child %d\n", i);
			execl("/bin/echo","echo", message,(char*)0);
		}
	}
	// parent part
	for(i=0; i<2; i++){
		
		if(waitpid(pid[i],&status,0) > 0){
			if(i==0)
					printf("Parent: First Child Finished\n");
			else if(i==1)
					printf("Parent: Second Child Finished\n");
		}
	}
	printf("Parent: All Children terminated\n");
	return 0;
}
