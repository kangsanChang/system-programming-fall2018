#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(){
	struct stat buf;
	int fd;

	if((fd = open("testfile", O_RDONLY)) < 0)
			exit(1);
	fstat(fd, &buf);
	printf("file size : %ld\n", buf.st_size);
	printf("user : %u\n", buf.st_uid);
	printf("last updated : %ld\n", buf.st_mtim.tv_sec);
}
