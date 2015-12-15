#ifndef DISPLAY_H
#define DISPLAY_H

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

#define FB_PATH		"/dev/fb0"
#define PAGE_SIZE 4096
#define DISPLAY_WIDTH  240
#define DISPLAY_HEIGHT 320
#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF



class Display
{
    public:
        Display();  //podrazumevani konsruktor
        ~Display(); // Destruktor
        void dodajString(std::string);
        void izbrisiDisplej();
        void ispisivanjeReci();
        void inicijalizacija(); //Inicijalizacija, poziva se samo ako displej prethodno nije bio inicijalizovan

        //Privatne funkcije
    private:
        //Ispisivanje jedne tacke
        void lcd_point(unsigned short x, unsigned short y, unsigned short color);   //Prima koordinate i boju tacke
        //Ispis jednog karaktera
        int lcd_putChar(int x, int y, unsigned char ch);
        //Ispis Stringa
        void lcd_putString(int x, int y, char *pStr);

    private:
        //static int x;  // X koordinata
        //static int y;  //Y koordinata
        std::vector<std::string> bafer;   //Niz vektora
        //const unsigned char font_mask[8];
        int 		fb_fd;  //Sluzi za citanje i upisivanje u drajver
        struct fb_fix_screeninfo finfo;
        int 		frame_offset;
        unsigned char *	frame_map;  //Jedina dinamicka varijabla i za nju je potreban destruktor
        int 		frame_len;
        unsigned char flag;


};

#endif // DISPLAY_H
