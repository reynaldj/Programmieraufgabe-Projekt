#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "array.h"
#include "string.h"

#define PORT 9000
typedef struct {
	char key;
}newchar;

typedef struct {
	char * key;
}newstring;
// void* shellrough(void *param){
// 	int clientfd = *((int *)param);
// 	pthread_t my_tid = pthread_self();

// 	pthread_detach(my_tid);
// 	free(param);


// }

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
char *readinput()
{
	char *eingabeString;
		arrayInit(eingabeString);

		char ch;
		int counter = 0;
		//printf("done");
		while ((ch = getchar()) != 1  )
		{
			//printf("%d", ch);
			arrayPush(eingabeString) = ch;
			counter++;
			// printf("%c",ch);
		}
		if (counter <= 0)
			return NULL;
		// char auszufuehren[(int)arrayLen(eingabeString) + 1];
		// int arrayLength = (int)arrayLen(eingabeString);
		// printf("Arraylen:%d",(int)arrayLen(eingabeString));
		// for (int i=1;i <= arrayLength;i++){
		// newchar e = arrayPop(eingabeString);
		// auszufuehren[arrayLength-i] = e.key;
		// printf("%c",e.key);

		//}
		// printf("done");
		arrayPush(eingabeString) = '\0';
		// printf("%s\n",auszufuehren);
		//arrayRelease(eingabeString);
		return eingabeString;
}


void write_file(int clientfd, char * filename){
	int n;
	FILE *fp;
	

	//char buffer [1024];
	//bzero(buffer, 1024);
	
	fp = fopen(filename, "w");
	if(fp == -1){
		printf("Error creatig file");
		exit(-1);
	}
	// while(1){
	// 	n = recv(clientfd, buffer, 1024, 0);
	// 	if (n <= 0){
	// 		break;
	// 		return;
	// 	}
	// 	if(buffer[0] == 1)
	// 	return;
	// 	if(fprintf(fp, "%s", buffer)<0){
	// 		printf("cannot write to file");
	// 		exit(-1);
	// 	};
	// 	bzero(buffer, 1024);

		// char *buf;
		// arrayInit(buf);
		// char c[1];
		// do
		// {
		// 	/* code */
		// 	if(read(clientfd,c,sizeof(c))<0){
		// 	printf("Could not read socket");
		// 	exit(-1);
		// 	}
		// 	arrayPush(buf)= (char)c[0];
		// } while (arrayTop(buf)!= EOF);
		// //char * buffer = readinput();
		
	
	
	
//}

//char * buffer = readinput();
char *eingabeString;
		arrayInit(eingabeString);

		char ch;
		int counter = 0;
		//printf("done");
		while ((ch = getchar()) != 1  )
		{
			//printf("%d", ch);
			arrayPush(eingabeString) = ch;
			counter++;
			// printf("%c",ch);
		}
		if (counter <= 0)
			return NULL;
		// char auszufuehren[(int)arrayLen(eingabeString) + 1];
		// int arrayLength = (int)arrayLen(eingabeString);
		// printf("Arraylen:%d",(int)arrayLen(eingabeString));
		// for (int i=1;i <= arrayLength;i++){
		// newchar e = arrayPop(eingabeString);
		// auszufuehren[arrayLength-i] = e.key;
		// printf("%c",e.key);

		//}
		// printf("done");
		arrayPop(eingabeString);
		arrayPush(eingabeString) = '\0';
		// printf("%s\n",auszufuehren);
		//arrayRelease(eingabeString);
		//return eingabeString;
// if(write(fp,eingabeString, arrayLen(eingabeString))<0){
// 	printf("write to file fail");
// 	exit(-1);
// };
	if(fprintf(fp, "%s", eingabeString)<0){
			printf("cannot write to file");
			exit(-1);
		};

close(fp);

return;
}

void send_file(FILE * fp){
	fseek(fp,0,SEEK_END);
	long fsize = ftell(fp);
	fseek(fp,0,SEEK_SET);

	char *string = malloc(fsize+1);
	fread(string,fsize,1,fp);
	fclose(fp);
	string[fsize] = 1;
	printf("%s",string);
}

char* changeDirectory(char* path, char* currentShellPath){
	if (chdir(path) !=0){
		if (strcmp(path,"-") == 0 || strcmp(path,"..") == 0 ){
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

}

void shell(int clientfd,char* cliIPAdress, int port){
	dup2(clientfd,0);
	dup2(clientfd,1);
	//close(clientfd);
	char* currentShellPath;
	arrayInit(currentShellPath);
	arrayPush(currentShellPath) = '.';
	arrayPush(currentShellPath) = '/';
	arrayPush(currentShellPath) = '>';

	while(1){
		// printf("%s", currentShellPath);
		
		// printf("auszufuehren");
		// for (int i = 0; i <arrayLength; i++)
		// {
		// 	/* code */
		// 	printf("%c",auszufuehren[i]);
		// }
		////////////////////////////////////////
		fflush(stdout);
		newchar * eingabeString;
		arrayInit(eingabeString);

		char ch;
		int counter = 0;
		while((ch = getchar()) != 0){
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
		
		// char auszufuehren [1024];
		// if(read(clientfd,auszufuehren,1024)<0){
		// 	printf("Cannot read from socket");
		// 	close(clientfd);
		// 	exit(-1);
		// }
		//printf("%s\n",auszufuehren);

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
		
		
		
		// if(strcmp(params[parameterLength-1],"&") == 0){
		// 	char * newparams[parameterLength];
		// 	for (int i = 0; i < parameterLength-1; i++)
		// 	{
		// 		/* code */
		// 		newparams[i] = malloc(strlen(params[i]));
		// 		strcpy(newparams[i], params[i]);
				

		// 	}
		// 	newparams[parameterLength-1] = NULL;
		// 	//freeArray(params,parameterLength+1);
		// 	execArgsAnd(newparams,parameterLength);
			
		// }else if(strcmp(params[0], "cd") == 0){
		// 	//printf("params1:%s\n",params[1]);
		// 	currentShellPath = changeDirectory(params[1], currentShellPath);
			

		// }else if(strcmp(params[0], "exit") == 0){

		// 	exit(0);

		// }else if(strcmp(params[0], "wait") == 0){

		// 	int pid = atoi(params[1]);
		// 	//printf("%i", pid);
		// 	intern_wait(pid);
		// 	signal(SIGINT, SIG_DFL);

		//}else{			
//		signal(SIGINT, SIG_IGN);
		//execArgsWithWait(params,parameterLength+1);
		if(strcmp(params[0], "cd") == 0){
		currentShellPath = changeDirectory(params[1], currentShellPath);
		}else if(strcmp(params[0],"exit")== 0){
		printf("Connection closed %s:%d",cliIPAdress,port);
		close(clientfd);
		exit(0);
		}else if(strcmp(params[0], "put") == 0){
		write_file(clientfd,params[1]);
		}else if(strcmp(params[0],"get")== 0){
		FILE * fp;
			char * filename = params[1];
			fp = fopen(filename, "r");
			if(fp == NULL){
				printf("Error reading file.");
				exit(-1);
			}
			send_file(fp);
		}
		else{
		execProg(params);
		}
		printf("%c",EOF);
		fflush(stdout);
//		}
		
	}
}
int main() {
	
	int serverfd, clientfd,ret; 
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;

	socklen_t addr_size;
	
	pid_t childpid;

	serverfd = socket(AF_INET, SOCK_STREAM, 0);

	if(serverfd < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);

	ret = bind(serverfd,
		(struct sockaddr*)&serverAddr,
		sizeof(serverAddr));
	
	if(ret < 0){
		printf("Error in binding.\n");
		exit(1);
	}

	if(listen(serverfd,50) == 0)
		printf("Listening\n");
	else
	printf("Error\n");
	pthread_t tid[60];

	int i = 0;


	while (1) {
		printf("[srv]: idle\n");
		sleep(2);
		while(1){
		addr_size = sizeof(clientAddr);
		clientfd = accept(serverfd, (struct sockaddr*)&clientAddr, &addr_size);
		//pthread_create(&tid[i++],NULL,shell, &clientfd);
		if (clientfd < 0){
			exit(1);
		}

		printf("Connection accepted from %s:%d\n",
				inet_ntoa(clientAddr.sin_addr),
				ntohs(clientAddr.sin_port));
		printf("Clients connected: %d\n\n", ++i);

		if((childpid = fork()) == 0){
			close(serverfd);
			shell(clientfd,inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));

		}
		}

		
		
		

	}
	
	return 0;
}
