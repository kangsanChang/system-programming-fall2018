#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#define MAXBUF 256

int main(){
	int ssock, csock;
	int clen;
	pid_t pid;
	struct sockaddr_in client_addr, server_addr;
	char buf[MAXBUF] = "i like you!";

	if((ssock = socket(AF_INET, SOCK_STREAM, 0))<0){
		perror("socket error: ");
		exit(1);
	}

	clen =sizeof(client_addr);

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(3317);

	if(bind(ssock,(struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		perror("bind error:");
		exit(1);
	}

	if(listen(ssock, 5) <0){
		perror("listen error : ");
		exit(1);
	}

	while(1){
		csock = accept (ssock, (struct sockaddr *)&client_addr, &clen);

		pid = fork();
		switch(pid){
			case -1:
					perror("fork err:");
					exit(1);
			case 0 :
					close(ssock);
					pid = getpid();
					printf("%d 번 프로세스에 새 소켓 연결됨 \n",pid);

					while(read(csock, buf, MAXBUF) >0){
						if(write(csock, buf, MAXBUF) <= 0){
							perror("write error :");
							exit(1);
						}
					}

					close(csock);
					printf("%d 번 프로세스 소켓의 연결이 종료됨 \n",pid);
					exit(1);
			default:
					close(csock);
					break;
		}
	}
	return 0;		
}
