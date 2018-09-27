#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#define MAXBUF 256

int main(int argc, char** argv){
	if(argc!=2){
		printf("usage: ./a.out [id]\n");
		exit(1);
	}

	int ssock;
	int clen;
	struct sockaddr_in client_addr, server_addr;
	char buf[MAXBUF], msg[MAXBUF];

	/*create socket*/
	if((ssock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("socket error :");
		exit(1);
	}

	/*server option*/
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(3317);

	/*transmit UDP DATA*/
	
	fgets(buf,sizeof(buf),stdin);
	sprintf(msg,"%s: %s", argv[1], buf);
	sendto(ssock, (void*)msg, MAXBUF, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	/*print msg from server*/
	recvfrom(ssock, (void*)msg, MAXBUF, 0, (struct sockaddr*)&client_addr, &clen);
	printf("%s",msg);

	close(ssock);
	return 0;
}
