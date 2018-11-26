#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 1024
#define FIFO_PATH "./myfifo"

int main() {
	int fp;
	char buffer[BUFSIZE]={0};
	ssize_t nread;
	if(mkfifo(FIFO_PATH, 0666) != 0)
			perror("mkfifo failure");
	if((fp = open(FIFO_PATH, O_RDWR)) < 0){
		perror("open error : ");
		exit(0);
	}

	while((nread=read(fp, (void *)&buffer, BUFSIZE)) > 0){
		write(1, (void *)&buffer, nread);
	}
	exit(1);
}
