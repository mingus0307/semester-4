/*
 * SocketExample.c
 *
 * Stefan Wohlfeil
 * 2017-04-09
 *
 * Clientprogramm, das sich mit einem Serverprozess verbindet
 * und eine Textzeile an diesen sendet.
 * Basiert auf Code aus der Dokumentation der GNU Libc.
 */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SERVERHOST "localhost"
#define SERVERPORT 3000
#define MESSAGESTRING "Nachricht vom Client\n"




/* init_sockaddr
 * Hilfsfunktion: Macht aus einen hostnamen und einer portnummer
 * eine passende Socket-Adress-Struktur von Typ AF_INET.
 *
 * Ergebnis wird in den ersten Parameter geschrieben
 */
void
init_sockaddr (struct sockaddr_in *name,
               const char         *hostname,
               uint16_t           port)
{
struct hostent *hostinfo;

   name->sin_family = AF_INET;
   name->sin_port = htons (port);
   hostinfo = gethostbyname (hostname);
   if (hostinfo == NULL) {
       fprintf (stderr, "Unknown host %s.\n", hostname);
       exit (EXIT_FAILURE);
   } /* if */
   name->sin_addr = *(struct in_addr *) hostinfo->h_addr;
} /* init_sockaddr */





/* write_to_server
 * Hilfsfunktion: Schreibt den übergebenen String in das
 * übergebene Socket
 *
 */
void
write_to_server (int  socket,
                 char *message)
{
int nbytes;

/* Intern ist ein Socket mit einem file descriptor vergleichbar,
   daher kann man unter UNIX einfach write statt send nehmen */
   nbytes = write (socket, message, strlen (message) + 1);
   if (nbytes < 0) {
      perror ("write");
      exit (EXIT_FAILURE);
   } /* if */
} /* write_to_server */





int
main (int  argc,
      char *argv[]) {
struct sockaddr_in servername;

/* Create the socket. */
int sock = socket (PF_INET, SOCK_STREAM, 0);
   if (sock < 0) {
       perror ("socket (client)");
       exit (EXIT_FAILURE);
   } /* if */
   /* Connect to the server. */
   init_sockaddr (&servername, SERVERHOST, SERVERPORT);
   if (0 > connect (sock,
                    (struct sockaddr *) &servername,
                    sizeof (servername))) {
       perror ("connect (client)");
       exit (EXIT_FAILURE);
   } /* if */
   /* Send data to the server. */
   write_to_server (sock, MESSAGESTRING);
   close (sock);
   exit (EXIT_SUCCESS);
} /* main */