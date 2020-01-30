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
	long page_faults, soft_page_faults, hard_page_faults;
	struct rusage forPageFaults;
	struct rusage *ptr_forPageFaults;
	ptr_forPageFaults = &forPageFaults;

	//---------------------whoami section------------------
	//start timer
	process_start = clock();
	//running whoami
	printf("running whoami...\n");
	strcpy(command, "whoami");
	system(command);
	//retrieving pagefault info
    getrusage(RUSAGE_CHILDREN, ptr_forPageFaults);
	//end timer
	process_end = clock();

	//whoami stats
	printf("-- Statistics--\n");
	//timer code
    time_elapsed = process_end - process_start;
	printf("Elapsed time: %d milliseconds\n", time_elapsed);
	//pagefaults code
    hard_page_faults = forPageFaults.ru_majflt;
    soft_page_faults = forPageFaults.ru_minflt;
    page_faults = hard_page_faults + soft_page_faults;
    printf("Page Faults: %ld\n", page_faults);
	printf("Page Faults (reclaimed): %ld\n", soft_page_faults);
	printf("-- End of Statistics--\n\n");


	//----------------------last section-----------------------
	//start timer
    process_start = clock();
    //running last
	printf("running last...\n");
	strcpy(command, "last");
	system(command);
	//retrieving pagefault info
    getrusage(RUSAGE_CHILDREN, ptr_forPageFaults);
    //end timer
    process_end = clock();

	//last stats
	printf("-- Statistics--\n");
	//timer code
    time_elapsed = process_end - process_start;
	printf("Elapsed time: %d milliseconds\n", time_elapsed);
	//pagefaults code
    hard_page_faults = forPageFaults.ru_majflt;
    soft_page_faults = forPageFaults.ru_minflt;
    page_faults = hard_page_faults + soft_page_faults;
    printf("Page Faults: %ld\n", page_faults);
	printf("Page Faults (reclaimed): %ld\n", soft_page_faults);
	printf("-- End of Statistics--\n\n");


	//-------------------ls -al /home section------------------------
	//start timer
    process_start = clock();
    //running ls -al /home
	printf("running ls...\n");
	execl(binaryPath, binaryPath, arg1, arg2, NULL);
    //retrieving pagefault info
    getrusage(RUSAGE_CHILDREN, ptr_forPageFaults);
    //end timer
    process_end = clock();


	//ls -al /home stats
	printf("-- Statistics--\n");
	//timer code
    time_elapsed = process_end - process_start;
	printf("Elapsed time: %d milliseconds\n", time_elapsed);
	//pagefaults code
	hard_page_faults = forPageFaults.ru_majflt;
	soft_page_faults = forPageFaults.ru_minflt;
    page_faults = hard_page_faults + soft_page_faults;
	printf("Page Faults: %ld\n", page_faults);
	printf("Page Faults (reclaimed): %ld\n", soft_page_faults);
	printf("-- End of Statistics--\n\n");
	

	return 0;
}
