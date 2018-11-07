#include <sys/types.h>
#include "ourhdr.h"
#include "tellwait.h"

static void charatatime(char *);

int main(){
	pid_t pid;
	TELL_WAIT();

	if((pid = fork()) < 0)
			perror("Fork Error!");
	else if(pid ==0){
		WAIT_PARENT(); // Parent goes First
		charatatime("output from child\n");
	}else{
		charatatime("output from parent\n");
		TELL_CHILD(pid); // child 에게 끝났다고 말해줌
	}
	exit(0);
}

static void charatatime(char *str){
	char *ptr;
	int c;

	setbuf(stdout, NULL);
	for(ptr = str; c=*ptr++;){
		putc(c,stdout);
		usleep(10000);
	}
}
