/* boring.c */
#define _PROGRAM_NAME "boring"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <timer.h>

int main(int argc, char *argv[]) {
	char command[50];
	int time_elapsed = 10;
	char *binaryPath = "~";
	char *arg1 = "ls -al";
	char *arg2 = "/home";
	time_t process_start, process_end;
	int pid_whoami;
	int pid_last;
	int pid_ls;

	//---------------------whoami section------------------
	//start timer
	process_start = clock();
	//running whoami
	printf("running whoami...\n");
	strcpy(command, "whoami");
	system(command);
	//getting pid for retrieving pagefault info

	//end timer
	process_end = clock();

	//whoami stats
	printf("-- Statistics--\n");
	//timer code
    time_elapsed = process_end - process_start;
	printf("Elapsed time: %d milliseconds\n", time_elapsed);
	//pagefaults code
	printf("Page Faults: %d\n", a);
	printf("Page Faults (reclaimed): %d\n", a);

	printf("-- End of Statistics--\n\n");


	//----------------------last section-----------------------
	//start timer
    process_start = clock();
    //running last
	printf("running last...\n");
	strcpy(command, "last");
	system(command);
	//getting pid for retrieving pagefault info

	//end timer
    process_end = clock();

	//last stats
	printf("-- Statistics--\n");
	//timer code
    time_elapsed = process_end - process_start;
	printf("Elapsed time: %d milliseconds\n", time_elapsed);
	//pagefaults code
	printf("Page Faults: %d\n", a);
	printf("Page Faults (reclaimed): %d\n", a);
	printf("-- End of Statistics--\n\n");


	//-------------------ls -al /home section------------------------
	//start timer
    process_start = clock();
    //running ls -al /home
	printf("running ls...\n");
	execl(binaryPath, binaryPath, arg1, arg2, NULL);
    //getting pid for retrieving pagefault info

    //end timer
    process_end = clock();


	//ls -al /home stats
	printf("-- Statistics--\n");
	//timer code
    time_elapsed = process_end - process_start;
	printf("Elapsed time: %d milliseconds\n", time_elapsed);
	//pagefaults code
	printf("Page Faults: %d\n", a);
	printf("Page Faults (reclaimed): %d\n", a);
	printf("-- End of Statistics--\n\n");
	

	return 0;
}
