#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
	int fd = open("/tmp/test.txt", O_RDONLY);
	int fsize = lseek(fd, (off_t)0, SEEK_END);

	printf("The size of test.txt is %d bytes.", fsize);
}
