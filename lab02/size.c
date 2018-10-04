#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
	printf("The size of test.txt is %ld bytes.\n",lseek(open("test.txt",O_RDONLY),(off_t)0, SEEK_END));
}
