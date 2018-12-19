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

	if((ssock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		perror("socket error : ");
		exit(1);
	}

	// socket 에 연결하기 위한 서버 옵션 설정 
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(4917);

	// socket에 ip 주소 등의 서버 옵션 설정
	if(bind(ssock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("bind error : ");
		exit(1);
	}
	clen = sizeof(client_addr);
	
	// udp data 수신
	while(1){

		recvfrom(ssock, (void*)buf, MAXBUF, 0, (struct sockaddr*)&client_addr, &clen);
		if(strcmp(buf,"exit")==0){
			char * byemsg = "bye bye!";
			sendto(ssock,(void*) byemsg, MAXBUF, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
			close(ssock);
			return 0;
		}
		strcpy(buf, "I miss you");

		// udp data 전송
		sendto(ssock,(void*) buf, MAXBUF, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
	}
	close(ssock);
	return 0;
}
