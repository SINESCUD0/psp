#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>

long factorial(int n)
{
	int c;
	int result = 1;

	for (c = 1; c <= n; c++){
		result = result * c;
	}

	return result;
}

int numeroRandom(){
	time_t t;
	int numero1;
	srand((unsigned) time(&t));
	//Generamos numero aleatorio entre 1 y 10
	numero1=rand() % 10;
	return numero1;
}

void pipe1(){
	int fd[2];
	pipe(fd);
	char buffer[100];
	int numero1;
	numero1 = numeroRandom();
	char numero[3];
	sprintf(numero,"%d",numero1);
	numero[2]='\n';
	pid_t pid;
	pid = fork();
	if (pid==0)
     
	{
		close(fd[1]); // Cierra el descriptor de escritura
		printf("El hijo se dispone a leer del padre \n");
		read(fd[0], buffer, 100);
		printf("Numero del padre: %s \n", buffer);
		wait(NULL);

	}
     
	else

	{
		
		close(fd[0]); // Cierra el descriptor de lectura
		printf("El padre escribe en el hijo \n");
		write(fd[1], numero, 2);  
		wait(NULL);
	}
}

void pipe2(){
	int fd[2];
	pipe(fd);
	char buffer[100];
	int numero1;
	numero1 = numeroRandom();
	char numero[3];
	sprintf(numero,"%d",numero1);
	numero[2]='\n';
	char factorial2[100];
	long factorial1 = factorial(numero1);
	sprintf(factorial2,"%ld",factorial1);
	pid_t pid;
	pid = fork();
	if (pid==0)
     
	{
		close(fd[0]); // Cierra el descriptor de lectura
		printf("El hijo escribe en el padre \n");
		write(fd[1], factorial2, 100); 

	}
     
	else

	{
		close(fd[1]); // Cierra el descriptor de lectura
		wait(NULL);
		printf("El padre lee el hijo\n");
		read(fd[0],buffer, 100);  
		printf("Mensaje leído del hijo: %s \n", buffer);
	}
}

void main(){
	pid_t pid;
	pid = fork();
	
	if (pid==0)
     
	{
		pipe2();
	}
     
	else

	{
		pipe1();
	}
}
