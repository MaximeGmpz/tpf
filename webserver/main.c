#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include "socket.h"

char buffer[512];

void traitement_signal( int sig ){
  printf ( "Signal %d reçu \n" , sig );
  waitpid(-1, NULL, 0);
}

void initialiser_signaux ( void ){
  struct sigaction sa ;
  sa.sa_handler = traitement_signal ;
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = SA_RESTART ;
  if (sigaction(SIGCHLD,&sa,NULL) == -1){
    perror("sigaction (SIGCHLD)");
  }
}

void inialiser_signaux(){
  
  if ( signal ( SIGPIPE , SIG_IGN ) == SIG_ERR )
    {
      perror ( " signal " );
    }
}

void main(void){
  initialiser_signaux();
  int socket_serveur = creer_serveur(8080);

  int socket_client ;
  

  while(1){
    socket_client = accept ( socket_serveur , NULL , NULL );
    if ( socket_client == -1){
      perror ( " echec d'accept " ); // traitement de l'erreur 
    }
    if (fork() == 0){
      FILE *fd = fdopen(socket_client,"w+");
   
      // On peut maintenant dialoguer avec le client
      const char * message_bienvenue = " Bonjour , bienvenue sur mon serveur 1 \n 2 \n 3 \n 4 \n 5 \n 6 \n 7 \n 8 \n 9 \n 10\n" ;
      fprintf(fd,"<TPF>:",message_bienvenue);
      while(1){
        fgets(buffer, 512,fd);
	printf("le serveur a recu: %s\n",buffer);
	fprintf(fd,"<TPF>:",buffer);
      }
      
    }
  }
  shutdown(socket_client,2);
  close(socket_client);
  shutdown(socket_serveur,2);
  close(socket_serveur);
}


