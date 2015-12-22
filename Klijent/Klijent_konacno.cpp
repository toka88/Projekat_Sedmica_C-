#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <arpa/inet.h>
#include <iostream>

using namespace std;

int main (int argc, char* argv[])
{
	int sockfd = 0, n = 0; 
    struct sockaddr_in serv_addr; 
    char message [100]; 
    int done; 
    int number; 
    char tmpstr [30]; 
    int received; 
    char * token; 
    char ans; 
    ftp_states stat; 
    char path[30]; 

    if(argc != 2) 
    { 
        printf("\n Usage: %s <ip of server> \n",argv[0]); 
        return 1; 
    } 
    memset(recvBuff, 0,sizeof(recvBuff)); 
    /* kreiraj socket za komunikaciju sa serverom */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
       printf("\n Error : Could not create socket \n"); 
       return 1; 
    } 
    memset(&serv_addr, 0, sizeof(serv_addr)); 
    /* kao i podatke neophodne za komunikaciju sa serverom */
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(5001); 
    /* inet_pton konvertuje ip adresu iz stringa u format
neophodan za 
serv_addr
 strukturu */	
	if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0) 
    { 
        printf("\n inet_pton error occured\n"); 
        return 1; 
    } 
    /* povezi se sa serverom definisanim preko ip adrese i porta */
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\n Error : Connect Failed \n"); 
        return 1; 
    }

    cout << "Are you OLD or NEW player...[o/n]... "<<endl;
    gets(message);
    write(sockfd, message, strlen(message));

    cout<< "Username: "<<endl;
    gets(message);
    write(sockfd, message, strlen(message));

    cout << "Password"<<endl;
    gets(message);
    write(sockfd, message, strlen(message));

    received = read(sockfd, message, 255);
    message[received] = 0;

    if(strcmp(message, "wait")){
    	cout << "Weiting on second player..."<<endl;
    }

    cout << "Game beginning..."<<endl;


    return 1;
}