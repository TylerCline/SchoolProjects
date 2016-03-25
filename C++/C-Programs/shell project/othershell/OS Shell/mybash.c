/*
 * Headstart for Assignment 2
 * CS 4420/5420
 * 
 *
 * Student(s) Name:  Jordan Leach, Tyler Cline
 *
 *
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "parser.h"
#define READ 0
#define WRITE 1

extern char **environ;

//********************************************************
// Function Name: read_line()
// Description: Reads in a line of input from the terminal
//********************************************************
char* read_line();

//********************************************************
// Function Name: print_info(struct CommandData*)
// Description: Prints information of the line entered
//		 from read_line()
//********************************************************
void print_info(struct CommandData*);

//********************************************************
// Function Name: is_built_in(const struct CommandData*)
// Description: Function to check if the command entered
//		 is a built in shell command
//********************************************************
int is_built_in(const struct CommandData*);

//********************************************************
// Function Name: executeBuiltInCommand(struct CommandData*, const int commandNum, int*)
// Description: Function to execute the given command if it is built in
//*******************************************************
void executeBuiltInCommand(struct CommandData*, const int commandNum, int*);

//********************************************************
// Function Name: execCmd(struct CommandData*, int currentPos)
// Description: Function to execute commands that are not built in
//********************************************************
void execCmd(struct CommandData*, int currentPos);


int main(int argc, char *argv[])
{       
        struct CommandData Cmd_Data; 
	pid_t   pid1, pid2; 
	//character array initialized to the size of PATH_MAX+1, PATH_MAX is the
	//maximum length a path can be. From limits.h
	char currentDir[PATH_MAX + 1];
        //Character line that will be passed to the parser
	char* line; //Line to be parsed
	int tempBuiltIn;
	int tempFdIn = 1, tempFdOut = 0, fdIn = -1, fdOut = -1;
	int fd[2];
	fd[READ] = -1; //output
	fd[WRITE] = -1; //input
	int pipeNeeded = 0; //No pipe needed at first
	int loopcntr = 1;	

	//Not sure if this is correct
	setenv("DEBUG", "NO",1);

	//Loop forever
	while(loopcntr){
	  
		//Print shell prompt
		if (getcwd(currentDir, sizeof(currentDir)) != NULL){
       			fprintf(stdout, "%s>", currentDir);
   		}

		//Read in the line of commands
		line = read_line();

		//Parse the line
                memset(&Cmd_Data , 0, sizeof(Cmd_Data));
		ParseCommandLine(line, &Cmd_Data);

		tempBuiltIn = is_built_in(&Cmd_Data);
		
		//Was the command entered a built in command?
		if(tempBuiltIn != -1){
		  	executeBuiltInCommand(&Cmd_Data, tempBuiltIn, &loopcntr);
		}
		
		else{

			//Check if input file needs to be opened
			if(Cmd_Data.infile != NULL){

				char* temp = Cmd_Data.infile;
				
				fdIn = open(temp, O_RDONLY, 0); //Get FD for the file
				tempFdIn = dup(STDIN_FILENO);	
			}

			//Check if output file needs to be opened
			if(Cmd_Data.outfile != NULL){

				char* temp = Cmd_Data.outfile;
				mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; 

				fdOut = open(temp, O_WRONLY | O_CREAT | O_TRUNC, mode);
				tempFdOut = dup(STDOUT_FILENO);
			}

			//Is a pipe needed?
			if(Cmd_Data.numcommands > 1){
				pipe(fd);
				pipeNeeded = 1; //Set as true
			}

                        //Create a child process
			pid1 = fork();

			//Was there an error during the fork?
			if(pid1 == -1){
				fprintf(stderr,"ERROR WITH FORK\n");
			}

                        

			//Child process
			else if(pid1 == 0){

				if(pipeNeeded){

					//Fork again
					pid2 = fork();

					//Was there an error during the fork?
					if(pid2 == -1){
						fprintf(stderr,"ERROR WITH FORK\n");
					}
	
					//Child process
					else if(pid2 == 0){
						//Was an output file opened?
						if(fdOut != -1){
							dup2(fdOut, STDOUT_FILENO); //Make STDOUT point at fdIn
							close(fdOut);	//Not needed anymore
						}
						;
						close(fd[WRITE]);
						dup2(fd[READ], STDIN_FILENO);
						close(fd[READ]);
                                                execCmd(&Cmd_Data, 1);
					       	close(STDIN_FILENO);
					}

					//Parent process
					else{
						//Was an input file opened?
						if(fdIn != -1){
							dup2(fdIn, STDIN_FILENO); //Make STDIN point at fdIn
							close(fdIn);	//Not needed anymore
						}
						close(fd[READ]);
						dup2(fd[WRITE], STDOUT_FILENO);
						close(fd[WRITE]);
                                                execCmd(&Cmd_Data, 0);
             					close(STDOUT_FILENO);

					}
				}
	
				else{

					//Was an input file opened?
					if(fdIn != -1){
						dup2(fdIn, STDIN_FILENO); //Make STDIN point at fdIn
						close(fdIn);	//Not needed anymore
					}


					//Was an output file opened?
					if(fdOut != -1){
						dup2(fdOut, STDOUT_FILENO); //Make STDOUT point at fdOut
						close(fdOut);	//Not needed anymore
					}
					
					execCmd(&Cmd_Data, 0);
					
				}							

			}
	
			//Parent process
			else{
				//Command running in background?
				if(!Cmd_Data.background){
					for(int i = 0; i < 2; i++)
					  wait(NULL);	//Wait on the child process
				}

				//Close the fds in parent
				close(fdIn);
				close(fdOut);
                                close(fd[0]);
                                close(fd[1]);

				//Reset pipe variable
				pipeNeeded = 0;

				//Reset fd values
				fdIn = fdOut = fd[READ] = fd[WRITE] = -1;

				//Return STDIN and STDOUT to their proper fd's
				dup2(tempFdIn, STDIN_FILENO);
				dup2(tempFdOut, STDOUT_FILENO);

			}

		}
		
		//This can be uncommented to see the information about the commands given to the shell
		//print_info(&Cmd_Data);
		
	}

    exit(0);
}

char* read_line(){
	char c;
	int index = 0;
	char *buf = malloc(sizeof(char) * 200);

	while(1){
		//Get the next input character
		c = getchar();

		//Is it a newline character?
		if(c == '\n'){
			buf[index] = '\0'; //Null character to end string
			return buf;
		}

		  buf[index] = c;
	
		index += 1;
	}
}

void print_info(struct CommandData* cd){

	int commandCounter = 0;
	int argCounter = 0;
	
	fprintf(stdout, "\nNumber of simple commands: %i\n",cd->numcommands);

	//Loop through all commands
	while(commandCounter < cd->numcommands){
		//Print the command name
		fprintf(stdout, "Command %i: %s\n", commandCounter+1,cd->TheCommands[commandCounter].command);

		//Check if the command has any arguments
		if(cd->TheCommands[commandCounter].numargs){

			while(argCounter < cd->TheCommands[commandCounter].numargs){
				//Print arguments for the command
				fprintf(stdout, "Argument %i : %s\n",argCounter,cd->TheCommands[commandCounter].args[argCounter]);
				argCounter += 1;
			}
		}
	
	commandCounter += 1;
	argCounter = 0;
	}

	//Print input file
	if(cd->infile == NULL){
		fprintf(stdout, "Input File: NULL\n");
	}
		
	else{	fprintf(stdout, "Input File: %s\n", cd->infile); 	}

	//Print output file
	if(cd->outfile == NULL){
		fprintf(stdout, "Output File: NULL\n");
	}
	else{	fprintf(stdout, "Output File: %s\n", cd->outfile);	}
	
	//Print whether or not background execution is on
	if(cd->background){	
		fprintf(stdout, "Background Execution: ON\n");
	}
	
	else{	fprintf(stdout, "Background Execution: OFF\n");	}

	fprintf(stdout, "\n");
}

int is_built_in(const struct CommandData* cd){
	int commandCounter = 0;
	char* temp;
	
	while(commandCounter < cd->numcommands){
		temp = cd->TheCommands[commandCounter].command;

		
		if(!strcmp(temp, "cd")||!strcmp(temp, "exit")||!strcmp(temp, "set")||
		   !strcmp(temp, "pwd")||!strcmp(temp, "export"))
		{
			return commandCounter;
		}
	commandCounter += 1;
	}
return -1;
}

void executeBuiltInCommand(struct CommandData* cd, const int commandNum, int* loopc){
	char* temp;
	temp = cd->TheCommands[commandNum].command;
	
	//exit command
	if(!strcmp(temp, "exit")){ *loopc = 0;}

	//cd command
	if(!strcmp(temp, "cd")){
		//Were there arguments passed?
		if(cd->TheCommands[commandNum].numargs == 1){
			chdir(cd->TheCommands[commandNum].args[0]);
		}
		
		//Go back to home directory
		else{
			temp = getenv("HOME");
			if(temp != NULL){ chdir(temp); } //Change the directory

			else{ fprintf(stderr, "An error occurred..."); }
		}	
	}

	//pwd command
	if(!strcmp(temp, "pwd")){
		char currentDir[PATH_MAX + 1];
		if (getcwd(currentDir, sizeof(currentDir)) != NULL){
       			fprintf(stdout, "%s\n", currentDir);
   		}
	}
	
	//set command
	if(!strcmp(temp, "set")){
		 for (char **env = environ; *env; ++env)
        		fprintf(stdout, "%s\n", *env);
	}

	//export command
	if(!strcmp(temp, "export")){
		fprintf(stdout, "\nExport was not implemented...\n");
	}
}



void execCmd(struct CommandData* Cmd_Data, int cnt){
	int temp;
	//Make my own array of arguments passed
	char* tempArr[Cmd_Data->TheCommands[cnt].numargs + 2];
	tempArr[0] = Cmd_Data->TheCommands[0].command;		//First argument is the name of the program
 
	for(int i = 0; i < Cmd_Data->TheCommands[cnt].numargs; i++){
		tempArr[i+1] = Cmd_Data->TheCommands[cnt].args[i];
	}
	
	tempArr[Cmd_Data->TheCommands[cnt].numargs+1] = NULL;	//Array of arguments must end in NULL for execvp to work					
	temp = execvp(Cmd_Data->TheCommands[cnt].command, tempArr);

	if(temp < 0){
		printf("Command/File could not be found.\n");
		kill(getpid(), SIGUSR1);
	}
}
