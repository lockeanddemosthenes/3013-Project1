/* custom.c */
#define _PROGRAM_NAME "custom"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//forward declarations for our two helper functions
void runccd(char *inputCommand);
void runcpwd();

int main(int argc, char *argv[]) {
    FILE *filepointer;
    char command[129];
    time_t process_start, process_end;
    long page_faults, soft_page_faults, hard_page_faults;
    struct rusage forPageFaults;
    struct rusage *ptr_forPageFaults;
    ptr_forPageFaults = &forPageFaults;

    //open the file to read
    filepointer = fopen("/custom.txt", "r");

    //read each line
    for(int i=0; i<32; i++){
        //----------------preliminary checks and setup-----------------

        //copy new line to command array
        fgets(command, 129, (FILE*)filepointer);

        //check if the command contains a new line
        //if not, then the command must be too long.
        //TODO? check if the command is the last line
        if(strchr(command, '\n') == NULL){
            printf("ERROR: THIS COMMAND IS LONGER THAN ALLOWED INPUT");
            continue;
        }

        //check if the line is empty, continue to next line if so
        //doing it this way allows us to account for blank lines followed by more commands
        if(command[0] == '\n'){
            continue;
        }

        //-----------------running the input line-------------------------
        printf("Running command: %s\n", command);

        //check if the command is either of the custom commands, run that if so
        //and if not, the command is a normal command, so we run it
        char* firstArg = strtok(command, " ");
        if(strcmp(firstArg, "ccd") == 0){
            //modifies the command string to not include ccd
            memmove(command, command+4, strlen(command));
            runccd(command);
        } if(strcmp(firstArg, "cpwd") == 0){
            //modifies the command string to not include cpwd
            memmove(command, command+4, strlen(command));
            runcpwd(command);
        } else{
            process_start = clock();
            system(command);
            getrusage(RUSAGE_CHILDREN, ptr_forPageFaults);
            process_end = clock();

            //print statistics (they only get printed with regular commands)
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

        //check for >32 args, print an error message if so
        if(i==31 && (getc(filepointer) != EOF)){
            printf("ERROR: MORE THAN 32 ARGUMENTS DETECTED. ONLY THE FIRST 32 WERE EXECUTED.");
        }
    }

    //close the file
    fclose(filepointer);
}

//runs the ccd command
void runccd(char *inputCommand){
    chdir(inputCommand);
    printf("Changed to directory: %s\n", inputCommand);
}

//runs the cpwd command
void runcpwd(){
    //set to max linux path size
    char cwd[4096];
    getcwd(cwd, 4096);
    printf("Current directory: %s\n", cwd);
}
