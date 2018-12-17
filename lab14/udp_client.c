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
	struct sockaddr_in client_addr, server_addr;
	char buf[MAXBUF];

	strcpy(buf, "I miss you already!");

	// create socket
	if((ssock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ){
		perror("socket error : ");
		exit(1);
	}

	// 서버에 연결하기 위한 서버 주소 옵션을 결정 
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(4917);

	// udp 로 데이터 전송
	sendto(ssock, (void*)buf, MAXBUF, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
	printf("Send message : %s\n", buf);
	clen = sizeof(client_addr);

	// udp 로 데이터 수신 
	recvfrom(ssock, (void*)buf, MAXBUF, 0, (struct sockaddr*)&client_addr, &clen);
	printf("Receive message : %s\n", buf);

	close(ssock);
	return 0;
}
