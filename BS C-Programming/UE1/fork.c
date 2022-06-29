#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(){
    pid_t pid1 = fork();
    pid_t pid2 = fork();

    if (pid2 == 0){
        printf("Hello2");
    }
    else if(pid2 > 0){
        printf("Hello1");
    }
}

