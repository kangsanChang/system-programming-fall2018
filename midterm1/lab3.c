#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
	struct stat buf;
	stat("testfile", &buf);
	printf("ino # : %lu \n", buf.st_ino);
	printf("mode : %u \n", buf.st_mode);
	printf("uid : %u \n", buf.st_uid);
}
