#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#define NAME "socket"

void main() {
	int sock, length, tolen;
	struct sockaddr_un to;
	char buf[1024] = "This is a messaeg from the client";

	sock = socket(PF_UNIX, SOCK_DGRAM, 0);
	to.sun_family = PF_UNIX;
	strcpy(to.sun_path, NAME);

	sendto(sock, &buf, sizeof(buf), 0, (struct sockaddr *)&to, sizeof(to));

	close(sock);
}
