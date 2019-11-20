

#include <stdio.h>

int main ( int argc, char **argv ) {
    printf("-----   reverse START [argc = %d]  -----\n",argc);
    for(int i=0;i<argc-1;++i){
        printf("%d: %s\n", i+1,argv[argc-i-1]);
    }
    printf("-------------   reverse END   -----------\n");
    return 0; 
}