#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int pip[2];
int main()
{
int nb_ecrit;
int pid;
/*  ouverture d'un pipe */
if(pipe(pip))
  { perror("pipe");
  exit(1);}
pid = fork();
if (pid == 0)
{
	close(pip[0]);
	close(pip[1]);
	printf("Je suis le fils\n");
	sleep(20);
}
else
{
	close(pip[0]);
	for(;;){
		if ((nb_ecrit = write(pip[1], "ABC", 3)) == -1)
      		{
      			perror ("pb write");
      			exit(1);
      		}
else
      			printf ("retour du write : %d\n", nb_ecrit);
	}
} 
exit(0);
}
