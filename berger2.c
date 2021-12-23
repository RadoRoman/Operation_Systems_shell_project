#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/utsname.h>
#include <fcntl.h>

void print_array(int len, char* arr[]){
    printf("array has %d entries\n", len );
    for (int i=0;i<len ;i++){
        printf("%s\n",arr[i]);
    }

}

int check_modifier1(char *arr[], int len){
    //printf("inside check_mod1 function: \n");
    for (int i=0;i<len ;i++)
    {
    if (strcmp(arr[i],">")==0){
        printf("found modifier: > at %d index\n",i);
        return 1;
    }
    }
    return 0;
}

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

int shell_parse(){
    char* username;
    char hostname[_SC_HOST_NAME_MAX];
    gethostname(hostname, _SC_HOST_NAME_MAX);

    username = getenv("USER");
    printf("%s@%s>",username,hostname);
    char line[100];
    /*take user input*/
    fgets(line,100,stdin);


    /*tokenize user input*/
    char *token;
    char* tokenarray[10];
    token = strtok(line, "\n ");

    /*create the tokenarray*/
    int j =0;
    while (token != NULL){
       tokenarray[j]=token;
       token = strtok(NULL,"\n ");
       j++ ;
    };

    //print_array(j,tokenarray);
    //print_array(argc, argv);

    /*for keyword quit*/
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

    /*for keyword globalusage*/
    if((strcmp(tokenarray[0],"globalusage")==0) && j ==1){
        printf("IMCSH Version 1.0 created by Rado and Jacqui\n");
    }

    /*keyword for exec*/
    if((strcmp(tokenarray[0],"exec")==0) && j>1){
        /*check for moifiers > and &, if 1 is returned the modifier is present*/
        if (check_modifier1(tokenarray,j)==1){
            printf("modifier > found\n");
            printf("length of tokenarray: %d\n", j);
            //get file name and check if present
            int index = j-1;
            printf("%s\n", tokenarray[index]);

            //use dup2 system call
            int file = open(tokenarray[index], O_WRONLY | O_CREAT, 0777);
            dup2(file,STDOUT_FILENO);
            close(file);
            
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
}


int main(int argc, char *argv[]){

    int i = 1;

    while (i == 1){
        if (shell_parse()==0){
            exit(0);
        }
    };
}