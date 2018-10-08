#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <error.h>

int main(){
	int fd;

	if((fd = creat("afile", S_IRUSR | S_IWUSR)) == -1)
			perror("afile");
	printf("This is displayed on the screen.\n");
	close(STDOUT_FILENO); // close STDOUT : 1
	dup(fd); // copied fd will get 1
	close(fd); // close origin fd
	printf("THis is written into the redirected file");
	return 0;
}
