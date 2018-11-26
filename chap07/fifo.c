#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
	int res = mkfifo("my_fifo",0775);
	if(res == 0) printf("FIFO Created!\n");
	exit(EXIT_SUCCESS);
}
