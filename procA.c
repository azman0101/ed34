#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#define BUFF 128
#define RCVTYPE 16
#define SNDTYPE 17 

typedef struct msgp {
	long mtype;
	char mtext[BUFF];
}msgp;

int main(int argc, char* argv[])
{
key_t cle;
int msgid;
msgp unMessage;

if ( ( cle  = ftok("/home/azman/ed34/test",17 ) ) == -1)
	perror("ftok"), exit(1);


printf("\n cle : %d\n", cle);
unMessage.mtype = SNDTYPE;
strcpy(unMessage.mtext, "Je suis le processus A");


if ( ( msgid = msgget(cle, IPC_CREAT|IPC_EXCL|S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH )) == -1 )
	perror("msgget"), exit(1);

printf("\n msgid: %d\n", msgid);
msgsnd(msgid, &unMessage, strlen(unMessage.mtext),0);

msgrcv(msgid, &unMessage, BUFF, RCVTYPE, MSG_NOERROR);
printf("ProcA: Message reçu: %s", unMessage.mtext);
 
exit(EXIT_SUCCESS);

}

