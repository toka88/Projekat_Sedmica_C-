#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>    //Za sortiranje
#include "Logovanje.h"

using namespace std;

int main()
{
    Logovanje l;
    string ime, sifra;
    /*
    l.createNewUser("Marina", "Leo");
    cout<<endl<<"Ime ";
    cin >>ime;
    cout<<endl<<"Sifra ";
    cin >>sifra;
    cout<<endl;


    //l.createNewUser(ime, sifra);
    */

    if(l.searchForUser("Goran","sdf"))
    {
        cout<<endl<<"Postoji korisnik"<<endl;
    }else
    {
        cout<<endl<<"Ne postoji"<<endl;
    }

    l.printScoreList();
    cout<<endl<<"koga zelis da obrises ";
    cin >> ime;

    l.deleteUser(ime);
    //l.printScoreList();
    //l.updateScoreList();
    //l.printScoreList();

    return 1;
}
