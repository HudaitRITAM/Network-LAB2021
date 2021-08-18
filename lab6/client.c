#include<netinet/in.h>
#include<arpa/inet.h> 
#include<netdb.h>
#include<fcntl.h>
#include<unistd.h> 
#include<string.h> 
#include<stdlib.h> 
#include<stdio.h>
#include<sys/types.h> 
#include<sys/socket.h>
int main(int argc,char **argv)
{
int sf,pno; struct sockaddr_in serv_addr; char buffer[2000]; if(argc<3)
{ 
fprintf(stderr,"%s hostname port\n",argv[0]); exit(0);
}
pno=atoi(argv[2]); //create socket
sf=socket(AF_INET,SOCK_STREAM,0); if(sf<0)
{
printf("\n socket not created");
exit(1);
}
else
printf("\n successfully socket created");
bzero((char*)&serv_addr,sizeof(serv_addr)); serv_addr.sin_family=AF_INET; serv_addr.sin_port=htons(pno); serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
if(connect(sf,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
{ printf("is error"); exit(1);
}
else
printf(" \n successfully connection established \n ");
//asking message from the client
while(1)
{
printf("\n enter message :"); 
bzero(buffer,sizeof(buffer));
scanf("%s",&buffer[0]);

//sends message to the server
int n;
send(sf,buffer,strlen(buffer),0);
//now read the server response
if(strcmp(buffer,"logout")==0)
{
close(sf); printf("\n you are disconnected\n \n ");
break;
}
else{ bzero(buffer,256); n=recv(sf,buffer,256,0);
printf("\n %s",buffer);
}
}
return 0;
}
