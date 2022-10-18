// Grant Guernsey

#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 
// I made the size here one because with a larger buffer size I was having issues with it adding unnecessary bogus char to end of files
#define MSGSIZE 1



// For -a change w to file to a if there is an a, also ave to change the f open to 2 instead of one
// For multiple files, check if argc is greater than 2 i guess and then go through a for loop for all of them and write 
int main(int argc, char **argv) 
{   
    // Creating the file pointer which is the file passed into t
    FILE *fp;

    // Creating the in buffer char array and the pipe
    char inbuf[MSGSIZE];
    int p[2];  

    // Creating the child pid and the status for the child to return
    pid_t child;
    int status;
    
    
    // Creating the pipe and exiting if the pipe creation fails
    if(pipe(p) < 0) exit(1);

    // Forking to create the child process
    child = fork();   

    // Parent process computation
    if(child != 0)
    { close(p[0]); //Closing the read end of the pipe as it will not be used

        // While the char array of inbuf is being filled with the info from STDIN_FILENO or the standard input. Used this instead of stdin because stdin lef the file hanging with erors
        while (read(STDIN_FILENO, inbuf, MSGSIZE) != 0)
        { 
           // Write the info from the command ran into the pipe for the child process to read from
           write(p[1], inbuf, MSGSIZE);
        }

        close(p[1]); // Closing the write end of the pipe because everything has been written 
        waitpid(child, &status, 0); // Waiting on the child to finish up its calculations
    }
    // Child process computation
    else
    { close(p[1]); // Closes the write end of the pipe as it is not used
       
        fp = fopen(argv[1], "w"); // Opens the text file given as an argument to write to 


        // Loops while the pipe is not empty
        while(read(p[0], inbuf, MSGSIZE) != 0){
            // Puts the inbuf into the text file
            fputs(inbuf, fp);
        }

        // Child process exits with a status of zero
        exit(0);
    }
       
}
    