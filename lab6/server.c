#include <netdb.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h> #include<unistd.h> int doprocessing (int sock);
int main( ) {
int sockfd, new, portno; char buffer[1000];
struct sockaddr_in serv_addr, cli_addr; int n;
pid_t pid;
/* First call to socket() function */ 
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
perror("ERROR opening socket"); exit(1);
}
/* Initialize socket structure */
bzero((char *) &serv_addr, sizeof(serv_addr)); portno = 5001;

 serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); serv_addr.sin_port = htons(portno);
/* Now bind the host address using bind() call.*/ 
if (bind(sockfd, (struct sockaddr *) &serv_addr,
sizeof(serv_addr)) < 0) { perror("ERROR on binding");
exit(1);
}
listen(sockfd,5);
socklen_t clilen;
while (1) { new = accept(sockfd, (struct sockaddr *) &cli_addr,&clilen);
if(new<0)
{ exit(1);
}
/* Create child process */
if ((pid=fork()) == 0) { /* This is the client process */
close(sockfd);
while(1)
{
bzero(buffer,256);
recv(new,buffer,255,0);
if(strcmp(buffer,"logout")==0)
	{	
	printf(" \n disconnected from %s:%d",inet_ntoa(cli_addr.sin_addr),htons(cli_addr.sin_port)); break;
}
else
{
printf("\n client %d and message: %s\n",htons(cli_addr.sin_port),buffer);
bzero(buffer,sizeof(buffer)); strcpy(buffer,"i got your message"); send(new,buffer,sizeof(buffer),0);
}
}
}
}
return 0;
}
