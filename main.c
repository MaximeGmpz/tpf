int socket_serveur ;
socket_serveur = socket ( AF_INET , SOCK_STREAM , 0);
if ( socket_serveur == -1)
{
/* traitement de l ’ erreur */
perror ( " socket_serveur " );
}
/* Utilisation de la socket serveur */
//-----------création socket en IPv4-----------------

struct sockaddr_in {
sa_family_t
sin_family ; /* address family : AF_INET */
in_port_t
sin_port ;
/* port in network byte order */
struct in_addr sin_addr ;
/* internet address */
};
/* Internet address . */
struct in_addr {
uint32_t
s_addr ;
};
// ??

struct sockaddr_in saddr ;
saddr . sin_family = AF_INET ; /* Socket ipv4 */
saddr . sin_port = htons (8080); /* Port d ’é coute */
saddr . sin_addr . s_addr = INADDR_ANY ; /* é coute sur toutes les interfaces */
if ( bind ( socket_serveur , ( struct sockaddr *)& saddr , sizeof ( saddr )) == -1)
{
perror ( " bind socker_serveur " );
/* traitement de l ’ erreur */
}

if ( listen ( socket_serveur , 10) == -1)
{
perror ( " listen socket_serveur " );
/* traitement d ’ erreur */
}

int socket_client ;
socket_client = accept ( socket_serveur , NULL , NULL );
if ( socket_client == -1)
{
perror ( " accept " );
/* traitement d ’ erreur */
}
/* On peut maintenant dialoguer avec le client */
const char * message_bienvenue = " Bonjour , bienvenue sur mon serveur \ n " ;
write ( socket_client , message_bienvenue , strlen ( message_bienvenue ));
