


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

int main() {
    char input[MAX_INPUT];
    char  *argv[MAX_INPUT];
    while (1) {
        printf("MyShell >>> ");
        scanf("%[^\n]%*c",input);
        parse(input, argv);
        if(strcmp(argv[0],"exit") == 0){
            break;
        }
        if(fork()==0){
            execv(argv[0],argv);
        }
        else{
            wait(NULL);
        }

    }
    return 0;
}

