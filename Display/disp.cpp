#include "Display.h"
#include "font5x7.h"
#include "font_macro.h"
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int main()
{	
	Display disp;
	string rec;
	disp.inicijalizacija();
	for(int i=0; i<39; i++)
	{
		disp.izbrisiDisplej();
		cin >> rec;
		disp.dodajString(rec);
		disp.ispisivanjeReci();
	}
	return 1;
}
