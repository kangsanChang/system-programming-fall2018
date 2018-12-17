#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/stat.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h> 
#include <signal.h>

#define MAXBUF 256

void handler(int sig){
  pid_t pid;
  int status;
  pid = wait(&status);
  printf("%d번 자식 프로세스가 종료되었습니다\n", pid);
}

int main() {
  int ssock, csock;
  int clen;
  pid_t pid;
  struct sockaddr_in client_addr, server_addr;
  char buf[MAXBUF] = "I like you!";

  signal(SIGCHLD, (void *)handler);

  /* 소켓 생성 */ 
  if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    perror("socket error : ");
    exit(1);
  }
  /* 서버 옵션 지정*/
  clen = sizeof(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(7917);

  /* 서버 옵션 설정 */
  if (bind(ssock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
    perror("bind error : ");
    exit(1);
  }

  /* 연결 수신 대기 */ 
  if (listen(ssock, 5) < 0){
    perror(" listen error : ");
    exit(1);
  }
  while (1){
    /* 연결 처리 */ 
    csock = accept(ssock, (struct sockaddr *)&client_addr, &clen); 
    /* fork()를 이용하여 multi-process 방식으로 통신 처리 */
    pid = fork();
    switch (pid){
    case -1:
      /* fork 함수 에러 발생 */ 
      perror(" fork error : ");
      exit(1);
    case 0:
      /* 자식 프로세스의 클라이언트 소켓 처리 */
      close(ssock);
      pid = getpid();
      printf("%d번 프로세스에 새로운 소켓이 연결되었습니다\n", pid);

      while (read(csock, buf, MAXBUF) > 0){
		char* ptr;
		if(strcmp(buf,"exit\n")==0){
			printf("%d번 프로세스에서 프로그램을 종료합니다.\n", pid);
			close(csock);
			exit(0);
		}
		char* opp = strpbrk(buf,"+-*/");
		if(!opp){
			strcpy(buf, "*** Input Error! ***");
		}else{
			char operator = opp[0];
			int operand1 = atoi(strtok(buf, &operator));
			int operand2 = atoi(opp+1);
		
			switch(operator){
				case '+':
						sprintf(buf,"Answer : %d", operand1+operand2);
						break;
				case '-':
						sprintf(buf,"Answer : %d", operand1-operand2);
						break;
				case '*':
						sprintf(buf,"Answer : %d", operand1*operand2);
						break;
				case '/':
						sprintf(buf,"Answer : %d", operand1/operand2);
						break;
			}
		}
        if (write(csock, buf, MAXBUF) <= 0){
          perror("write error : ");
          exit(1);
        }
	  }
      close(csock);
      printf("%d번 프로세스 소켓의 연결이 종료되었습니다\n", pid);
      exit(1);
    default:
      /* 부모 프로세스의 클라이언트 소켓 제거 */
      close(csock);
      break;
      }
    }
    return 0;
}

