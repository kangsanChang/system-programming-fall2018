#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //read write lseek
#include <fcntl.h> // open
#include <sys/stat.h> // open
#include <sys/types.h> // open
#define BUFSIZE 10
int main() {
	int fds, fdd;
	char buf[BUFSIZE];
	if((fds = open("copied", O_RDONLY)) < 0)
			exit(1);
	if((fdd = open("dcopied", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR))< 0)
			exit(1);
	lseek(fds, (off_t)10, SEEK_SET);
	read(fds, buf, BUFSIZE);
	write(fdd, buf, BUFSIZE);
}
