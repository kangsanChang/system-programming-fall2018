#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#define MAXBUF 256

int main() {
	int ssock;
	int clen;
	struct sockaddr_in server_addr;
	char buf[MAXBUF];

	// create socket

	if((ssock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		perror("socket error : ");
		exit(1);
	}

	clen = sizeof(server_addr);

	//socket 접속 주소 지정
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(3317);

	//지정 주소로 접속
	if(connect(ssock, (struct sockaddr*)&server_addr, clen) < 0){
		perror("connect error: ");
		exit(1);
	}

	memset(buf,0,MAXBUF);

	//server 전송하는 문자열 받음
	if(read(ssock, buf, MAXBUF) <= 0){
		perror("read error: ");
		exit(1);
	}

	//socket 닫음
	close(ssock);

	//받아온 문자열을 화면에 출력
	printf("\nread : %s\n\n", buf);
	return 0;
}
