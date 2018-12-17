#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXBUF 256
#define MAX(a,b) ((a) > (b)) ? (a) : (b)
void str_cli(FILE *fp, int sockfd){
	int maxfdp1;
	fd_set rset;
	char sendline[MAXBUF], recvline[MAXBUF];

	FD_ZERO(&rset);
	while(1){
		FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = MAX(fileno(fp), sockfd) +1;
		select(maxfdp1, &rset, NULL, NULL, NULL);
		
		// socket 이 읽기 가능한 상황
		if(FD_ISSET(sockfd, &rset)){
			if(read(sockfd, recvline, MAXBUF) == 0){
				perror("str_cli: server terminated prematurely");
				exit(1);
			}
			fputs(recvline, stdout);	
		}

		// 입력하는 상황
		if(FD_ISSET(fileno(fp), &rset)){
			if(fgets(sendline, MAXBUF, fp) == NULL)
					return; /* all done */
			write(sockfd, sendline, strlen(sendline));
		}
	}
}

int main(){
	int ssock;
	int clen;
	struct sockaddr_in server_addr;
	char buf[MAXBUF];

	if((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket error : ");
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

	str_cli(stdin, ssock);
}
