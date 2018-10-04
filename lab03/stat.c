#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	struct stat sb;
	if(argc != 2){
		printf("usage: a.out <pathname>\n");
		exit(1);
	}
	stat(argv[1], &sb);
	printf("inode #\t: %ld\n",sb.st_ino);
	printf("mode\t: %o\n",sb.st_mode);
	printf("uid\t: %d\n",sb.st_uid);
}
