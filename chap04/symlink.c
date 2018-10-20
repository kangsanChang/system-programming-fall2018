#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
	char *buf[256], tname[256];
	if(argc < 3 || argc > 4 || (argc==4 && strcmp(argv[1], "-s")))
	{
		printf("Usage : %s <orig_file> <new_file> \n",argv[0]);
		return 1;
	}
	if(argc==4)
			return symlink(argv[2], argv[3]);
	else
			return link(argv[1], argv[2]);
}
