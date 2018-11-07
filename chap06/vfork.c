#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 6;

int main(){
	int var;
	pid_t pid;

	var = 88;
	printf("before vfork\n");

	if((pid = vfork()) < 0)
			perror("vfork Error");
	else if (pid == 0){ // child
		glob++;
		var++;
		_exit(0); // child termination
	}
	// print parent
	printf("pid = %d, glob = %d, var = %d \n",getpid(),glob,var);
	exit(0);
}
