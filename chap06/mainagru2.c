#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	int i = 0;
	char **p = argv;

	while(*p)
			printf("argv[%d]: %s\n", i++, *p++);
	exit(0);
}
