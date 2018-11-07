#include <unistd.h>
#include <stdio.h>

void main(){
	printf("executing ls\n");
	execl("/bin/ls", "ls", "-l", (char *) 0);

	// exec 를 실행했으므로 믿에있는 코드는 실행되지 않음
	// completely wipe out
	printf("farewell eec\n");
	perror("execl failed to run ls \n");
	exit(1);
}
