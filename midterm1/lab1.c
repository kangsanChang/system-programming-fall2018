#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 512

int main(int argc, char* argv[]){
	if(argc != 3)
		exit(1);

	int fds,fdd;
	ssize_t nread;
	char buf[BUFSIZE];
	fds = open(argv[1],O_RDONLY);	
	fdd = open(argv[2],O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	
	while(nread = read(fds, buf, BUFSIZE)){
			printf("%ld : %s \n\n",nread, buf);
			write(fdd, buf, nread);
	}
	close(fds);
	close(fdd);
	exit(0);
}

