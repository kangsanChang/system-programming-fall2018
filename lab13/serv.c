#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#define NAME "socket"

void main() {
	int sock, length, fromlen;
	struct sockaddr_un name, from;
	char buf[1024];

	sock = socket(PF_UNIX, SOCK_DGRAM, 0); // socket(domain, type, protocol(0 하면 알아서 맞춰줌))
	// unix Domain 에서 socket 의 주소 정보 지정하기
	name.sun_family = PF_UNIX; // UNIX 로 설정
	strcpy(name.sun_path, NAME); // 경로 설정

	bind(sock, (struct sockaddr *)&name, sizeof(struct sockaddr_un)); // 만든 주소(name)을 소켓에 바인딩 
	printf("socket->%s\n", NAME);

	recvfrom(sock, buf, 1024, 0, (struct sockaddr *)&from, &fromlen);

	printf("-> %s\n", buf);

	unlink(NAME);

	close(sock);
}
