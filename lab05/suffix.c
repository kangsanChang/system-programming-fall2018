#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

typedef struct dirent Dirent;

int match(char *s1, char *s2) {
	int diff = strlen(s1) - strlen(s2);
	if(strlen(s1) > strlen(s2)) return (strcmp(&s1[diff], s2) == 0);
	else return 0;
}

int main(int argc, char* args[]){
	Dirent *dp;
	DIR *dir_fd;
	int i;
	if(argc !=3)
		perror("Useage : ./a.out [dirpath] [suffix]\n");

	if(!(dir_fd = opendir(args[1])))
		perror("There is no path to open");
	while(dp = readdir(dir_fd)){
		if(match(dp->d_name, args[2])){
				printf("%s : ", dp->d_name);
				printf("%lu\n", dp->d_ino);
				break;
		}
	}
	return 0;
}
