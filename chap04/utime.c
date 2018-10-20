#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include "error.h"

int main(int argc, char *argv[]){
	int i;
	struct stat statbuf;
	struct utimbuf timebuf;

	for(i=1;i<argc;i++){
		if(stat(argv[i], &statbuf) < 0) // open 하기 전 시간에 대한 정보 값을 받아놓기 위해 statbuf에 저장.
				perror(argv[i]);
		if(open(argv[i], O_RDWR|O_TRUNC) <0) // access 를 했으니 access time 이 바뀌어야 함, truncate 시도도 하므로 modify time도 바뀜
				perror(argv[i]);

		timebuf.actime = statbuf.st_atime; // stat에서 받은 access time 정보 옮기기
		timebuf.modtime = statbuf.st_mtime; // 같은 행위
		// 수정해놓고 안한 척 하기
		if(utime(argv[i], &timebuf) <0)
				perror(argv[i]);
	}
	return 0;
}
