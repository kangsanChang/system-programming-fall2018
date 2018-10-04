#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <error.h>

int main(int argc, char *argv[]){
	if (argc != 2)
			printf("usage: a.out <pathname>");
	if (access(argv[1], R_OK) < 0)
			perror("R_OK");
	else
			printf("read access OK\n");

	if (open(argv[1], O_RDONLY) <0)
			perror("O_RDONLY");
	else
			printf("open for reading OK\n");
	return 0;
}
