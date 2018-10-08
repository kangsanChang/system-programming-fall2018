#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int fd;
	if((fd = open("testfile", O_RDONLY))<0)
			exit(1);
	printf("fd : %d\n",fd);
	printf("The size of testfile is : %ld\n", lseek(fd, (off_t)0, SEEK_END)); 
}
