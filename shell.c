


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include  <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 200
void  parse(char *line, char **argv)
{
    while (*line != '\0') {       /* if not the end of line ....... */
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';     /* replace white spaces with 0    */
        *argv++ = line;          /* save the argument position     */
        while (*line != '\0' && *line != ' ' &&
               *line != '\t' && *line != '\n')
            line++;             /* skip the argument until ...    */
    }
    *argv = '\0';                 /* mark the end of argument list  */
}
void  execute(char **argv)
{
    pid_t  pid;
    int    status;

    if ((pid = fork()) < 0) {     /* fork a child process           */
        printf("*** ERROR: forking child process failed\n");
        exit(1);
    }
    else if (pid == 0) {          /* for the child process:         */
        if (execvp(*argv, argv) < 0) {     /* execute the command  */
            printf("*** ERROR: exec failed\n");
            exit(1);
        }
    }
    else {                                  /* for the parent:      */
        while (wait(&status) != pid)       /* wait for completion  */
            ;
    }
}
int main() {
    char input[MAX_INPUT];         /* the input line                 */
    char  *argv[MAX_INPUT];              /* the command line argument      */
    while (1) {                   /* repeat until done ....         */
        printf("MyShell >>> ");
        scanf("%[^\n]%*c",input);
        parse(input, argv);
        if(strcmp(argv[0],"exit") == 0){
            break;
        }
        execute(argv);/* otherwise, execute the command */
    }
    return 0;
}

