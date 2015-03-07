#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token sparators


int sfile(char *kw, char *ta) {
	FILE *fp;
	char temp[MAX_BUFFER];
        int line_num = 1;
        int find_result = 0; 
	fp = fopen(ta, "rb");	
	while(fgets(temp, MAX_BUFFER, fp) != NULL) {
               	  char *pos = strstr(temp, kw); // kw's initial point 
		  int count = (int)(pos-temp);  
		  int len = strlen(kw); // search keyword's length
		  if(pos != NULL) {
		        printf("In %s Line %d, Char: %d~%d\n", ta, line_num, count+1, count+len);
                        find_result++;
                }
                line_num++;
        }

        if(find_result == 0) {
                printf("Sorry, couldn't find a match.\n");
        }
        fclose(fp);  
	return 0;


}


/*******************************************************************/

int main (int argc, char ** argv)
{
char linebuf[MAX_BUFFER];                  // line buffer
char cmndbuf[MAX_BUFFER];                  // command buffer
char * args[MAX_ARGS];                     // pointers to arg strings
char ** arg;                               // working pointer
char * prompt = "(O-O) " ;                    // shell prompt
char *err;


// keep reading input until "exit" command or eof of redirected input 

while (!feof(stdin)) { 

// get command line from input


    fputs (prompt, stdout);                // write prompt
    fflush(stdout);
    if (fgets(linebuf, MAX_BUFFER, stdin )) { // read a line

// tokenize the input into args array

        arg = args;
        *arg++ = strtok(linebuf,SEPARATORS);   // tokenize input
        while ((*arg++ = strtok(NULL,SEPARATORS)));
                                           // last entry will be NULL 

        if (args[0]) {                     // if there's anything there

            cmndbuf[0] = 0;                // set zero-length command string

// check for internal/external command 

              // "clr" command
	      if (!strcmp(args[0],"clr")) { 
                strcpy(cmndbuf, "clear");
              // "find" command
            } else if (!strcmp(args[0],"find")) { 
        		if(args[1]==NULL || args[2]==NULL) {
        			printf("Usage: find keyword target\n");
			} else {
				// sfile(args[1], args[2]);
				if(args[2]=".")
                                args[2]="hello.txt";   
				sfile(args[1], args[2]);}
                               // strcat(cmndbuf, args[2]);

	      // "exit" command 
            } else if (strcmp(args[0], "exit") == 0) {  
                break;
	     // fork and exec
            } else {              
                pid_t pid;
		/*fork a child process*/
		pid = fork();
		if(pid<0){  /*error occurred*/
			fprintf(stderr, "Fork Failed");
		}
		else if(pid == 0){ /*child process*/
			//execlp("echo","echo", show, NULL);
			execvp(args[0], args);
		}
		else {  /*parent process*/
			wait(NULL);
		}
	    }
        
    
		if (cmndbuf[0])
                system(cmndbuf);
		}
	}
}
return 0; 
}
