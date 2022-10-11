#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main(){


	pid_t pid, pid_hijo;
	
	pid = fork();
	if(pid==0){
		system("hostname");
	}
	else{
		wait(NULL);
		printf("\nSoy el padre y mi pid es: %d \n", getpid());
		printf("\nMi hijo es el proceso: %d \n", pid);
	}
	exit(0);
}
