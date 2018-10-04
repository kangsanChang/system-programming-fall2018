#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "error.h"
#include <stdio.h>

int main(){
	int fd, len;
	char buf[20];

	fd = open("tempfile", O_RDWR | O_CREAT | O_TRUNC, 0666); // umask 와 비교해서 생성됨.
	if (fd== -1) perror("open1");
	unlink("tempfile"); // tempfile의 link가 0 임. 근데 여전히 open 된 것임. 왜냐면 open 한 프로세스가 돌고있기 때문
	len = write(fd, "How are you?", 12); // 12 byte writing
	if(len != 12) perror("write");
	lseek(fd, 0L, SEEK_SET); // 0에서 0으로 이동. 즉 맨 앞으로 옮김. 왜냐면 writing 하면서 file pointer가 제일 뒤로 가있을거니까
	len = read(fd, buf, sizeof(buf)); // read 해서 한 내용을 buf에 가져다둠. buf 에 있는 내용은 how are you
	if(len < 0) perror("read");
	buf[len] = '\0'; // 끝임을 표시하기 위해 강제로 넣은것
	printf("%s\n", buf); // 화면에 print 됨. 아직 살아있으니까
	close(fd); // process 종료, link count가 0이 되어 이제 시스템에서 사라지게 됨.(ino tb에서 삭제)
	fd = open("tempfile", O_RDWR); // close 한 것에서 다시 open 시도함.
	if(fd== -1) perror("open2"); // 당연히 안되겠지? 에러남.
	close(fd);
	return 0;
}
