#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
	if(argc != 3){
		printf("usage: ./a.out <filename> <newname>\n");
		exit(1);
	}
	link(argv[1], argv[2]);
	unlink(argv[1]);
}
