#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 512

int main() {
	char buffer[BUFSIZE];
	int fd_src, fd_dest;
	ssize_t nread;
	
	if((fd_src = open("afile", O_RDONLY)) == -1)
			exit(1);
	fd_dest = open("bfile", O_RDWR | O_CREAT,S_IRUSR|S_IWUSR);

	while((nread = read(fd_src,buffer,BUFSIZE))>0)
		write(fd_dest, buffer, nread);

	close(fd_src);
	close(fd_dest);
	
	exit(0);
}
