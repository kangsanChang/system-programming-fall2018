#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int match(char* s1, char* s2){
	int diff = strlen(s1) - strlen(s2);
	if (strlen(s1) > strlen(s2)) return (strcmp(&s1[diff],s2)==0);
	else return 0;
}

int main(int argc, char* argv[]){
	struct stat buf;
	if(argc != 2){
		printf("USAGE : ./a.out (directory path)\n");
	}

	stat(argv[1], &buf);
	

}
