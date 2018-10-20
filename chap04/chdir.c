#include <unistd.h>
#include <stdio.h>
#include <error.h>

#define PATH_MAX 1024

int main(void){
	char path[PATH_MAX +1];
	if(chdir("/tmp")<0)
			perror("error chdir");
	else{
			if(getcwd(path,PATH_MAX)==NULL)
					perror("error getcwd");
			else
					printf("Current working directory changed to %s \n",path);
	}
}
