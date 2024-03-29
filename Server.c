#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <signal.h>
#include <unistd.h>
#define BUFF 128
#define RCVTYPE 16
#define SNDTYPE 17 

int msgid;
typedef struct msgp {
	long mtype;
	int terme1;	
	int terme2;	
}msgp;

void interup() {

printf("Fin du server d'addition");

msgctl(msgid, IPC_RMID, NULL);

exit(0);
}

int main(int argc, char* argv[])
{
key_t cle;
msgp unMessage;

if ( ( cle  = ftok("/home/azman/ed34/Server",17 ) ) == -1)
	perror("ftok"), exit(1);


printf("\n cle : %d\n", cle);


if ( ( msgid = msgget(cle, IPC_CREAT|IPC_EXCL|S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH )) == -1 )
	perror("msgget"), exit(1);

printf("\n msgid: %d\n", msgid);

signal(SIGINT, interup);

for (;;) {
	msgrcv(msgid, &unMessage, sizeof(msgp), RCVTYPE, MSG_NOERROR);


	printf("\nServer: Terme1: %d, Terme2: %d\n", unMessage.terme1, unMessage.terme2);
	unMessage.terme1 = unMessage.terme1 + unMessage.terme2;
	unMessage.mtype = SNDTYPE;
	msgsnd(msgid, &unMessage, sizeof(unMessage),0);
sleep(1);
} 
exit(EXIT_SUCCESS);

}

