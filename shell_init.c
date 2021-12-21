#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/utsname.h>

void shell_quit(){
    char quitvar[] = "N";
    printf("Are you sure you want to quit [Y/N]. ");
    scanf("%s",quitvar);
    if (strcmp(quitvar,"Y")==0){
        printf("shutdown in progress...\ngoing to cancel threads...\ngood bye\n");
        exit(0);}

}

int shell_parse(char* variable){   
    /*printf("%s", variable);*/
    char *token;
    char* tokenarray[10];
    token = strtok(variable, " ");
    int j =0;
    /*create the tokenarray*/
    while (token != NULL){
       tokenarray[j]=token;
       token = strtok(NULL," ");
       j++ ;
    }
    /*for(int i=0;i<j;i++){
        printf("%s\n",tokenarray[i]);
        printf("%s",tokenarray[0]);
        }*/
    
    /*if block for quit*/
    if (strcmp(tokenarray[0],"quit\n")==0){
        shell_quit();
    }
    /*if block for exec*/
    if (strcmp(tokenarray[0],"exec")==0){
        printf("perform statements exec\n");
    }
    /*if block for exec*/
    if (strcmp(tokenarray[0],"globalusage\n")==0){
        printf("show some data\n");
    }
    return 1;

}


void shell_init(){ 

    struct utsname uts;
    char variable[100];
    if (uname(&uts) == -1)
    perror("uname");
    printf("%s@", getenv("USER"));
    printf("%s>", uts.nodename);
    /*needs 3 input arguments*/
    fgets(variable,100,stdin);
    shell_parse(variable);
    
}


int main(){
    printf("WELCOME TO IMCSH V1.0.0\n");
    while(1){
        shell_init();

    };
    return(1);
}