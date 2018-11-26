#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
	FILE *fpr;
	FILE *fpw;
	char buffer [BUFSIZ + 1];

	memset(buffer, '\0', sizeof(buffer));
	fpr = popen("who", "r");
	fread(buffer, sizeof(char), BUFSIZ, fpr);
	fpw = popen("sort","w");
	fwrite(buffer, sizeof(char), strlen(buffer), fpw);
	pclose(fpr);
	pclose(fpw);
}
