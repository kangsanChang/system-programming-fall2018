#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#define MAXBUF 256
/*
 DESC.
 - 1+2, 6*5 와 같이 operand 와 operator 를 붙여서 입력
 - 종료 시 exit 입력
 - 규칙에 어긋난 방식으로 입력 시 input Error 출력하고 재입력 받음
 */
int main() {
	int ssock;
	int clen, num=0;
	struct sockaddr_in server_addr;
	char buf[MAXBUF];

	if((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket error :");
		exit(1);
	}

	clen = sizeof(server_addr);

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(7917);

	if(connect(ssock, (struct sockaddr *)&server_addr, clen) < 0){
		perror("connect error : ");
		exit(1);
	}

	while(1){
		printf("계산 식 입력 (1+2 와 같은 형태로 입력, exit 시 종료) : ");
		fgets(buf, MAXBUF, stdin);
		if(strcmp(buf,"exit\n")==0){
			write(ssock,buf,MAXBUF);
			close(ssock);
			return 0;
		}
		if(write(ssock, buf, MAXBUF) <= 0){
			perror("write error : ");
			exit(1);
		}
		
		if(read(ssock, buf, MAXBUF) <= 0){
			perror("read error : ");
			exit(1);
		}
		printf("%s\n", buf);
	}
	close(ssock);
	return 0;
}
