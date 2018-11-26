#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 1024
#define FIFO_PATH "./myfifo"

int main() {
	int fp;
	char buffer[BUFSIZE] = {0};
	ssize_t nread;

	if((fp = open(FIFO_PATH, O_RDWR)) < 0){
		perror("open error : ");
		exit(0);
	}
	while(1){
		while((nread=read(0, buffer,BUFSIZE)) > 0){
			write(fp, (void*)&buffer, nread);
		}
	}
	exit(1);
}
