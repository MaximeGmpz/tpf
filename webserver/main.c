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
  if ( signal ( SIGPIPE , SIG_IGN ) == SIG_ERR )
    {
      perror ( " signal " );
    }
}

void verif_GET(FILE * fd, char * buffer){
 const char s[2] =" ";
      char * token;
      int t1,t2;
    
      token = strtok(buffer,s);//premier token
      if(strcmp(token,"GET")==0){
	int cpt=0;
	while(cpt<2){
	    token = strtok(NULL, s);
	    cpt++; 
	}
	token=strtok(token,"/.");
	if(strcmp(token,"HTTP")==0){//verif parti HTTP
	  if(strcmp(token=strtok(NULL,"/."),"1")==0){//Verif de M
	    if((t1=strcspn(token=strtok(NULL,"/."),"0"))==0|| (t2=strcspn(token,"1"))==0){ //vérif de m
	      fprintf(fd,"ok");
	      do{
		fgets(buffer, 512, fd);
	      }while(strcmp(buffer,"\n")!=0 || strcmp(buffer,"\r\n")!=0);
		 
	      const char * msg="Connection OK\n";
	      fprintf(fd, "HTTP1.1 200 OK\r\nContent-Length: %d\r\n\r\n%s",(int)strlen(msg),msg);
	    }else{
	      printf("m != 0 ou 1 :|%s| |%d| |%d|",token,t1,t2);
	      exit(1);
	    }
	  }else{
	    printf("M != 1:|%s|",token);
	    exit(1);
	  }
	}else{
	  printf("erreur HTTP|%s|",token);
	  exit(1);
	}
      }else{
	printf("erreur GET|%s|",token);
	exit(1);
      }
}


void main(void){

  int socket_serveur = creer_serveur(8080);

  int socket_client ;
  

  while(1){
    initialiser_signaux();
    socket_client = accept ( socket_serveur , NULL , NULL );
    FILE *fd = fdopen(socket_client,"w+");
    if (fork() == 0){
      if ( socket_client == -1){
	perror ( " echec d'accept " ); // traitement de l'erreur 
      }
      const char * message_bienvenue = " Bonjour , bienvenue sur mon serveur 1 \n 2 \n 3 \n 4 \n 5 \n 6 \n 7 \n 8 \n 9 \n 10\n";
    
      while(socket_client){
	char buffer[512];
		     
	if(fgets(buffer,512,fd)!=NULL){
	  verif_GET(fd,buffer);
	
	  printf("le serveur a recu: %s\n",buffer);
	  fprintf(fd,"<TPF>:");
	  fprintf(fd,"<TPF>:",message_bienvenue);
	}else{
	  printf("erreur fgets");
	  exit(1);
	}
      }
	
    }
      fclose(fd);
      shutdown(socket_client,2);
      close(socket_client);
    
  }
	
  shutdown(socket_serveur,2);
  close(socket_serveur);
}



