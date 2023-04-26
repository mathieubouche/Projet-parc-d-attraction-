#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>


void deplacements(int* coorx, int* coory)
{
 if (key[KEY_UP])
        {* coory=* coory-7;

        }

        if (key[KEY_DOWN])
        {
            * coory=* coory+7;
        }
        if (key[KEY_RIGHT])
        {
            *coorx=*coorx+7;
        }

        if (key[KEY_LEFT])
        {
            *coorx=*coorx-7;
        }

        if(* coory>SCREEN_H-50)
        {
            * coory=SCREEN_H-50;
        }
        if(* coory<0)
        {
        * coory=0;
        }
        if(*coorx<0)
        {*coorx=0;

        }

         if(*coorx>SCREEN_W-30)
        {*coorx=SCREEN_W-30;

        }

}

void delimitations(BITMAP*page)
{
     rect(page,75,50,155,150,makecol(255, 0, 0));
     rect(page,15,270,165,355,makecol(255, 0, 0));
     rect(page,165,255,250,355,makecol(255, 0, 0));
     rect(page,70,435,155,510,makecol(255, 0, 0));
     rect(page,310,160,360,220,makecol(255, 0, 0));//maison milieu
     rect(page,450,30,565,100,makecol(255, 0, 0));
     rect(page,520,360,630,430,makecol(255, 0, 0));
     rect(page,410,420,460,445,makecol(255, 0, 0)); //tableau
     rect(page,630,190,710,250,makecol(255, 0, 0));
     rect(page,720,10,800,80,makecol(255, 0, 0));
     rect(page,200,550,600,580,makecol(255, 0, 0));//train





}

























int main()
{
    BITMAP *page;
    BITMAP *carte;
    BITMAP *cowboy1;
    int width;


    allegro_init();
    install_keyboard();
    int coorx=400;
    int coory=475;
    int* coorx1=&coorx;
    int* coory1=&coory;
    int coorx2=0;
    int coory2=0;
    int* coorx3=&coorx2;
    int* coory3=&coory2;
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


    // CREATION DU BUFFER D'AFFICHAGE � la taille de l'�cran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);
    carte=load_bitmap("carte bonnes dims.bmp",NULL);
    if (!carte)
    {
        allegro_message("pas pu trouver images/carte.bmp");
        exit(EXIT_FAILURE);
    }
    cowboy1=load_bitmap("cowboytest.bmp",NULL);
    if (!cowboy1)
    {
        allegro_message("pas pu trouver images/cowboy1.bmp");
        exit(EXIT_FAILURE);
    }
    clear_bitmap(page);


    while(!key[KEY_ESC])
    {

        clear_bitmap(page);
        blit(carte,page,0,0,0,0,SCREEN_W,SCREEN_H);
        deplacements(coorx1,coory1);
        delimitations(page);
        draw_sprite(page,cowboy1, *coorx1 ,*coory1);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(50);
    }
free(page);
free(carte);



    return 0;
}END_OF_MAIN();
