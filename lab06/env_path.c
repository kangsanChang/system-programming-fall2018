#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
	printf("BEFORE : %s\n",getenv("PATH"));
	setenv("PATH",strcat(getenv("PATH"),":./"),1);
	printf("AFTER : %s\n", getenv("PATH"));
	return 0;
}
