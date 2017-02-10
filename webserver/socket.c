#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

int creer_serveur(int port){
  int socket_serveur ;
  socket_serveur =socket(AF_INET,SOCK_STREAM,0);
  if (socket_serveur==-1){
    //traitement de l'erreur
    perror ( " socket_serveur " );
  }
  // Utilisation de la socket serveur
  //-----------création socket en IPv4-----------------
  //attachement de la socket serveur
  struct sockaddr_in saddr ;
  saddr.sin_family = AF_INET ; // Socket ipv4 
  saddr.sin_port =htons(port); // Port d'ecoute
  saddr.sin_addr.s_addr = INADDR_ANY ; // écoute sur toutes les interfaces
  int optval = 1;
  if ( setsockopt ( socket_serveur , SOL_SOCKET , SO_REUSEADDR , & optval , sizeof ( int )) == -1)
    perror ( " Can not set SO_REUSEADDR option " );
  if(bind(socket_serveur,(struct sockaddr*)&saddr,sizeof(saddr))==-1){
    perror ( " bind socker_serveur " ); // traitement de l erreur
  }
  struct sockaddr_in {
    sa_family_t sin_family ; // address family : AF_INET
    in_port_t sin_port ; // port in network byte order
    struct in_addr sin_addr ; // internet address 
  };
  // Internet address . 
  struct in_addr {
    uint32_t s_addr ;
  };

  

  if ( listen ( socket_serveur,10)==-1){
    perror ( " listen socket_serveur " );
    // traitement de l'erreur
  }
 
  return socket_serveur;
}
