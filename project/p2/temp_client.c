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
	1. 서버 실행 후 클라이언트 실행
	2. 클라이언트에서 41F 또는 5C 와 같이 변환할 온도 입력
	3. 서버에서 변환된 온도 출력
	4. 종료시 ctrl + c 입력
 */

int main() {
	int ssock;
	int clen;
	struct sockaddr_in client_addr, server_addr;
	char received_msg[MAXBUF];
	char send_msg[MAXBUF];

	if((ssock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))<0){
		perror("socket error: ");
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(4220);

	while(1){
		printf("온도 입력 (숫자 뒤 화씨면 F, 섭씨면 C 를 붙여서 입력) : ");
		fgets(send_msg,MAXBUF,stdin);
		sendto(ssock, (void*)send_msg, MAXBUF, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
		recvfrom(ssock, (void*)received_msg, MAXBUF, 0, (struct sockaddr*)&client_addr, &clen);
		printf("변환된 온도 : %s\n", received_msg);
	}
	close(ssock);

	return 0;
}
