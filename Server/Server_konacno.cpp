#include <stdio.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <dirent.h> 
#include <stdlib.h> 
#include <string.h> 
#include <pthtread.h>
#include <unistd.h> 
#include <iostream>
#include "Logovanje.h"  //Za rad sa testualnim fajlom

using namespace std;

struct igraci
{
   char ime[20];
   char sifra[20];
   int bodovi;
};

void* igric_handler(void*);    //prptotip funkcije zaz igranje

int main( int argc, char *argv[] ) 
{
    Logovanje log;
	int sockfd, newsockfd, portno, clilen, newsockfd_second, ; 
    char buffer[256]; 
    char * token;
    igraci prvi, drugi;
    bool petlja = false;
    /*Niz sa tredovima */
    pthread_t prviTred, drugiTred;

    struct sockaddr_in serv_addr, cli_addr; 
    int  n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd < 0) 
    { 
        perror("ERROR opening socket"); 
        exit(1); 
    } 
    //Inicijalizacija strukture socketa
    bzero((char*) &serv_addr, sizeof(serv_addr));	//inicijalizuje se struktura na nulu
    portno = 5005;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /******* Bindovanje ***********/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, 
                          sizeof(serv_addr)) < 0) 
    { 
         perror("ERROR on binding"); 
         exit(1); 
    }

    cout<<"Server started... waiting for players..."<<endl;

    listen(sockfd,9); //Maksimalan  broj koji ce se kreirati, mislim da je jedan za server i ostali za igrace

    clilen = sizeof(cli_addr);

    while(1)
    {
    	newsockfd = accept(sockfd,(struct  sockaddr *) &cli_addr, &clilen);


    	cout << "Player one connected..." <<endl;
    	//Proveravane da li je prvi igrrac stari ili novi
        read(newsockfd, buffer, 255);
        buffer[n]=0; //Pretvara niz carova u odgovarajuci string
    	
        if(strcmp(buffer,"n") || strcmp(buffer, "N"))
        {
            cout << "Registrovanje novog korisnika..." << endl;
            n = read(newsockfd, prvi.ime, 19);  //Preuzimanje imena
            prvi.ime[n] = 0;

            n = read(newsockfd, prvi.sifra, 19);   //Preuzimanje sifre
            prvi.sifra[n] = 0;

            log.createNewUser(prvi.ime, prvi.sifra);

        } else if(strcmp(buffer,"o") || strcmp(buffer, "O"))
        {
            cout << "Proveravanje korisnika u bazi..."
            n = read(newsockfd, prvi.ime, 19);
            prvi.ime[n] = 0;
            n = read(newsockfd, prvi.sifra, 19);
            prvi.sifra[n] = 0;

            if (log.searchForUser(prvi.ime, prvi.sifra))
            {
                cout << "Korisnik je pronadjen"<< endl;
            }else
            {
                continue;   //Vraca se na pocetak da ceka novog korisnika jer ovaj ne postoji
            }

        }


        cout << "Cekanje na drugog korisnika" << endl;
        while(!petlja)
        {
                /***************  Ceka se na konekciju drugog korisnika ****************/
            newsockfd_second = accept(sockfd,(struct  sockaddr *) &cli_addr, &clilen);
            cout << "Second player connected..."<<endl;
            //Da li je novi ili stari
            n = read(newsockfd_second, buffer, 255);
            buffer[n] = 0;


            if(strcmp(buffer,"n") || strcmp(buffer, "N"))
            {
                cout << "Registrovanje novog korisnika..." << endl;
                n = read(newsockfd, drugi.ime, 19);  //Preuzimanje imena
                drugi.ime[n] = 0;

                n = read(newsockfd, drugi.sifra, 19);   //Preuzimanje sifre
                drugi.sifra[n] = 0;

                log.createNewUser(drugi.ime, drugi.sifra);

            } else if(strcmp(buffer,"o") || strcmp(buffer, "O"))
            {
                cout << "Proveravanje korisnika u bazi..."
                n = read(newsockfd, drugi.ime, 19);
                drugi.ime[n] = 0;
                n = read(newsockfd, drugi.sifra, 19);
                drugi.sifra[n] = 0;

                if (log.searchForUser(drugi.ime, drugi.sifra))
                {
                    cout << "Korisnik je pronadjen"<< endl;
                    petlja = true;  //Da se izadje iz ove petlje
                } else
                {
                    continue;   //Vraca se na pocetak da ceka novog korisnika jer ovaj ne postoji
                }
            }
        

        }
        int sockets[2] = {newsockfd, newsockfd_second}; //u ovom nizu se cuvaju socketi od prethodnih korisnika
        if(pthread_create(&prviTred, NULL, igric_handler, (void*) sockets)) //Kreiranje prvog treda kome se daje adresa drugog korisnika
        {
            perror("could not create thread");
            return 1;
        }
    }

    pthread_exit(NULL); //terminiranje preostalih tredova
    free(token);    //Oslobadjanje memorije koju je zauzeo pokazivac
    return 1;
}

void* igric_handler(void* socket)
{

    char buffer[256];
    char* message;
    int socket_first = *((int*) socket);   //za komunikaciju sa prvim
    int socket_second = *(((*int)socket)+1);   //za komunikaciju sa drugim

    //Obavestavanje igraca o pocetku igre
    message = "Game is beginning...";
    write(socket_first, message, strlen(message));
    write(socket_second, message, strlen(message));


    //Zavrsetak programa
    free(socket)
    free(message);
    return 0,
}