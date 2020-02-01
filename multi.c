/* multi.c */
#define _PROGRAM_NAME "multi"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//forward declarations for our helper functions
void runccd(char *inputCommand);
void runcpwd();
void commandRunner();

int main(int argc, char *argv[]) {
	FILE *filePointer;
	char command[129];
	time_t process_start, process_end;
	long page_faults, soft_page_faults, hard_page_faults;
	int lineNumber[];
	struct rusage forPageFaults;
	struct rusage *ptr_forPageFaults;
	ptr_forPageFaults = &forPageFaults;

	//loop through ARGV and parse values to an integer
	for(int i=0, i<argc, i++) {
		lineNumber[i] = argv[i]
	}

	//open the file to read
	filePointer = fopen("/multi.txt", "r");

	//read each line
	for(int i=0; i<32; i++){
		commandRunner();
		
		//check for >32 args, print an error message if so
		if(i==31 && (getc(filePointer) != EOF)){
			printf("ERROR: MORE THAN 32 ARGUMENTS DETECTED. ONLY THE FIRST 32 WERE EXECUTED.");
		}
	}
	//close the file
	fclose(filePointer);
}

//file-reading helper method
void commandRunner() {
	//----------------preliminary checks and setup-----------------
	
	//copy new line to command array
	fgets(command, 129, (FILE*)filePointer);

	//check if the command contains a \n
	//if not, then the command must be too long.
	if(strchr(command, '\n') == NULL){
		printf("ERROR: COMMAND TOO LONG");
		continue;
	}

	//account for empty lines: check if line is empty
	//if so, continue to next line
	if(command[0] == '\n'){
		continue;
	}

	//-----------------running the input line-------------------------
	printf("Running command: %s\n", command);

	//TODO: integrate the following
	//somewhere while this is going on:
	//use wait3(WNOHANG) to wait for children to finish
	//if wait3() returns info about completed child process, print statistics and repeat loop
	//if wait3() returns nothing, exit loop and read next command
		//if not background process, use wait() without WNOHANG to finish other background commands first
		//once complete, loops wait3(WNOHANG) to pick up remaining tasks
		//if wait3(WNOHANG) returns an error, read next command

	//check if the command is either of the custom commands
	//if so, run that specifically
	//if not, the command is a normal command: run it normally
	char* firstArg = strtok(command, " ");
	if(strcmp(firstArg, "ccd") == 0){
		//modifies the command string to not include ccd
		memmove(command, command+4, strlen(command));
		runccd(command);
	} else if(strcmp(firstArg, "cpwd") == 0){
		//modifies the command string to not include cpwd
		memmove(command, command+4, strlen(command));
		runcpwd(command);
	} else{
		process_start = clock();
		system(command);
		getrusage(RUSAGE_CHILDREN, ptr_forPageFaults);
		process_end = clock();

		//print statistics (only for regular commands)
		printf("-- Statistics--\n");
		time_elapsed = process_end - process_start;
		printf("Elapsed time: %d milliseconds\n", time_elapsed);
		hard_page_faults = forPageFaults.ru_majflt;
		soft_page_faults = forPageFaults.ru_minflt;
		page_faults = hard_page_faults + soft_page_faults;
		printf("Page Faults: %ld\n", page_faults);
		printf("Page Faults (reclaimed): %ld\n", soft_page_faults);
		printf("-- End of Statistics--\n\n");
	}
}

//ccd helper method
void runccd(char *inputCommand){
	chdir(inputCommand);
	printf("Changed to directory: %s\n", inputCommand);
}

//cpwd helper method
void runcpwd(){
	//set to max linux path size
	char cwd[4096];
	getcwd(cwd, 4096);
	printf("Current directory: %s\n", cwd);
}
