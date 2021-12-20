#include<stdio.h>
#include<string.h>
/* */

int main (int argc, char *argv[]){
    /*x is the first argument*/
    char *x = argv[1];
    if(!strcmp(x,"quit")) {
        printf("enter code to quit program\n");
        break;
        }
    else if (!strcmp(x,"globalusage")) {
        printf("IMCSH Version 1.1 created by R.Roman and J.Berger\n");
        }
    else if (!strcmp(x,"exec")) {
        printf("enter code for execution here\n");
        }
    else { 
        printf("do whatever");
        }
    ;

    /* *
    for (int i = 0; i < argc; i++)
    printf("argv[%d] = %s\n", i, argv[i]); 
    */

    /*if argv[1] == 'globalusage' show IMCSH Version 1.1 created by <author(s)> */
    /*if argv[1] == 'exec' do something  and return PID*/
        /*if modifier & exists at argv[-1] run process in the background*/
    /*if argv[1] == 'quit' exit  */
    /*if modifier '>' and <filename.txt> exists append the text other wise create the file and add text  */
    
    return 0;

}