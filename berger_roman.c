#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/utsname.h>
#include<fcntl.h>

//helper function to print an array of strings
void print_array(int len, char* arr[]){
    printf("array has %d entries\n", len );
    for (int i=0;i<len ;i++){
        printf("%s\n",arr[i]);
    }
}

//function to identify if the modifier > is present in the command
//returns 1 if modifier is present, returns 0 if not present
int check_modifier1(char *arr[], int len){
    //printf("inside check_mod1 function: \n");
    for (int i=0;i<len ;i++)
    {
    if (strcmp(arr[i],">")==0){
        //printf("found modifier: > at %d index\n",i);
        return 1;
    }
    }
    return 0;
}

//function to identify is the modifier & is present in the command
//returns 1 if modifier is present, returns 0 if not present
int check_modifier2(char *arr[], int len){
    //printf("inside check_mod2 function: \n");
    for (int i=0;i<len ;i++)
    {
    if (strcmp(arr[i],"&")==0){
        return 1;
    }
    }
    return 0;
}

//this function parses the user input in the shell
//3 keywords are parsed:
// globalusage, exec and quit
int shell_parse(void){
    char* username;
    char hostname[_SC_HOST_NAME_MAX];
    gethostname(hostname, _SC_HOST_NAME_MAX);
    username = getenv("USER");
    printf("%s@%s>",username,hostname);
    char line[100];

    //take user input with fgets and save it in variable line
    fgets(line,100,stdin);


    //tokenize user input with function strtok
    char *token;
    char* tokenarray[10];
    token = strtok(line, "\n ");

    //create a tokenarray
    int j =0;
    while (token != NULL){
       tokenarray[j]=token;
       token = strtok(NULL,"\n ");
       j++ ;
    };

    //print_array(j,tokenarray);
    //print_array(argc, argv);

    // if block for keyword quit
    if(strcmp(tokenarray[0],"quit")==0){
        char var[2];
        printf("sure? [Y/N]");
        fgets(var,2,stdin);
        if (strcmp(var,"Y")==0){
            return 0;
        }
        else if (strcmp(var,"N")==0){ 
            return 1;}
        else{ 
            printf("unknown command\n");
            return 1;}
    }

    // if block for keyword globalusage
    if((strcmp(tokenarray[0],"globalusage")==0) && j ==1){
        printf("IMCSH Version 1.0 created by Rado and Jacqui\n");
    }

    //if block for keyword exec
    if((strcmp(tokenarray[0],"exec")==0) && j>1){
        //check for modifiers > and &, if 1 is returned the modifier is present

        //check first for modifier >
        if (check_modifier1(tokenarray,j)==1){
            /*takes the input from tokenarray and adds them into cmd array for the execvp function*/
            //printf("modifier > found\n");
            //printf("length of tokenarray: %d\n", j);
            //get file name from last index tokenarray
            int index = j-1;
            //printf("%s\n", tokenarray[index]);
            //use dup2 system call
            int fd = open(tokenarray[index], O_WRONLY | O_CREAT, 0777);
            dup2(fd, 1);
            close(fd);
            return 1;
            }


        //check for modifier &   
        }else if (check_modifier2(tokenarray,j)==1){
            printf("modifier & found\n");

        }else{
        //no modifiers present, parse input string
        /*takes the input from tokenarray and adds them into cmd array for the execvp function*/
        char* cmd = tokenarray[1];
        /*create a new array cmd array and use all tokenarray componenets except the one
        at index 0. Then add NULL at the last element of cmd array*/
        char *cmdarray[j];
        int last_index = j-1;
        for (int i=0;i<j;i++){
            int ii = i+1; //c doesnt allow to have i+1 in square brackets so we had to inititalize new integers
            cmdarray[i]=tokenarray[ii];
        }
        cmdarray[last_index] = NULL;//last entry needs to be NULL

        pid_t pid;
        pid = fork();
        if (pid <0){
            fprintf(stderr, "Fork failed");
            return 1;}
        else if (pid ==0) {
            
            execvp(cmd,cmdarray);} //ls,-l,NULL

        else {
            wait(NULL);
            printf("Child PID was: %d\n", pid);}
    }

    return 1;
    }



int main(int argc, char *argv[]){

    int i = 1;

    while (i == 1){
        if (shell_parse()==0){
            exit(0);
        }
    };
}