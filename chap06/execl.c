#include <unistd.h>

main(int argc, char *argv[]){
	execl("/bin/ls", "ls", argv[1],(char*)0);
}
