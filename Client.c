#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#define BUFF 128
#define RCVTYPE 17
#define SNDTYPE 16 

typedef struct msgp {
	long mtype;
	int terme1;	
	int terme2;	
}msgp;

int main(int argc, char* argv[])
{
key_t cle;
int msgid;
msgp unMessage;

if (argc != 3) printf("		USAGE: nombre nombre\n"), exit(-1);

if ( ( cle  = ftok("/home/azman/ed34/Server",17 ) ) == -1)
	perror("Lancer le serveur d'addition"), exit(1);


printf("\n cle : %d\n", cle);
unMessage.mtype = SNDTYPE;
unMessage.terme1 = atoi(argv[1]);
unMessage.terme2 = atoi(argv[2]);

if ( ( msgid = msgget(cle, 0 )) == -1 )
	perror("msgget"), exit(1);

printf("\n msgid: %d\n", msgid);
msgsnd(msgid, &unMessage, sizeof(msgp),0);

msgrcv(msgid, &unMessage, BUFF, RCVTYPE, MSG_NOERROR);
 
printf("Client: Somme: %d", unMessage.terme1);
exit(EXIT_SUCCESS);

}

