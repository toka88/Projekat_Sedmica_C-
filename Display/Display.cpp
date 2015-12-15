#include "Display.h"

#include <iostream>
#include <vector>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>
#include <linux/fb.h>
#include <sys/mman.h>


#include "font5x7.h"
#include "Display.h"

#define FB_PATH		"/dev/fb0"
#define PAGE_SIZE 4096
#define DISPLAY_WIDTH  240
#define DISPLAY_HEIGHT 320
#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF

const unsigned char font_mask[8]= {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

using namespace std;
///Inicijalizacija statickih varijabli
//    Display::flag=0; //Na pocetku se inicijalizuje na nulu da bi se znalo da li je displej vec inicijalizovan ili ne
     //inicijalizacija maske
//    Display::frame_len = 0;
//    Display::frame_map = NULL;

///Konstruktor bez parametara
Display::Display()
{
    //Podrazumevani konstruktor, sva inicijalizacija se radi u inicijalizacija() funkciji
}

///Destruktor
Display::~Display()
{
    delete[] frame_map; //Oslobadjanje memorije na koju je pokazivao ovaj pokazivac
}


///Inicijalizacija displeja
void Display::inicijalizacija()
{
		flag=0; //Na pocetku se inicijalizuje na nulu da bi se znalo da li je displej vec inicijalizovan ili ne
    //font_mask[8]= {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01}; //inicijalizacija maske
    frame_len = 0;
    frame_map = NULL;
		
    fb_fd = open(FB_PATH, O_RDWR);
    if (fb_fd < 0) {
		printf("Couldn't open %s\n", FB_PATH);  //Ako vrednost ima manju vrednost o nula onda nije otvoren fajl i prijavljuje se greska
	}
	/* Get the type of video hardware */
	if (ioctl(fb_fd, FBIOGET_FSCREENINFO, &finfo) < 0 ) {
		printf("Couldn't get fb hardware info\n");
	}
	frame_offset = ((long)finfo.smem_start) - (((long)finfo.smem_start &~ (PAGE_SIZE-1)));
	frame_len = finfo.smem_len + frame_offset;
	frame_map = (unsigned char *)mmap(NULL, frame_len, PROT_READ|PROT_WRITE, MAP_SHARED, fb_fd, 0); /// ??? Mislim da bi trebalo da ovo radi
	flag = 1;   //displej je uspesno inicijalizovan
}




//Dodavanje novog elementa u niz
void Display::dodajString(string rec)
{
    if(bafer.capacity()<31) //Proverava da li je pun bafer
    {
        bafer.push_back(rec);   //ako nije dodaje element na kraj
    }
    else if(bafer.capacity()==31) //Ako je pun
    {
        bafer.erase(bafer.begin()); //Isbrisan elemenat koji je prvi dodat u listu, najstariji podatak
        bafer.push_back(rec);    //Dodat novi elemenat na kraj liste
    }
}

// Brise se sve sa ekrana
void Display::izbrisiDisplej()
{
    for(int i = 0; i<DISPLAY_WIDTH; i++)
    {
        for(int j=0; j<DISPLAY_HEIGHT; j++)
        {
            //pitati Vuka za "FREJM"
            lcd_point(i,j,COLOR_BLACK);  // ekran se ispisuje crnom bojom
        }
    }
}

/// Ispisuju se sve reci koje su smestene u bafer
//Zamisljeno je da se pre ispisivanja pozove funkcija za brisanje
void Display::ispisivanjeReci()
{
    int x = 10;
    int y = 10;
    for(unsigned int i = 0; i < bafer.capacity(); i++)
    {		
    		char* privremena = new char[bafer[i].size() + 1];
    		strcpy(privremena, bafer[i].c_str());
    		
        lcd_putString(x, y, privremena);	////ova metoda vraca pointer na ovaj string
        y+=10;  //Prabacuje u novi red za pisanje
        x=10;   //Vraca kursor na pocetak reda
        delete[] privremena;
    }
}






///Privatne funkcjie funkcije
//pomocna funkcija za ispisivanje jedne tacke
 void Display::lcd_point(unsigned short x, unsigned short y, unsigned short color)
 {
     if(x >= DISPLAY_WIDTH)
     {
        return;
     }
     if(y >= DISPLAY_HEIGHT)
     {
         return;
     }

     *((unsigned short *)(frame_map + x*2 + 240*2*y)) = color;
     return;
 }
 //Pomocna za ispisivanje jednog karaktera
 int Display::lcd_putChar(int x, int y, unsigned char ch)
 {
     unsigned char data = 0; 
     int i = 0;
     int j = 0;
     unsigned short color = COLOR_BLACK;

     if(x>=(DISPLAY_WIDTH - 8))
     {
         return 0;
     }
     if(y>=(DISPLAY_HEIGHT-8))
     {
         return 0;
     }
     if((ch < 0x20)||(ch>0x7f))
     {
         ch = 0x20;
     }

     ch -=0x20;

     for(i=0; i<8; i++)
     {
         data = font5x7[ch][i];
         for(j=0; j<6; j++)
         {
            if( (data&font_mask[j])==0 )
            {
                color = COLOR_WHITE;
            }
            else
            {
                color = COLOR_BLACK;
            }
            lcd_point(x,y,color);
            x++;
         }
         y++;
         x -= 6;
     }
     return 1;
 }
 // Pomocna funkcija za ispisivanje stringa
void Display::lcd_putString(int x, int y, char *pStr)
 {
     while(1)
     {
         if((*pStr)=='\0')
         {
             break;
         }

         if(lcd_putChar(x,y,*pStr++)==0)
         {
             break;
         }
         x +=6;
     }
 }

