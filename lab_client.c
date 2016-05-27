#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_UDP_PORT 9000
#define SERV_HOST_ADDR "127.0.0.1" /* host addr for server */
#define MAXLINE 512

char *pname;

main(argc, argv)
int argc;
char *argv[];
{
	int sockfd;
	struct sockaddr_in cli_addr, serv_addr;
	
	pname = argv[0];
	/*
	* Fill in the structure "serv_addr" with the address of the
	* server that we want to send to.
	*/
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
	serv_addr.sin_port = htons(SERV_UDP_PORT);
	/*
	* Open a UDP socket (an Internet datagram socket).
	*/
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	perror("client: can't open datagram socket");
	/*
	* Bind any local address for us.
	*/
	
	bzero((char *) &cli_addr, sizeof(cli_addr));  /* zero out */
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	cli_addr.sin_port = htons(0);

	if (bind(sockfd,(struct sockaddr*)&cli_addr,sizeof(cli_addr))< 0)
	perror("client: can't bind local address");

	dg_cli(stdin,sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr));
	close(sockfd);
	exit(0);		
}
	
	dg_cli(fp, sockfd, pserv_addr, servlen)
	FILE *fp;
	int sockfd;
	struct sockaddr *pserv_addr; /* ptr to appropriate sockaddr_XX structure */
	int servlen; /* actual sizeof(*pserv_addr) */
	{
	        struct timeval time1, time2; // structures that can take time in seconds and micro seconds.
		double t[10],time_avg;
		int n,pktCount;
		char sendline[MAXLINE], recvline[MAXLINE + 1],header, packet[MAXLINE];
		printf("\n Enter the message to be send :  ");	
		fgets(sendline, MAXLINE, fp);
		int i,pktSize,pkt,j;
		n = strlen(sendline);
		pktSize = 6;
		if(n%pktSize == 0)
			{ pkt = n/pktSize;}
                else {pkt = n/pktSize + 1;}
        
	for(pktCount=0;pktCount<pkt-1;pktCount++)
	{	
		header=(char)(((int) '0' ) + pktCount);
		packet[0] = header;	
		for(i=1; i<=pktSize; i++)
		{
		packet[i] = sendline[pktCount*pktSize + i-1];		
                packet[pktSize+1] = '\0';		
		}
		gettimeofday(&time1,NULL); // time measurement at time instant t1
		if(sendto(sockfd,packet, n, 0, pserv_addr, servlen) != n)
		perror("dg_cli: sendto error on socket");
		/*
		* Now read a message from the socket and write it to * our standard output.
		*/
		n = recvfrom(sockfd, recvline, MAXLINE, 0, (struct sockaddr *) 0, (int *) 0);
			
		
		if (n < 0)
		perror("dg_cli: recvfrom error");
		
		gettimeofday(&time2,NULL); // time measurement at time instant t2	
		t[pktCount] = ((double)(time2.tv_sec-time1.tv_sec)*1000000+(double)(time2.tv_usec-time1.tv_usec))/1000;
		time_avg = time_avg + t[pktCount];

		recvline[n] = 0; /* null terminate */
		printf("\n Packet Send  :  ");		
		fputs(recvline, stdout);
		printf("\n");	
		printf("Time difference in %f ms \n", ((double)(time2.tv_sec-time1.tv_sec)*1000000+(double)(time2.tv_usec-time1.tv_usec))/1000);	
	}
	
	if (ferror(fp))
	perror("dg_cli: error reading file");
	time_avg=time_avg/(pkt-1);
	printf("\nAverage time is: %f \n",time_avg);
	}
	
