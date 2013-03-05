/*
 * client.c
 *
 *  Created on: 01.03.2013
 *      Author: dev
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

	if (argc < 3) {
          fprintf(stderr,"usage %s hostname port\n", argv[0]);
          exit(0);
       }
       portno = atoi(argv[2]);
       sockfd = socket(AF_INET, SOCK_STREAM, 0);
       if (sockfd < 0)
           error("ERROR opening socket");
       server = gethostbyname(argv[1]);
       if (server == NULL) {
           fprintf(stderr,"ERROR, no such host\n");
           exit(0);
       }

       bzero((char *) &serv_addr, sizeof(serv_addr));
       serv_addr.sin_family = AF_INET;
       bcopy((char *)server->h_addr,
            (char *)&serv_addr.sin_addr.s_addr,
            server->h_length);
       serv_addr.sin_port = htons(portno);
       if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
           error("ERROR connecting");

    int fd = open("/home/dev/workspace/client/Debug/somefile.txt", O_RDONLY );

    if(fd<=0)
    {
    	printf("Error of opening file");
    	exit(0);
    }



    while(1)
    {

    	char *bf;
    	bf = (char *) malloc(sizeof(char)*1024);
    	size_t result;
    	result = read(fd,bf,1023);
    	char fbuffer[1024];
    	if(result == 0) return 0;;
    	int i=0;
    	 while(1)
    	    {
    	    	fbuffer[i]=bf[i];
    	    	i++;
    	    	if(i>=(int)result)
    	    	{
    	    		break;
    	    	}
    	    }
    	 fbuffer[i+1]='~';
    	    n = write(sockfd,fbuffer,result);
    	    if (n < 0)
    	        error("ERROR writing to socket");
    }







    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0)
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}
