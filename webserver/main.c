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

void initialiser_signaux(){
  
  if ( signal ( SIGPIPE , SIG_IGN ) == SIG_ERR )
    {
      perror ( " signal " );
    }
}

void main(void){
  initialiser_signaux();
  int socket_serveur = creer_serveur(8080);

  int socket_client, lg ;
  

  while(1){
    socket_client = accept ( socket_serveur , NULL , NULL );
    if ( socket_client == -1){
      perror ( " echec d'accept " ); // traitement de l'erreur 
    }
    if (fork() == 0){
   
      // On peut maintenant dialoguer avec le client
      const char * message_bienvenue = " Bonjour , bienvenue sur mon serveur 1 \n 2 \n 3 \n 4 \n 5 \n 6 \n 7 \n 8 \n 9 \n 10\n" ;
      wait(1000);
      write(socket_client,message_bienvenue,strlen(message_bienvenue));
      while(1){
	lg = read(socket_client,buffer, 512);
	printf("le serveur a recu: %s\n",buffer);
	write(socket_client,buffer, 512);
      }
      
    }
  }
  shutdown(socket_client,2);
  close(socket_client);
  shutdown(socket_serveur,2);
  close(socket_serveur);
}


