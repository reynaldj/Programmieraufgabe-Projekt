#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "array.h"

typedef struct {
	char key;
}newchar;

typedef struct {
	char * key;
}newstring;

int checkpipe (char ** array, int arraylen){
	
		signed int index_pipe = -1;
		for (int i = 0; i < arraylen-1; i++)
		{
			/* code */
			 if(strcmp(array[i],"|")== 0){
				
			 	index_pipe = i;
			 }
		}
		//printf("Index:%d",index_pipe);
	return index_pipe;
}

void execAnd(char ** parsed){
	//TODO
	  int pipefd[2];
	  pipe(pipefd);
	  char buf[512];
	  int saved_stdout = dup(1);
	pid_t pid = fork(); 
	char * dir = malloc(strlen(parsed[0]));
	strcpy(dir,parsed[0]);
	int withp = 1;
	if (parsed[0][0] == '.' && parsed[0][1] == '/'){
		char * token = strtok(parsed[0],"/");
		token = strtok(NULL,"\0");
		parsed[0] = realloc(parsed[0],strlen(token));
		strcpy(parsed[0],token);
		withp = 0;
	}

	
	
    if (pid == -1) {
        printf("\nFailed forking child..");
        exit(-1);
    } else if (pid == 0) {
        // printf("Hello");
		close(pipefd[0]);

		
		  dup2(pipefd[1],1);
		  close(pipefd[1]);
		  char * buf  = {"1\0"};
		  write(1,buf,strlen(buf));
		  dup2(saved_stdout,1);
		  close(saved_stdout);
		  int pipefd2[2];
	 	pipe(pipefd2);
		if (withp == 1){
			if (execvp(dir, parsed)< 0) {
			// printf("\33[2K\r");
			// printf("DEleted");
            //printf("\nCould not execute command..");
			//fflush(stdout);
			printf("\nCould not execute command..\n\r");
			dup2(pipefd2[1],1);
		  close(pipefd2[1]);
			char * buf  = {"2\0"};
		  write(1,buf,strlen(buf));
		  close(pipefd2[0]);
		   exit(-1);
        }
		}else{
		if (execv(dir, parsed)< 0) {
			// printf("\33[2K\r");
			// printf("DEleted");
            //printf("\nCould not execute command..");
			//fflush(stdout);
			printf("\nCould not execute command..\n\r");
			dup2(pipefd2[1],1);
		  close(pipefd2[1]);
			char * buf  = {"2\0"};
		  write(1,buf,strlen(buf));
		  close(pipefd2[0]);
		   exit(-1);
        }	
		}
		
		  
       
    } else {
		
		 read(pipefd[0],buf,512);
		 //printf("Buf:%s",buf);
		 close(pipefd[0]);
		 close(pipefd[1]);
		 //printf("%s",buf);
		 if ( strcmp(buf,"1") != 0)
		 {
		// 	/* code */
		
		
		 	return;
		 }else {
			 printf("[%d]",pid);
			return;
		
		 }
			
		

		
		
        
        
    }
}

void execProg(char ** parsed) {
	pid_t pid = fork(); 
	//int status = 0;
	int status;
	char * dir = malloc(strlen(parsed[0]));
	strcpy(dir,parsed[0]);
	int withp= 1;
	if (parsed[0][0] == '.' && parsed[0][1] == '/'){
		char * token = strtok(parsed[0],"/");
		token = strtok(NULL,"\0");
		parsed[0] = realloc(parsed[0],strlen(token));
		strcpy(parsed[0],token);
		withp=0;
}
	
	
    if (pid == -1) {
        printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        if(withp==1){
		if (execvp(dir, parsed) < 0) {
            printf("\nCould not execute command..");
        }
		}else{
		if (execv(dir, parsed) < 0) {
            printf("\nCould not execute command..");
        }
		}
        exit(0);
    } else {
        // waiting for child to terminate
        //while((wpid = wait(&status))>0);
		waitpid(pid,&status,0);
        return;
    }
}

void execPipe(char ** firstProg,char ** secondProg){
	// for (int i = 0; i < 3; i++)
	// {
	// 	/* code */
	// 	printf("SEcProg:%s",secondProg[i]);
	// }
	//char buf[512];
	int pipefd[2];
	//int status = 0;
	int status1,status2;
	//int status1;
	pid_t pid1,pid2;
	pipe(pipefd);
	pid1 = fork();

	if(pid1 < 0){
		 printf("\nFailed forking child..");
        exit(-1);
	}else if(pid1 == 0){
		int withp = 1;
		char * dir = malloc(strlen(firstProg[0]));
	strcpy(dir,firstProg[0]);
	if (firstProg[0][0] == '.' && firstProg[0][1] == '/'){
		char * token = strtok(firstProg[0],"/");
		token = strtok(NULL,"\0");
		firstProg[0] = realloc(firstProg[0],strlen(token));
		strcpy(firstProg[0],token);
		withp=0;
}
		// printf("Dir:%s",dir);
		// for (int i = 0; i < 3; i++)
		// {
		// 	/* code */
		// 	printf("FirstPRog:%s",firstProg[i]);
		// }
		
		close(pipefd[0]);
		dup2(pipefd[1],1);
		close(pipefd[1]);
		if(withp==1){
		if(execvp(dir,firstProg)<0){
			//printf("withp");
			printf("Fehler");
			exit(-1);
		};
		}else{
			if(execv(dir,firstProg)<0){
			//printf("withoutp");
			printf("Fehler");
			exit(-1);
		};
		}
	}else {
		
		pid2 = fork();
		if(pid2 <0){
			printf("Error");
		}else if(pid2 == 0){
		//read(pipefd[0],buf,512);
		//printf("Buf:%s",buf);
		//waitpid(pid1,&status1,0);
		//wait(NULL);
		write(pipefd[0],(char*)-1,1);
		int withp = 1;
		char * dir = malloc(strlen(secondProg[0]));
		strcpy(dir,secondProg[0]);
		if (secondProg[0][0] == '.' && secondProg[0][1] == '/'){
		char * token = strtok(secondProg[0],"/");
		token = strtok(NULL,"\0");
		secondProg[0] = realloc(secondProg[0],strlen(token));
		strcpy(secondProg[0],token);
		withp =0;
}
		close(pipefd[1]);
		dup2(pipefd[0],0);
		close(pipefd[0]);
		//printf("INdex2:%s\n",secondProg[1]);
		if(withp==1){
		if(execvp(dir,secondProg)<0){
			//printf("withp");
			printf("Pipe funktioniert nicht");
			exit(-1);
		}
		}else{
			if(execv(dir,secondProg)<0){
			printf("withoutp");
			printf("Pipe funktioniert nicht");
			exit(0);
		};
		}
		}else{
			close(pipefd[0]);
			close(pipefd[1]);
			 waitpid(pid1,&status1,0);
			 waitpid(pid2,&status2,0);
			//while((wpid = wait(&status))>0);
			//printf("FIrst DOne");
			//wait(NULL);
			//printf("SEcond DOne");
			
			return;
		}
		
	}
}

void execAndPipe(char ** firstProg,char ** secondProg){
// for (int i = 0; i < 3; i++)
	// {
	// 	/* code */
	// 	printf("SEcProg:%s",secondProg[i]);
	// }
	//char buf[512];
	int pipefd[2];
	int pipeasynfd[2];
	pipe(pipeasynfd);
	char buf[512];
	int saved_stdout = dup(1);
	//int status = 0;
	int status1,status2;
	//int status1;
	pid_t pid1,pid2;
	pipe(pipefd);
	pid1 = fork();

	if(pid1 < 0){
		 printf("\nFailed forking child..");
        exit(-1);
	}else if(pid1 == 0){
		int withp = 1;
		char * dir = malloc(strlen(firstProg[0]));
	strcpy(dir,firstProg[0]);
	if (firstProg[0][0] == '.' && firstProg[0][1] == '/'){
		char * token = strtok(firstProg[0],"/");
		token = strtok(NULL,"\0");
		firstProg[0] = realloc(firstProg[0],strlen(token));
		strcpy(firstProg[0],token);
		withp=0;
}
		// printf("Dir:%s",dir);
		// for (int i = 0; i < 3; i++)
		// {
		// 	/* code */
		// 	printf("FirstPRog:%s",firstProg[i]);
		// }
		close(pipeasynfd[0]);
		dup2(pipeasynfd[1],1);
		close(pipeasynfd[1]);
		char * buf = {"1\0"};
		write(1,buf,strlen(buf));
		//printf("prog1");
		dup2(saved_stdout , 1);
		close(saved_stdout);
		int pipeasynfd2[2];
		pipe(pipeasynfd2);

		close(pipefd[0]);
		dup2(pipefd[1],1);
		close(pipefd[1]);
		if(withp==1){
		if(execvp(dir,firstProg)<0){
			//printf("withp");
			dup2(pipeasynfd2[1],1);
			close(pipeasynfd2[1]);
			char * buf = {"-1\0"};
			write(1,buf,strlen(buf));
			close(pipeasynfd2[0]);
			printf("Fehler");
			exit(-1);
		};
		}else{
			if(execv(dir,firstProg)<0){
			//printf("withoutp");
			dup2(pipeasynfd2[1],1);
			close(pipeasynfd2[1]);
			char * buf = {"-1\0"};
			write(1,buf,strlen(buf));
			close(pipeasynfd2[0]);
			printf("Fehler");
			exit(-1);
		};
		}
	}else {
		read(pipeasynfd[0],buf,512);
		close(pipeasynfd[0]);
		close(pipeasynfd[1]);
		//printf("BUf%s",buf);
		if(strcmp(buf,"1") == 0){
			printf("\nCould not execute command.. \n\r");
			return;
		}else{
			printf("[%d]",pid1);
		}
		int pipeasynfd2[2];
		pipe(pipeasynfd2);
		char bufsecond[512];
		int saved_stdoutsecond = dup(1);
		pid2 = fork();
		if(pid2 <0){
			printf("Error");
		}else if(pid2 == 0){
		//read(pipefd[0],buf,512);
		//printf("Buf:%s",buf);
		//waitpid(pid1,&status1,0);
		//wait(NULL);
		waitpid(pid1,&status1,0);
		close(pipeasynfd2[0]);
		dup2(pipeasynfd2[1],1);
		close(pipeasynfd2[1]);
		char * bufsecond = {"1\0"};
		
		write(1,bufsecond,strlen(bufsecond));
		printf("prog2");
		dup2(saved_stdoutsecond,1);
		close(saved_stdoutsecond);
		int pipeasynfd3[2];
		pipe(pipeasynfd3);

		write(pipefd[0],(char*)-1,1);
		int withp = 1;
		char * dir = malloc(strlen(secondProg[0]));
		strcpy(dir,secondProg[0]);
		if (secondProg[0][0] == '.' && secondProg[0][1] == '/'){
		char * token = strtok(secondProg[0],"/");
		token = strtok(NULL,"\0");
		secondProg[0] = realloc(secondProg[0],strlen(token));
		strcpy(secondProg[0],token);
		withp =0;
}
		close(pipefd[1]);
		dup2(pipefd[0],0);
		close(pipefd[0]);
		//printf("INdex2:%s\n",secondProg[1]);
		if(withp==1){
		if(execvp(dir,secondProg)<0){
			//printf("withp");
			dup2(pipeasynfd3[1],1);
			close(pipeasynfd3[1]);
			char * buf = {"-1\0"};
			write(1,buf,strlen(buf));
			close(pipeasynfd3[0]);
			printf("Pipe funktioniert nicht");
			exit(-1);
		}
		}else{
			if(execv(dir,secondProg)<0){
			dup2(pipeasynfd3[1],1);
			close(pipeasynfd3[1]);
			char * buf = {"-1\0"};
			write(1,buf,strlen(buf));
			close(pipeasynfd3[0]);
			printf("withoutp");
			printf("Pipe funktioniert nicht");
			exit(0);
		};
		}
		}else{
			
			read(pipeasynfd2[0],bufsecond,512);
			close(pipeasynfd2[0]);
			close(pipeasynfd2[1]);
			
			if(strcmp(bufsecond,"1") != 0){
				close(pipefd[0]);
			close(pipefd[1]);
				printf("\nCould not execute command..\n\r");
				return;
			}else{
				close(pipefd[0]);
			close(pipefd[1]);
				printf("[%d]",pid2);
				return;
			}

			
			//  waitpid(pid1,&status1,0);
			//  waitpid(pid2,&status2,0);
			//while((wpid = wait(&status))>0);
			//printf("FIrst DOne");
			//wait(NULL);
			//printf("SEcond DOne");
			
			return;
		}
		
	}
}

void execArgsWithWait(char ** parsed,int parsed_len){
		
		signed int index_pipe =checkpipe(parsed,parsed_len); 
		//printf("Index:%d",index_pipe);
		if(index_pipe >= 0){
		int firstprog_len = index_pipe + 1;
		int secondprog_len = parsed_len-(index_pipe+1);
		char * firstprog[firstprog_len];
		char * secondprog[secondprog_len];
		for (int i = 0; i < firstprog_len-1; i++)
			{
				/* code */
				firstprog[i] = malloc(strlen(parsed[i]));
				strcpy(firstprog[i], parsed[i]);
				

			}
		firstprog[firstprog_len-1] = NULL;
		for (int i = 0; i < secondprog_len-1; i++)
			{
				/* code */
				secondprog[i] = malloc(strlen(parsed[index_pipe+1+i]));
				strcpy(secondprog[i], parsed[index_pipe+1+i]);
				

			}
		secondprog[secondprog_len-1] = NULL;
		execPipe(firstprog,secondprog);
		}else{
			execProg(parsed);
		}
	
	}

void execArgsAnd(char ** parsed,int parsed_len){
	signed int index_pipe =checkpipe(parsed,parsed_len); 
		//printf("Index:%d",index_pipe);
		if(index_pipe >= 0){
		int firstprog_len = index_pipe + 1;
		int secondprog_len = parsed_len-(index_pipe+1);
		char * firstprog[firstprog_len];
		char * secondprog[secondprog_len];
		for (int i = 0; i < firstprog_len-1; i++)
			{
				/* code */
				firstprog[i] = malloc(strlen(parsed[i]));
				strcpy(firstprog[i], parsed[i]);
				

			}
		firstprog[firstprog_len-1] = NULL;
		for (int i = 0; i < secondprog_len-1; i++)
			{
				/* code */
				secondprog[i] = malloc(strlen(parsed[index_pipe+1+i]));
				strcpy(secondprog[i], parsed[index_pipe+1+i]);
				

			}
		secondprog[secondprog_len-1] = NULL;
		execAndPipe(firstprog,secondprog);
		}else{
			execAnd(parsed);
		}

}

void freeArray(char **a, int m) {
    int i;
    for (i = 0; i < m; ++i) {
        free(a[i]);
    }
    free(a);
}

char* changeDirectory(char* path, char* currentShellPath){
	if (chdir(path) !=0){
		if (strcmp(path,"-") == 0){
		// char *prev;
		// prev = getcwd(prev, 0);
		// printf("PRev:%s",prev);
		// chdir(prev);
		// free(prev);
		char  tmp1,tmp2;
		tmp1 = arrayPop(currentShellPath);
		tmp2 = arrayPop(currentShellPath);
		//printf("CurrentShellPath:%s\n",currentShellPath);
		char tmp3 = 0;
		while(!arrayIsEmpty(currentShellPath)){
			//printf("CurrentShellPath:%s\n",currentShellPath);

			tmp3=arrayPop(currentShellPath);
			arrayPush(currentShellPath)='\0';
			arrayPop(currentShellPath);
			
			if(tmp3!='/'){
			//printf("%c\n",tmp3);
			continue;
			}else{
				//printf("Weiter");
				//statt goto, kannste auch breaken
				goto weiter;
			}
			
		}
		weiter:;
		// if(tmp3=='/'){
		// arrayPush(currentShellPath)=tmp3;
		// }
		
		// char * move_to;
		// arrayInit(move_to);
		
		// //arrayPush(move_to) = '/';
		// for (int i = 0; i < arrayLen(currentShellPath); i++)
		// {
		// 	/* code */
		// 	arrayPush(move_to) = currentShellPath[i];
		// }
		// printf("move%s",move_to);
		chdir("..");
		if(arrayIsEmpty(currentShellPath)){
			arrayPush(currentShellPath) = '.';
		}
		arrayPush(currentShellPath)=tmp2;
		
		
		arrayPush(currentShellPath)=tmp1;
		//printf("Path:%s",currentShellPath);
		
		return currentShellPath;
	}
		
		printf("Could not change Directory \n");
		return currentShellPath;
	}

	

	//kriege hier ne Warnung das arrayPop nicht benutzt wird .. will ich ja auch nicht xd
	//deswegen der spaß mit tmp, werde ich mir noch was einfallen lassen 
	//oder halt in makefile warnings ignorieren
	char tmp;
	if(strcmp(currentShellPath, "./>") == 0){

		tmp = arrayPop(currentShellPath);
		tmp = arrayPop(currentShellPath);
		tmp = arrayPop(currentShellPath);
		//printf("CurrentShellPath:%s\n",currentShellPath);
		arrayPush(currentShellPath) = tmp;
		tmp = arrayPop(currentShellPath);

		while (*path != '\0'){
			
			arrayPush(currentShellPath) = *path;
			path++;
			//printf("CurrentShellPath:%s\n",currentShellPath);
		}
		arrayPush(currentShellPath) = '/';
		arrayPush(currentShellPath) = '>';
		
		/*arraystrcat(path, ">");
		currentShellPath = path;*/
	}else{
		tmp = arrayPop(currentShellPath);
		
		arrayPush(currentShellPath) = tmp;
		tmp = arrayPop(currentShellPath);
		

		while (*path != '\0'){
			//printf("CurrentShellPath:%s\n",currentShellPath);
			arrayPush(currentShellPath) = *path;
			path++;
		}
		arrayPush(currentShellPath) = '/';
		arrayPush(currentShellPath) = '>';

	}
	//printf("CurrentShellPath:%s\n",currentShellPath);
	return currentShellPath;
}


void intern_wait(pid_t pid){
	int status;
	signal(SIGINT, SIG_IGN);
	pid_t own_pid = getpid();
	if (own_pid == pid){
		signal(SIGINT, SIG_IGN);
	}else{
	//signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, WUNTRACED); // WNOHANG
	if (WIFEXITED(status) != 0){
		printf("[%d] terminated\n", pid);
	}else{
		printf("Interrupted!");
	}
	if(WEXITSTATUS(status) != 0){
		printf("[EXITSTATUS] %i\n", WEXITSTATUS(status));
		}
	}
}



int main(void) {

	char* currentShellPath;
	arrayInit(currentShellPath);
	arrayPush(currentShellPath) = '.';
	arrayPush(currentShellPath) = '/';
	arrayPush(currentShellPath) = '>';

	while(1){
		printf("%s", currentShellPath);
		
		//printf("auszufuehren");
		//for (int i = 0; i <arrayLength; i++)
		//{
			/* code */
		//	printf("%c",auszufuehren[i]);
		//}
		//////////////////////////////////////////
		newchar * eingabeString;
		arrayInit(eingabeString);

		char ch;
		int counter = 0;
		while((ch = getchar()) != 10){
		//printf("%d",ch);
		arrayPush(eingabeString) = (newchar){.key = ch};
		counter++;
		}
		if (counter <= 0)
		continue;
		char auszufuehren[(int)arrayLen(eingabeString) + 1];
		int arrayLength = (int)arrayLen(eingabeString);
		//printf("Arraylen:%d",(int)arrayLen(eingabeString));
		for (int i=1;i <= arrayLength;i++){
		newchar e = arrayPop(eingabeString);
		auszufuehren[arrayLength-i] = e.key;
		//printf("%c",e.key);
		
		}
		auszufuehren[arrayLength] = '\0';
		//printf("%s\n",auszufuehren);
		arrayRelease(eingabeString);
		/////////////////////////////// auszufuehren ist ein String von der Eingabe z.B "ls"
		
		char * token;
		newstring * arguments;

		//char * auszufuehren_copy = malloc(strlen(auszufuehren));
		//strcpy(auszufuehren_copy,auszufuehren);
		arrayInit(arguments);
		token = strtok(auszufuehren," ");
		while(token != NULL){
		//printf("%s\n",token);
		arrayPush(arguments) = (newstring){.key = token  };
		token = strtok(NULL," ");
		}
		int parameterLength = (int)arrayLen(arguments);
		
		char * params[parameterLength+1];

		for (int i = 1; i <= parameterLength; i++)
		{
			/* code */
			newstring str = arrayPop(arguments);
			params[parameterLength-i] = malloc(strlen(str.key));
			strcpy(params[parameterLength-i],str.key);
		}
		params[parameterLength] = NULL;
		arrayRelease(arguments);
		
		// printf("Parameters:\n");
		// for (int i = 0; i < parameterLength; i++)
		// {
		// 	/* code */
		// 	printf("%s\n",params[i]);
		// }
		
		
		
		if(strcmp(params[parameterLength-1],"&") == 0){
			char * newparams[parameterLength];
			for (int i = 0; i < parameterLength-1; i++)
			{
				/* code */
				newparams[i] = malloc(strlen(params[i]));
				strcpy(newparams[i], params[i]);
				

			}
			newparams[parameterLength-1] = NULL;
			//freeArray(params,parameterLength+1);
			execArgsAnd(newparams,parameterLength);
			
		}else if(strcmp(params[0], "cd") == 0){
			//printf("params1:%s\n",params[1]);
			currentShellPath = changeDirectory(params[1], currentShellPath);
			

		}else if(strcmp(params[0], "exit") == 0){

			exit(0);

		}else if(strcmp(params[0], "wait") == 0){

			int pid = atoi(params[1]);
			//printf("%i", pid);
			intern_wait(pid);
			signal(SIGINT, SIG_DFL);

		}else{			
		signal(SIGINT, SIG_IGN);
		execArgsWithWait(params,parameterLength+1);

		}
		
			
		



		//printf("LEngth:%d",parameterLength);

		//for (int i = 0; i < parameterLength; i++)
		//{
		//	/* code */
		//	printf("Parameters: %s\n",arrayPop(arguments).key);
		//	
		//}
		
		
		
		//char * token = strtok(auszufuehren," ");
		//printf("%s\n",token);
		




	}
	
	return 0;
}
