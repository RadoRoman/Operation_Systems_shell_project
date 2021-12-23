# Operation_Systems_shell_project
Code documentation
Main functions:
Int main(int argc, char *argv[])
To keep the shell running an infinite while loop calls the function shell_parse() and keeps running as long as shell_parse() does not return zero.
Int shell_parse()
In this function no arguments are handed over.
The function can return 1 to keep the loop running or 0 to break the loop in main().
At the start of the function username and hostname are fetched and outputted in a print statement which is displayed while the console is running.
The fgets function catches user input in the created shell.
Char line[100];
fgets(line,100,stdin);

The created variable line which is an array of characters is then further split into tokens with the strtok() function. As a delimited a space AND \n is used.
Token = strtok(line,”\n “);
Once the token are extracted an array of tokens is created in a while loop. This tokenarray will be used further to search for keywords and modifiers.
After creating the tokenarray an if-block starts that distinguishes 3 cases:
•	Keyword quit
•	Keyword globalusage
•	Keyword exec
If block for keyword quit:
The strcmp() function is used to compare the first item in the tokenarray with the string “quit”, if this statement is true a print statement asks the user to confirm his choice by pressing Y or N. The fgets function takes the user input and compares with the Y and N string (again using strcmp()). In case of user pressing N or an unknown key the shell stays open (by returning 1) and for Y the shell closes (by returning 0).
If block for keyword globalusage:
Here the same method is used to if the first item in tokenarray is equal to globalusage AND also the length of token array (names int j) needs to be 1. 
If block for keyword exec:
If exec is the first item in the token array and more commands are entered (by checking int j). The 2 helper functions to check for modifiers are called. Both helper functions are able to identify the modifiers but they are not working in terms of the requested actions/output.
For the modifier > we tried to make C open a file and use dup2 to write text in a file. However we only managed to create a file but the content didn’t show up as desired.
For the modifier & we have not written any output for creating a process in the background.
If none of the modifiers appear after the exec command a child is created with the fork() function and its PID returned after the child process in finished.
Helper functions:
Void print_array(int len, char* arr[])
This simple function uses a for loop to print an array of strings
Int check_modifier1(char *arr[], int len)
This function checks via the strcmp() function if the modifier > is present in any of the strings from the array.
Int check_modifier2(char *arr[], int len)
This function checks via the strcmp() function if the modifier & is present in any of the strings from the array.





