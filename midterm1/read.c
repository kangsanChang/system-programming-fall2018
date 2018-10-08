#include <unistd.h> // for read(), close()
#include <fcntl.h> // for open()
#include <stdlib.h> // for exit

#define BUFSIZE 512

void main(){
	char buffer[BUFSIZE];
	int fd;
	ssize_t nread;
	long total = 0;
	
	while((nread = read(fd = open("testfile",O_RDONLY)), buffer, BUFSIZE) >0){
			printf("nread vlaue of this term : %ld\n",nread);
			total += nread;
	}

	close(fd);

	printf("Num of char in testfile : %ld\n", total);
}
