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
	1. 서버 실행 후 클라이언트로 부터 입력 대기
	2. 클라이언트로 부터 입력 받으면 출력하고 서버 입력 후 보냄
 */
int main(){
	int ssock;
	int clen;
	struct sockaddr_in client_addr, server_addr;
	char received_msg[MAXBUF];
	char send_msg[MAXBUF];

	// socket 생성
	if((ssock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ){
		perror("socket error : ");
		exit(1);
	}

	// socket 연결 위한 서버 옵션 
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(4220);

	//socket 에 ip 주소등의 서버 옵션 설정
	if(bind(ssock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
		perror("bind error : ");
		exit(1);
	}

	while(1){
		// udp data 수신
		recvfrom(ssock, (void *)received_msg, MAXBUF, 0, (struct sockaddr*)&client_addr, &clen);
		printf("Received MSG : %s", received_msg);
		printf("\nINPUT TEXT : ");
		fgets(send_msg, MAXBUF, stdin);
		// udp data 전송 
		sendto(ssock, (void *)send_msg, MAXBUF, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
	}
	close(ssock);
	return 0;
}
