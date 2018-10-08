#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <error.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main() {
	int fd;

	if((fd=creat("file.hole", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))<0)
			perror("file.hole");
	if(write(fd, buf1, 10) != 10)
			perror("buf1");
	if(lseek(fd, 40, SEEK_SET) == -1)
			perror("lseek");
	if(write(fd,buf2,10) != 10)
			perror("buf2");
	return 0;
}
