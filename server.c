/*
 * server.c
 *
 *  Created on: 01.03.2013
 *      Author: dev
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     char fbuffer[1024];
     int fd = open("/home/dev/workspace/server/Debug/somefile.txt", O_CREAT | O_WRONLY);


  struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);
     if (newsockfd < 0)
          error("ERROR on accept");
     bzero(fbuffer,1024);
	 size_t result;
     while((n = read(newsockfd,fbuffer,1024))&&n>0)
     {
    	 if(n==0)
    	 {
    		 close(fd);
    		 printf("Closed\n");
    		 exit(0);

    	 }
		 int j=0;

		 while(j<n)
			 {
				 char * gg;
				 char p=fbuffer[j];
				 gg=&p;

				 		 result = write(fd,gg,1);
				 j++;
			 }

	   if (n < 0) error("ERROR reading from socket");



     }
     close(fd);
   		 if(result > 0 )
   		 {
   			 printf("OK\n");
   			 exit(0);
   		 }



     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0;
}
