#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <ctype.h>

#define MAXBUF 256

int main(){
	int ssock;
	int clen;
	struct sockaddr_in client_addr, server_addr;
	char received_msg[MAXBUF];
	int changedTemp;
	char tempType;
	char answer[MAXBUF] = "";

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
		tempType = received_msg[strlen(received_msg)-2];
		if (toupper(tempType) == 'F')
		{
			changedTemp = (atoi(received_msg)-32)*5 / 9;
			sprintf(answer, "%d", changedTemp);
			strcat(answer, "C");
		}
		else if (toupper(tempType) == 'C')
		{
			changedTemp = (atoi(received_msg)* 9 / 5) + 32;
			sprintf(answer, "%d", changedTemp);
			strcat(answer, "F");
		}else{
			strcat(answer, "Wrong input!\n");
		}
		sendto(ssock, (void *)answer, MAXBUF, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
		strcpy(answer, "");
	}
	close(ssock);
	return 0;
}
