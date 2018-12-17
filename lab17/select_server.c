#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#define MAXBUF 256

int main(){
	int ssock,csock;
	int clen, data_len;
	int fd;
	pid_t pid;
	struct sockaddr_in client_addr, server_addr;
	fd_set read_fds, tmp_fds;
	char buf[MAXBUF] = "I like you!";

	// socket 생성
	if((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket error : ");
		exit(1);
	}

	// server option 지정
	clen = sizeof(client_addr);

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(7917);

	//server option 설정 
	if(bind (ssock, (struct sockaddr *)&server_addr, sizeof(server_addr)) <0){
		perror("bind error : ");
		exit(1);
	}

	//연결 수신 대기
	if(listen(ssock,5) < 0){
		perror("listen error : ");
		exit(1);
	}

	FD_ZERO(&read_fds);
	FD_SET(ssock, &read_fds);

	while(1){
		tmp_fds = read_fds;
		if(select(FD_SETSIZE, &tmp_fds, (fd_set*)0, (fd_set*)0, (struct timeval *)0) < 1){
			perror("select error : ");
			exit(1);
		}

		for(fd=0; fd<FD_SETSIZE; fd++){
			if(FD_ISSET(fd, &tmp_fds)){
				// FD event 가 발생했을 경우
				if(fd==ssock){
					//event 발생 FD 가 server socket 인 경우
					//connect
					csock = accept(ssock, (struct sockaddr *)&client_addr, &clen);
					//FD에 추가
					FD_SET(csock, &read_fds);
					printf("새로운 클라이언트 %d번 파일 디스크립터 접속\n", csock);
				} else {
					// event 발생 FD 가 client socket 인 경우
					// 해당 FD 소켓으로부터 데이터를 읽는다.
						data_len = read(fd, buf, MAXBUF);
						buf[data_len]='\0';
						if(data_len > 0){
							// 해당 FD socket에 데이터를 쓴다
							write(fd, buf, MAXBUF);	
						}else if(data_len < 0){
							// error handling
							perror("read error : ");
							exit(1);
						}
				}
			}
		}
	}
	return 0;
}
