#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#define NBALLONS 10

typedef struct ballons
{
    int x, y;    // coordonnée (du coin sup. gauche)
    int dx, dy;// vecteur deplacement
    int tx, ty;
    BITMAP* poulet;
    BITMAP* pouleto;

}t_ballons;








void vecDepAleaActeur(t_ballons *coincoin)
{
    do
    {
        coincoin->dx = rand()%4;
        coincoin->dy = rand()%4;
    }
    while (coincoin->dx==0 || coincoin->dy==0);
}





t_ballons * creerballons ()
{
    t_ballons *ballon;

    ballon = (t_ballons*)malloc(1*sizeof(t_ballons));
    ballon->poulet = load_bitmap("10-ballons-de-baudruche-en-latex-opaque-rouge_88620_1.bmp", NULL);
    ballon->pouleto = create_bitmap(50,50);
    stretch_blit(ballon->poulet, ballon->pouleto,0,0,ballon->poulet->w,ballon->poulet->h,0,0,ballon->pouleto->w,ballon->pouleto->h);

    ballon->tx = 60;
    ballon->ty = 60;

    ballon->x = rand()%(SCREEN_W - ballon->tx);
    ballon->y = rand()%(SCREEN_H - ballon->ty);

    vecDepAleaActeur(ballon);

    return ballon;
}

void remplirTabActeurs(t_ballons * tab[NBALLONS])
{
    // On "accroche" NACTEUR nouveaux acteurs
    // à chaque case du tableau
    for (int i=0;i<NBALLONS;i++)
        tab[i]=creerballons();
}



void actualiserActeur(t_ballons *coincoin)
{
    // contrôle des bords : ici on décide de rebondir sur les bords
    if  (  ( coincoin->x < 0 && coincoin->dx < 0 ) || ( coincoin->x + coincoin->tx > SCREEN_W && coincoin->dx > 0) )
        coincoin->dx = -coincoin->dx;

    if  (  ( coincoin->y < 0 && coincoin->dy < 0 ) || ( coincoin->y + coincoin->ty > SCREEN_H && coincoin->dy > 0) )
        coincoin->dy = -coincoin->dy;



   /* if  (  ( coincoin->x < 415  ) && ( coincoin->y < 207  ))
        coincoin->dx = -coincoin->dx;
        coincoin->dy = -coincoin->dy;*/



    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    coincoin->x = coincoin->x + coincoin->dx;
    coincoin->y = coincoin->y + coincoin->dy;

}





// Déterminer si les rectangles de 2 acteurs s'intersectent
// Retourne 0 si pas de collision
// Si collision alors retourne une valeur selon la position de a2 par rapport à a1
// 1 : plutôt à droite   2 : plutôt à gauche   3 : plutôt en bas   4 : plutôt en haut
int collisionActeurs(t_ballons *a1, t_ballons *a2)
{
    int retour;
    int m[4],imin,i;

    // Calcul des marges d'intersection (a2 par rapport à a1)
    m[0]=a2->x + a2->tx - a1->x; // 0: à droite
    m[1]=a1->x + a1->tx - a2->x; // 1: à gauche
    m[2]=a2->y + a2->ty - a1->y; // 2: en bas
    m[3]=a1->y + a1->ty - a2->y; // 3: en haut

    // Chercher l'indice de la plus petite marge
    imin=0;
    for (i=1;i<4;i++)
        if (m[i]<m[imin])
            imin=i;

    // A priori pas de collision
    retour=0;

    // Si la plus petite marge n'est pas strictement négative
    // alors c'est qu'on a une collision et cette collision est de ce coté
    if (m[imin]>=0)
        retour=imin+1;  // on retourne l'indice du coté + 1 (car 0 signifie "pas de collision")

    return retour;
}





// Gérer l'évolution de l'ensemble des acteurs
void actualiserTabActeurs(t_ballons * tab[NBALLONS])
{
    int i,j,cote;

    // Contrôle des collisions : si on entre en collision avec un autre
    // et que la collision tend à nous rapprocher alors on rebondit
    for (i=0;i<NBALLONS;i++)
        for (j=i+1;j<NBALLONS;j++)
            if ( (cote=collisionActeurs(tab[i], tab[j]) ) )
            {
                if ((cote==1 && tab[i]->dx<0) || (cote==2 && tab[i]->dx>0))
                    tab[i]->dx=-tab[i]->dx;
                if ((cote==3 && tab[i]->dy<0) || (cote==4 && tab[i]->dy>0))
                    tab[i]->dy=-tab[i]->dy;
                if ((cote==1 && tab[j]->dx>0) || (cote==2 && tab[j]->dx<0))
                    tab[j]->dx=-tab[j]->dx;
                if ((cote==3 && tab[j]->dy>0) || (cote==4 && tab[j]->dy<0))
                    tab[j]->dy=-tab[j]->dy;
            }

    // Gérer les déplacements habituels...
    for (i=0;i<NBALLONS;i++)
        actualiserActeur(tab[i]);

}


void tir(t_ballons * tab[NBALLONS],BITMAP*page,BITMAP*reticule)
{


    t_ballons * monballon;

    draw_sprite(page,reticule,mouse_x,mouse_y);


  if (mouse_b&1){

        for (int i=0;i<NBALLONS;i++)
        {
            monballon=tab[i];
            if ( mouse_x+60 >= monballon->x && mouse_x+60 <= monballon->x + monballon->tx &&
                 mouse_y+60 >= monballon->y && mouse_y+60 <= monballon->y + monballon->ty )
            {
                tab[i]->x=5000;

            }
        }

    }

}







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
    /* rect(page,75,50,155,150,makecol(255, 0, 0));
     rect(page,15,270,165,355,makecol(255, 0, 0));
     rect(page,165,255,250,355,makecol(255, 0, 0));
     rect(page,70,435,155,510,makecol(255, 0, 0));
     rect(page,310,160,360,220,makecol(255, 0, 0));//maison milieu
     rect(page,450,30,565,100,makecol(255, 0, 0));
     rect(page,520,360,630,430,makecol(255, 0, 0));
     rect(page,410,420,460,445,makecol(255, 0, 0)); //tableau
     rect(page,630,190,710,250,makecol(255, 0, 0));
     rect(page,720,10,800,80,makecol(255, 0, 0));
     rect(page,200,550,600,580,makecol(255, 0, 0));//train*/





}


// Dessiner un acteur sur une bitmap bmp
void dessinerActeur(BITMAP *bmp, t_ballons *coincoin)
{
    //rectfill(bmp,coincoin->x,coincoin->y,coincoin->x+coincoin->tx,coincoin->y+coincoin->ty,makecol(255,0,0));
    draw_sprite(bmp,coincoin->pouleto,coincoin->x,coincoin->y);
    //draw_sprite(bmp,coincoin->poulet,coincoin->x,coincoin->y);
}

void dessinerTabActeurs(BITMAP *bmp,t_ballons * tab[NBALLONS])
{
    for (int i=0;i<NBALLONS;i++)
        dessinerActeur(bmp,tab[i]);

}


void finballons(t_ballons* tab[NBALLONS],int* compteur,int* sortie)
{*compteur=0;
    for(int i=0;i<NBALLONS;i++)
    {
        if(tab[i]->x>800 )
        {
            *compteur=*compteur+1;
          printf("%d\n",*compteur);
        }
    }

    if(*compteur==NBALLONS)
    {
        *sortie=1;
    }



}


void mainjeuballons(BITMAP*page)
{
clear(page);

        t_ballons * mesCanards[NBALLONS];

         BITMAP*fond;
         BITMAP*reticule;

        int sortie,compteur;
        int* sortie1=&sortie;
        int* compteur1=&compteur;
         *sortie1=0;
         *compteur1=0;


        reticule=load_bitmap("icone-de-reticule-hghx1j.bmp",NULL);
  if (!reticule) {
        allegro_message("pas pu trouver/charger reticule.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }



         fond=load_bitmap("cicuit course chevaux.bmp", NULL);

    if (!fond) {
        allegro_message("pas pu trouver/charger mon_image.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

remplirTabActeurs(mesCanards);
        while(*sortie1==0)
        {




        // GESTION INTERFACE

        clear_bitmap(page);
        blit(fond,page,0,0,0,0,SCREEN_W,SCREEN_H);
        // DETERMINER NOUVELLEs POSITIONs
        actualiserTabActeurs(mesCanards);

        // AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
        dessinerTabActeurs(page,mesCanards);
        tir(mesCanards,page,reticule);
        finballons(mesCanards,compteur1,sortie1);
        // AFFICHAGE DU BUFFER MIS A JOUR A L'ECRAN
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // ON FAIT UNE PETITE PAUSE
        rest(15);
        }
        allegro_message("fini");
        //free(reticule);
       // free(mesCanards);


}










void choixattraction(int* coorx, int* coory,BITMAP* page)
{
    if((*coorx >75 && *coorx<155) && (*coory>50 && *coory<150))
    {//rect(page,75,50,155,150,makecol(255, 0, 0));
    mainjeuballons(page);
    *coorx=100;
    *coory= 160;

    }


}










int main()
{
    BITMAP *page;
    BITMAP *carte;
    BITMAP *cowboy1;
    int width;


    allegro_init();
    install_keyboard();
    install_mouse();
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
        choixattraction(coorx1,coory1,page);
       // delimitations(page);
        draw_sprite(page,cowboy1, *coorx1 ,*coory1);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        rest(50);
    }


free(page);
free(carte);



    return 0;
}END_OF_MAIN();
