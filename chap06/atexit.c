#include <stdio.h>
#include <stdlib.h>

static void my_exit1(void), my_exit2(void);
void err_sys(const char *message);

int main(){
	if (atexit(my_exit2) != 0)
			err_sys("can't register my_exit2"); // 만일 에러날 시 file descriptor 2 번이 기록
	if (atexit(my_exit1) != 0)
			err_sys("can't register my_exit1");
	printf("main is done\n");
	return 0;
}

static void my_exit1(void){
	printf("first exit handler\n");
}

static void my_exit2(void){
	printf("second exit handler\n");
}

void err_sys(const char *message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
