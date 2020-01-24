/* boring.c */
#define _PROGRAM_NAME "boring"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char command[50];
	int a = 10;
	char *binaryPath = "~";
	char *arg1 = "ls -al";
	char *arg2 = "/home";

	//running whoami
	printf("running whoami...\n");
	strcpy(command, "whoami");
	system(command);

	//whoami stats
	printf("-- Statistics--\n");
	printf("Elapsed time: %d ms\n",a);
	printf("Page Faults: %d\n",a);
	printf("Page Faults (reclaimed): %d\n",a);
	printf("-- End of Statistics--\n\n");

	//running last
	printf("running last...\n");
	strcpy(command, "last");
	system(command);

	//last stats
	printf("-- Statistics--\n");
	printf("Elapsed time: %d ms\n",a);
	printf("Page Faults: %d\n",a);
	printf("Page Faults (reclaimed): %d\n",a);
	printf("-- End of Statistics--\n\n");

	//running ls -al /home
	printf("running ls...\n");
	execl(binaryPath, binaryPath, arg1, arg2, NULL);

	//ls -al /home stats
	printf("-- Statistics--\n");
	printf("Elapsed time: %d ms\n",a);
	printf("Page Faults: %d\n",a);
	printf("Page Faults (reclaimed): %d\n",a);
	printf("-- End of Statistics--\n\n");
	

	return 0;
}
