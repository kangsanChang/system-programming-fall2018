#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#define BUFSIZE 50
// use open read write close
// cpy 50 byte only
int main() {
	int sfd, dfd;
	char buf[BUFSIZE];
	if((sfd = open("testfile", O_RDONLY)) < 0)
		exit(1);	
	if((dfd = open("copied", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
		exit(1);

	read(sfd, buf, BUFSIZE);
	write(dfd, buf, BUFSIZE);

}
