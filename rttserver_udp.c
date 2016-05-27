#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXMESG 2048
#define SERV_UDP_PORT 9000
#define SERV_HOST_ADDR "127.0.0.1"
/* replace this entry with the IP address of the server */

char *pname;

main(argc, argv)
int argc;
char *argv[];
{
	int sockfd;
	struct sockaddr_in serv_addr, cli_addr;
	
	pname = argv[0];

	/*
	* Open a UDP socket (an Internet datagram socket).
	*/

	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	perror("server: can't open datagram socket");

	/*
	* Bind our local address so that the client can send to us.
	*/

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SERV_UDP_PORT);

	if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))< 0)
	perror("server: can't bind local address");
	
	dg_echo(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	/* NOTREACHED */
}

/*
* Read a datagram from a connectionless socket and write it back to
* the sender.
*
* We never return, as we never know when a datagram client is done.
*/

dg_echo(sockfd, pcli_addr, maxclilen)
	int sockfd;
	struct sockaddr *pcli_addr; /* ptr to appropriate sockaddr_XX structure */
	int maxclilen; /* sizeof(*pcli_addr) */
	{
	int n, clilen;
	char mesg[MAXMESG];
	for ( ; ; ) 
	{
		clilen = maxclilen;
		n = recvfrom(sockfd, mesg, MAXMESG, 0, pcli_addr, &clilen);
		printf("Packet Recieved : \t");
		puts(mesg);
		if (n < 0)
			perror("dg_echo: recvfrom error");
		sleep(1);
		if (sendto(sockfd, mesg, n, 0, pcli_addr, clilen) != n)
		perror("dg_echo: sendto error");
		printf("Packet Send Back \n");
	}
}


