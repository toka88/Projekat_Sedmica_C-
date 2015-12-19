
#include "Logovanje.h"
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;
//Pomocna lokalna funkcija
bool poredjenje(const player &a, const player &b)
{
    return a.score > b.score;
};

//Konstruktor bez parametara
Logovanje::Logovanje()
{

}

//Destruktor
Logovanje::~Logovanje()
{

}


//Trazenje korisnika
bool Logovanje::searchForUser(string username, string password)
{
    bool hasSuchUser = false;
    readFile.open(FIlE_DEST);
    if(!readFile.is_open())
    {
        std::cerr << "ERROR. File not opened..."<<endl;
        return hasSuchUser=false;
    }
    while(!readFile.eof())
    {
        readFile >> this->username >> this->password>> this->score;
        if(this->username == username && this->password == password)
        {
            hasSuchUser = true;
        }
    }
    readFile.close();   // Zatvorreno za citanje
    return hasSuchUser;

}

//Kreiranje novog korisnika
bool Logovanje::createNewUser(string user, string pass)
{
    int startScore = 0;
    writeFile.open(FIlE_DEST, std::ios::app);
    if(! writeFile.is_open())
    {
        cout << "Error. File not opened"<<endl;
        return false;
    } else  //Ako je uspesno otvoren
    {
        writeFile << user <<" "<<pass <<" " << startScore << endl;
    }
    writeFile.close();  //Zatvaranje otvorenog fajla
    return true;   // Podaci upisani  u bazu

}

//Brisanje postojeceg korisnika od strane administratora
bool Logovanje::deleteUser(string username)
{
    readFile.open(FIlE_DEST);
    writeFile.open("logovanje_temp.txt");   //pomocni fajl u koji ce se smestati oni clanovi koji nisu kikovani

    if(!readFile.is_open())
    {
        std::cerr << "Error. File not opened"<<endl;
        return false;
    }
    if(!writeFile.is_open())
    {
        std::cerr << "Error. File not opened"<<endl;
        return false;
    }
    while(! readFile.eof())
    {
        readFile >> this->username >> this->password >> this->score;
        if(this->username == username)
        {
            continue;
        }else
        {
            writeFile << this->username << " " << this->password << " " << this->score<<endl; // prepisivanje korisnika
        }
    }

    readFile.close();
    writeFile.close();

    remove(FIlE_DEST);  //Delete old file
    rename("logovanje_temp.txt",FIlE_DEST); //rename new file into old name

    return true;
}

//Stampanje rang liste
void Logovanje::printScoreList()
{
    int counter=1;
    readFile.open(FIlE_DEST);
    if(!readFile.is_open())
    {
        std::cerr << "ERROR. File not opened"<<endl;
        return;
    }
    while(!readFile.eof())
    {
        readFile >> this->username >> this->password >> this->score;
        cout << counter++ << ". Player: " << this->username << " score: " << this->score << endl;    //Ispisivanje imena i bodova
    }
    readFile.close();//Zatvaranje fajla
    return;
}

void Logovanje::updateScoreList()
{
    vector<player> players;
    readFile.open(FIlE_DEST);

    if(!readFile.is_open())
    {
        std::cerr << "Error. File not opened"<<endl;
        return;
    }

    while(!readFile.eof())
    {
        //Lokalne promenjive
        int temp;
        player p;

        readFile >> this->username >> this->password >> this->score;
        //Konvertovanje u int
        temp = atoi( this->score.c_str() );
        //Formiranje strukture
        p.user = this->username;
        p.pass = this->password;
        p.score = temp;
        players.push_back(p);
    }
    readFile.close(); //Zatvoren fajl iz koga se cita

    //Rangiranje takmicara
    sort(players.begin(), players.end(),poredjenje);

    //Kreiranje novog dokumenta za upis
    writeFile.open("logovanje_temp.txt");
    if(!writeFile.is_open())
    {
        std::cerr << "Error. File not opened"<<endl;
        return;
    }

    for(unsigned int i; i<players.size();i++)
    {
        writeFile << players[i].user<<" "<< players[i].pass <<" "<< players[i].score << endl;
    }

    players.clear();
    writeFile.close();

    remove(FIlE_DEST);  //Delete old file
    rename("logovanje_temp.txt",FIlE_DEST); //rename new file into old name

    return;
}

