#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main ()  {
      int pip1[2]; int pip2[2];
      pid_t retour;
      char chaine[30];
pipe(pip1);
pipe(pip2);
retour = fork();
if (retour == 0)
            {
            close (pip1[0]);
            close (pip2[1]);
            write (pip1[1], "hello, je suis le processus A", 36);
            read (pip2[0], chaine, 36);
            printf("fils: la chaine lue est %s\n", chaine);
            close (pip1[1]);
            close (pip2[0]);
            }
else
{

close (pip1[1]);
close (pip2[0]);
write (pip2[1], "hello, je suis le processus B", 36);
read (pip1[0], chaine, 36);
printf("pere: la chaine lue est %s\n", chaine);
close (pip1[0]);
close (pip2[1]);
wait(NULL);
}
exit(0);
}
