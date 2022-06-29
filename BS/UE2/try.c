#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(void){
    char * argv[] = {"egrep","/\*.*\*/",NULL};
    pid_t pid = fork();

    if (pid==0){
        execvp("egrep",argv);
        printf("Child%d\n",getpid());
        exit(-1);
    }else {
        waitpid(pid,0,0);
        printf("Parent%d\n",pid);
        
    }
    return 0;
}