/*
 * Headstart for Assignment 2
 * CS 4420/5420
 * 
 *
 * Student Name:  
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
int isEnvAssignment = 0;
char* read_line();
void print_info(struct CommandData*);
int is_built_in(struct CommandData*);
void executeBuiltInCommand(struct CommandData*, const int commandNum, int*, char*, char*);
void execCmd(struct CommandData*, int currentPos);

int main(int argc, char *argv[])
{       
        struct CommandData* Cmd_Data = malloc(sizeof(*Cmd_Data)); 
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
	  //character arrays to store both the environment variable name and value
	        char* envName[256];
		char* envVal[256];
		//initializing them
		for(int i = 0; i <= 256; i++){
		  if(i == 256){
		    envName[i-1] = '\0';
		    envVal[i-1] = '\0';
		  }
		  else{
		   envName[i] = ".";
		   envVal[i] = ".";
		  }
		}
		//Print shell prompt
		if (getcwd(currentDir, sizeof(currentDir)) != NULL){
       			fprintf(stdout, "%s>", currentDir);
   		}

		//Read in the line of commands
		line = read_line();

		//Parse the line
                memset(Cmd_Data , 0, sizeof(*Cmd_Data));
		ParseCommandLine(line, Cmd_Data);

		tempBuiltIn = is_built_in(Cmd_Data);

		//Was the command entered a built in command?
		if(tempBuiltIn != -1){
		  //if the input string had an assignment operation, extract the name
		  //and value from the input string and store them in envName, envVal.
		 
		  if(isEnvAssignment == 1){
		  int cntr = 0; 
		  int j = 0;
		  while(j < sizeof(*line)){
		    if(line[j] == ' ')
		      break;
		    j++;
		      }
                  for(int i = j; i < sizeof(*line); i++){
		    if(line[i] == '\0')
		      envVal[i] = '\0';
		    else if(line[i] == '='){
		      envName[i] = '\0';
		      cntr = i;
		    }
		    else if(i > cntr)
		      envVal[i] = &line[i];
		    else
		      envName[i] = &line[i];
		  }
		  
		  isEnvAssignment = 0;
		  fprintf(stdout, "Command: %s\n", envVal[0]);
		  setenv(*envName, *envVal, 0);
		  
		  }
		  //execute the built in command. envName, and envVal are passed in to
		  //allow export to execute. 
		  executeBuiltInCommand(Cmd_Data, tempBuiltIn, &loopcntr, *envName, *envVal);
		}
		
		else{

			//Check if input file needs to be opened
			if(Cmd_Data->infile != NULL){

				char* temp = Cmd_Data->infile;
				
				fdIn = open(temp, O_RDONLY, 0); //Get FD for the file
				tempFdIn = dup(STDIN_FILENO);	
			}

			//Check if output file needs to be opened
			if(Cmd_Data->outfile != NULL){

				char* temp = Cmd_Data->outfile;
				mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; 

				fdOut = open(temp, O_WRONLY | O_CREAT | O_TRUNC, mode);
				tempFdOut = dup(STDOUT_FILENO);
			}

			//Is a pipe needed?
			if(Cmd_Data->numcommands > 1){
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
                                                execCmd(Cmd_Data, 1);
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
                                                execCmd(Cmd_Data, 0);
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
					
					execCmd(Cmd_Data, 0);
					
				}							

			}
	
			//Parent process
			else{
				//Command running in background?
				if(!Cmd_Data->background){
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
		//char* aux = getenv("DEBUG");
		//if(*aux == "NO")
		print_info(Cmd_Data);
		
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

		else{
		  if(c == '=')
		    isEnvAssignment = 1;

		  buf[index] = c;
		}
	
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

int is_built_in(struct CommandData* cd){
	int commandCounter = 0;
	char* temp;

	while(commandCounter < cd->numcommands){
		temp = cd->TheCommands[commandCounter].command;
		
		if(!strcmp(temp, "cd")||!strcmp(temp, "exit")||!strcmp(temp, "set")||
		   !strcmp(temp, "jobs")||!strcmp(temp, "kill")||!strcmp(temp, "fg")||
	           !strcmp(temp, "bg")||!strcmp(temp, "pwd")||!strcmp(temp, "export"))
		{
			return commandCounter;
		}
	commandCounter += 1;
	}
return -1;
}

void executeBuiltInCommand(struct CommandData* cd, const int commandNum, int* loopc, char* envName, char* envVal){
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
		//Where there arguments passed?
	  if(cd->TheCommands[commandNum].numargs){
	    setenv(envName, envVal, 1);
	  }
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
//exit(0);

if(temp < 0){
 printf("%s\n", strerror(errno));
 kill(getpid(), SIGUSR1);
 }
}
