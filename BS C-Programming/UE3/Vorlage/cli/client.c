#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "array.h"
#include <string.h>

#define PORT 9000
#define HOST "127.0.0.1"
typedef struct
{
	char key;
} newchar;

typedef struct
{
	char *key;
} newstring;

char *readinput()
{
	char *eingabeString;
		arrayInit(eingabeString);

		char ch;
		int counter = 0;
		//printf("done");
		while ((ch = getchar()) != 10 )
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

char *readinputeof()
{
	char *eingabeString;
		arrayInit(eingabeString);

		char ch;
		int counter = 0;
		//printf("done");
		while ((ch = getchar()) != EOF)
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

char ** getparams(char * auszufuehren){
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
		return &params;
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

		char *buf;
		arrayInit(buf);
		char c[1];
		do
		{
			/* code */
			if(read(clientfd,c,sizeof(c))<0){
			printf("Could not read socket");
			exit(-1);
			}
			arrayPush(buf)= (char)c[0];
		} while (arrayTop(buf)!= 1);
		// //char * buffer = readinput();
		arrayPop(buf);
	
	
	
//}

//char * buffer = readinput();
// char *eingabeString;
// 		arrayInit(eingabeString);

// 		char ch;
// 		int counter = 0;
// 		//printf("done");
// 		while ((ch = getchar()) != 1  )
// 		{
// 			//printf("%d", ch);
// 			arrayPush(eingabeString) = ch;
// 			counter++;
// 			// printf("%c",ch);
// 		}
// 		if (counter <= 0)
// 			return NULL;
// 		// char auszufuehren[(int)arrayLen(eingabeString) + 1];
// 		// int arrayLength = (int)arrayLen(eingabeString);
// 		// printf("Arraylen:%d",(int)arrayLen(eingabeString));
// 		// for (int i=1;i <= arrayLength;i++){
// 		// newchar e = arrayPop(eingabeString);
// 		// auszufuehren[arrayLength-i] = e.key;
// 		// printf("%c",e.key);

// 		//}
// 		// printf("done");
// 		arrayPop(eingabeString);
// 		arrayPush(eingabeString) = '\0';
// 		// printf("%s\n",auszufuehren);
// 		//arrayRelease(eingabeString);
// 		//return eingabeString;
// // if(write(fp,eingabeString, arrayLen(eingabeString))<0){
// // 	printf("write to file fail");
// // 	exit(-1);
// // };
	if(fprintf(fp, "%s", buf)<0){
			printf("cannot write to file");
			exit(-1);
		};

close(fp);

return;
}

void send_file(FILE *fp, int sockfd){
	int n;
	// char data[1024] = {0};

	// while(fgets(data, 1024, fp) != NULL){

	// 	if(send(sockfd, data, sizeof(data),0)== -1){
	// 		printf("Cannot send data");
	// 		exit(-1);
	// 	}
	// 	bzero(data, 1024);
	// }
	// char eof[1] = {1};
	// if(send(sockfd,eof,1,0)== -1){
	// 	printf("Cannot send data");
	// 		exit(-1);
	// };
	//fclose(fp);
	fseek(fp,0,SEEK_END);
	long fsize = ftell(fp);
	fseek(fp,0,SEEK_SET);

	char *string = malloc(fsize+1);
	fread(string,fsize,1,fp);
	fclose(fp);
	string[fsize] = 1;
	if(write(sockfd,string,fsize+1)<0){
		printf("Cannot send file");
	 	exit(-1);
	 }
	//write(sockfd, EOF, 1);
	// char * buffer;
	// arrayInit(buffer);
	// char ch;
	// do{
	// 	ch = fgetc(fp);
	// 	arrayPush(buffer) = ch;

	// }while(ch != EOF);

	// if(write(sockfd,buffer,arrayLen(buffer)< 0)){
	// 	printf("Cannot send file");
	// 	exit(-1);
	// }
	
	// 	if(send(sockfd, string, sizeof(string),0)== -1){
	// 		printf("Cannot send data");
	//  		exit(-1);
	//  	}
	

}
int main()
{
	int clientfd, ret;

	struct sockaddr_in cliAddr;

	clientfd = socket(AF_INET, SOCK_STREAM, 0);

	if (clientfd < 0)
	{
		printf("Error in conncection.\n");
		exit(1);
	}

	printf("Client socket created.\n");
	
	memset(&cliAddr, '\0', sizeof(cliAddr));

	cliAddr.sin_family = AF_INET;
	cliAddr.sin_port = htons(PORT);
	cliAddr.sin_addr.s_addr = inet_addr(HOST);

	ret = connect(clientfd, (struct sockaddr *)&cliAddr, sizeof(cliAddr));

	if (ret < 0)
	{
		printf("Error in connection.\n");
		exit(1);
	}

	printf("Connected to server.\n");
	printf("Port:%d\n",ntohs(cliAddr.sin_port));
	while (1)
	{
		printf("$>");
		
		//int saved_stdin = dup(0);
		 char * auszufuehren = readinput();
		 if (write(clientfd, auszufuehren, arrayLen(auszufuehren)) < 0)
		{
			printf("Could not send message");
			exit(-1);
		}
		//char ** params = getparams(auszufuehren);
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
		 
		
		if(strcmp(params[0],"exit") == 0){
			close(clientfd);
			exit(0);
		}
		if(strcmp(params[0],"put")==0){
			FILE * fp;
			char * filename = params[1];
			fp = fopen(filename, "r");
			if(fp == NULL){
				printf("Error reading file.");
				exit(-1);
			}
			send_file(fp,clientfd);

		}
		if(strcmp(params[0],"get")==0){
		write_file(clientfd,params[1]);
		}
		//dup2(clientfd, 0);
		char *buf;
		arrayInit(buf);
		char c[1];
		do
		{
			/* code */
			if(read(clientfd,c,sizeof(c))<0){
			printf("Could not read socket");
			exit(-1);
			}
			arrayPush(buf)= (char)c[0];
		} while (arrayTop(buf)!= EOF);
		arrayPop(buf);
		arrayPush(buf) = '\0';
		
		
		printf("%s\n",buf);

		 //char * auszuzeigen = readinputeof();
		//  if(strcmp(auszuzeigen,"eof")==0){
		//  	continue;
		//  }else{
		  	//printf("%s\n",auszuzeigen);
		//  }
		//dup2(saved_stdin, 0);
		//close(saved_stdin);
		
		// char * buf;
		// arrayInit(buf);
		// char c[1];
		// int n;
		// while(n >0){
		// 	n=read(fd)
		// }
	}

	// getc(stdin);
	// printf("Client Exit\n");

	return 0;
}
