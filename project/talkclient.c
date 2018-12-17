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
	1. Client 는 실행 후 보낼 text 입력
	2. 서버로부터 온 메시지 를 출력하고 다시 입력
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
		printf("INPUT TEXT : ");
		fgets(send_msg,MAXBUF,stdin);
		sendto(ssock, (void*)send_msg, MAXBUF, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
		recvfrom(ssock, (void*)received_msg, MAXBUF, 0, (struct sockaddr*)&client_addr, &clen);
		printf("Received MSG : %s", received_msg);
	}
	close(ssock);

	return 0;
}
