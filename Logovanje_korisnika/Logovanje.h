
#ifndef LOGOVANJE_H
#define LOGOVANJE_H
#include <stdio.h>
#include <fstream>  /* Za citanje i upisivanje u fajjl */

const char FIlE_DEST[] = "Proba.txt";
struct player{
    std::string user;
    std::string pass;
    int score;
};

class Logovanje
{
    public:
        Logovanje();
        ~Logovanje();
        bool searchForUser(std::string, std::string);   //radi
        bool createNewUser(std::string, std::string);   //radi
        bool deleteUser(std::string);                   //
        void updateScoreList();
        void printScoreList();

    private:
        std::string score;
        std::ifstream readFile;
        std::ofstream writeFile;
        std::string username;
        std::string password;
};

#endif // LOGOVANJE_H
