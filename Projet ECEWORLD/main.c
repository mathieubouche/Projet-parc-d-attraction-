#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#define NBALLONS 18

typedef struct ballons
{
    int x, y;    // coordonnée (du coin sup. gauche)
    int dx, dy;// vecteur deplacement
    int tx, ty;
    BITMAP* poulet;
    BITMAP* pouleto;

}t_ballons;

typedef struct joueur
{
    int x,y;
    BITMAP* cowboy;
    int nbtickets;
    char nom[25];
    int score[9];

}t_joueur;







void vecDepAleaActeur(t_ballons *coincoin,int* choix)
{
   if(*choix==1)
    {do
    {int z;
        z=rand()%4;
        coincoin->dx = rand()%4;
        coincoin->dy = rand()%4;
         if(z==0)
        { coincoin->dx=- coincoin->dx;
          coincoin->dy=- coincoin->dy;
        }



        if(z==1)
        { coincoin->dx=- coincoin->dx;

        }
         if(z==2)
        { coincoin->dy=- coincoin->dy;

        }

    }
    while (coincoin->dx==0 || coincoin->dy==0);}
   if(*choix==2)
   {do
    {
        coincoin->dx =rand()%5 ;

    }
    while (coincoin->dx==0) ;}
}





t_ballons * creerballons (int*choix)
{
    t_ballons *ballon;

    ballon = (t_ballons*)malloc(1*sizeof(t_ballons));
    int z=0;
    if(*choix==1)
   {ballon->tx = 50;
    ballon->ty = 50;
    ballon->poulet = load_bitmap("10-ballons-de-baudruche-en-latex-opaque-rouge_88620_1.bmp", NULL);
    ballon->pouleto = create_bitmap(50,50);
    stretch_blit(ballon->poulet, ballon->pouleto,0,0,ballon->poulet->w,ballon->poulet->h,0,0,ballon->pouleto->w,ballon->pouleto->h);
    ballon->x = rand()%(SCREEN_W - ballon->tx);
    ballon->y = rand()%(SCREEN_H - ballon->ty);
    vecDepAleaActeur(ballon,choix);
    }

    if(*choix==2)
    {ballon->tx = 60;
    ballon->ty = 60;
    ballon->poulet = load_bitmap("photo planche.bmp", NULL);
    if (! ballon->poulet)
    {
        allegro_message("pas pu trouver images/carte.bmp");
        exit(EXIT_FAILURE);
    }
    ballon->pouleto = create_bitmap(60,60);
    stretch_blit(ballon->poulet, ballon->pouleto,0,0,ballon->poulet->w,ballon->poulet->h,0,0,ballon->pouleto->w,ballon->pouleto->h);
    ballon->x = rand()%(SCREEN_W - ballon->tx);
    vecDepAleaActeur(ballon,choix);
    z=rand()%5;
    if(z==0)
    {ballon->y=125;

    }
     if(z==1)
    {ballon->y=185;

    }
     if(z==2)
    {ballon->y=245;

    } if(z==3)
    {ballon->y=305;

    }
     if(z==4)
    {ballon->y=365  ;

    }

    }
    return ballon;
}

void remplirTabActeurs(t_ballons * tab[NBALLONS],int* choix)
{
    // On "accroche" NACTEUR nouveaux acteurs
    // à chaque case du tableau

    for (int i=0;i<NBALLONS;i++)
        tab[i]=creerballons(choix);



}


void actualiserActeur(t_ballons *coincoin,int* choix)
{int z;
    // contrôle des bords : ici on décide de rebondir sur les bords
 if(*choix==1){

        z=rand()%20;
        if(z==19)
        {vecDepAleaActeur(coincoin,choix);}
        if  (  ( coincoin->x < 0 && coincoin->dx < 0 ) || ( coincoin->x + coincoin->tx > SCREEN_W && coincoin->dx > 0) )
        coincoin->dx = -coincoin->dx;

        if  (  ( coincoin->y < 0 && coincoin->dy < 0 ) || ( coincoin->y + coincoin->ty > SCREEN_H && coincoin->dy > 0) )
        coincoin->dy = -coincoin->dy;


    coincoin->x = coincoin->x + coincoin->dx;
    coincoin->y = coincoin->y + coincoin->dy;
    }
    if(*choix==2)
    { coincoin->x = coincoin->x + coincoin->dx;
      if(coincoin->x>SCREEN_W)
      {
          coincoin->x=0;
          z=rand()%5;
    if(z==0)
    {coincoin->y=125;

    }
     if(z==1)
    {coincoin->y=185;

    }
     if(z==2)
    {coincoin->y=245;

    } if(z==3)
    {coincoin->y=305;

    }
     if(z==4)
    {coincoin->y=365  ;

    }


      }
    }

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
void actualiserTabActeurs(t_ballons * tab[NBALLONS],int* choix)
{
    int i,j,cote;

    // Contrôle des collisions : si on entre en collision avec un autre
    // et que la collision tend à nous rapprocher alors on rebondit
   if(choix==1)
    { for (i=0;i<NBALLONS;i++)
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
}
    // Gérer les déplacements habituels...
    for (i=0;i<NBALLONS;i++)
        actualiserActeur(tab[i],choix);

}


void tir(t_ballons * tab[NBALLONS],BITMAP*page,BITMAP*reticule)
{
    t_ballons * monballon;
    draw_sprite(page,reticule,mouse_x,mouse_y);
    if (mouse_b&1)
    {
        for (int i=0;i<NBALLONS;i++)
        {monballon=tab[i];
            if ( mouse_x+30 >= monballon->x && mouse_x+30 <= monballon->x + monballon->tx &&
                 mouse_y+30 >= monballon->y && mouse_y+30 <= monballon->y + monballon->ty )
               {
                tab[i]->x=5000;
                }
        }

    }

}







void deplacements(t_joueur* joueur,int* choix)
{int i;
    if(*choix==0)
    {
        i=7;
    }
     if(*choix==2)
    {
        i=14;
    }

        if (key[KEY_UP])
        {joueur->y=joueur->y-i;
        }
        if (key[KEY_DOWN])
        {joueur->y=joueur->y+i;
        }
        if (key[KEY_RIGHT])
        {joueur->x=joueur->x+i;
        }
        if (key[KEY_LEFT])
        {joueur->x=joueur->x-i;
        }
        if(joueur->y>SCREEN_H-50)
        {joueur->y=SCREEN_H-50;
        }
        if(joueur->y<0)
        {joueur->y=0;
        }
        if(joueur->x<0)
        {joueur->x=0;
        }
    if(joueur->x>SCREEN_W-30)
        {joueur->x=SCREEN_W-30;
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
         // printf("%d\n",*compteur);
        }
    }

    if(*compteur==NBALLONS)
    {
        *sortie=1;
    }



}


void mainjeuballons(BITMAP*page,int* choix)
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

remplirTabActeurs(mesCanards,choix);
        while(*sortie1==0)
        {

        // GESTION INTERFACE

        clear_bitmap(page);
        blit(fond,page,0,0,0,0,SCREEN_W,SCREEN_H);
        // DETERMINER NOUVELLEs POSITIONs
        actualiserTabActeurs(mesCanards,choix);

        // AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
        dessinerTabActeurs(page,mesCanards);
        tir(mesCanards,page,reticule);
        finballons(mesCanards,compteur1,sortie1);
        // AFFICHAGE DU BUFFER MIS A JOUR A L'ECRAN
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // ON FAIT UNE PETITE PAUSE
        rest(15);
        }

        //free(reticule);
       // free(mesCanards);


}




void actuliserdeppersorondin(t_joueur* joueur,t_ballons*tab[NBALLONS],BITMAP*page)
{
int z=0;

    for( int i=0;i<NBALLONS;i++)
    {
        //rect(page,tab[i]->x,tab[i]->y,tab[i]->x+tab[i]->tx,tab[i]->y+tab[i]->ty,makecol(255, 0, 0));
        if(  ((joueur->x>tab[i]->x-7 && joueur->x<tab[i]->x+tab[i]->tx-7) || (joueur->x+30>tab[i]->x-7 && joueur->x+30<tab[i]->x+tab[i]->tx+7))&&  (joueur->y+37>tab[i]->y-7 && joueur->y+37<tab[i]->y+tab[i]->ty+7) )
        {   z=1;
            joueur->x=joueur->x+tab[i]->dx;



           //rect(page,joueur->x+10,joueur->y,joueur->x+30,joueur->y+36,makecol(255, 0, 0));

           break;

        }

        }

        if((joueur->y+37 >150 && joueur->y+37<425) && z==0   )
           {
                joueur->y=550;
               // rect(page,joueur->x+10,joueur->y,joueur->x+30,joueur->y+36,makecol(0, 255, 0));

           }


   printf("%d\n",z);



}




void mainjeuriviere(BITMAP*page,int *choix)
{ int test;
        t_joueur * j;
        j=(t_joueur*)malloc(sizeof(t_joueur));
        j->x=400;
        j->y=670;
        t_ballons * mesrondins[NBALLONS];
        remplirTabActeurs(mesrondins,choix);
        //allegro_message("ici");
         BITMAP*fond;
         BITMAP*elargi;
         fond=load_bitmap("map traversee riviere.bmp",NULL);
          if (!fond)
    {
        allegro_message("pas pu trouver images/carte.bmp");
        exit(EXIT_FAILURE);
    }
     elargi = create_bitmap(800,600);
    stretch_blit(fond, elargi,0,0,fond->w,fond->h,0,0,elargi->w,elargi->h);

 j->cowboy =load_bitmap("cowboytest.bmp",NULL);
  if (!j->cowboy)
    {
        allegro_message("pas pu trouver images/carte.bmp");
        exit(EXIT_FAILURE);
    }





         while(j->y>50)
         { clear_bitmap(page);

           deplacements(j,choix);

           blit(elargi,page,0,0,0,0,SCREEN_W,SCREEN_H);

           actuliserdeppersorondin(j,mesrondins,page);
           actualiserTabActeurs(mesrondins,choix);


           dessinerTabActeurs(page,mesrondins);



          // rect(page,0,150,800,425,makecol(255, 0, 0));
           draw_sprite(page,j->cowboy,j->x,j->y);

          // printf("%d\n",mesrondins[3]->x);
           blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
           rest(100);

         }





}


void tourfonc(int*tour)
{ *tour=*tour+1;

    if (*tour>1)
    {
        *tour=0;

    }

}



void choixattraction(BITMAP* page,int* tour,t_joueur* j1,t_joueur* j2,int*choix)
{rect(page,15,270,165,355,makecol(255, 0, 0));
    if((j1->x >75 && j1->x<155) && (j1->y>50 && j1->y<150)||(j2->x >75 && j2->x<155) && (j2->y>50 && j2->y<150))
    {//rect(page,75,50,155,150,makecol(255, 0, 0));
    *choix=1;
    allegro_message("tour de %s",j1->nom);
    mainjeuballons(page,choix);

    if((j1->x >75 && j1->x<155) && (j1->y>50 && j1->y<150))
    {j1->x=0;
    j1->y= 0;}
    if((j2->x >75 && j2->x<155) && (j2->y>50 && j2->y<150))
    {j2->x=0;
    j2->y= 0;
    }
    tourfonc(tour);
    allegro_message("tour de: %s",j2->nom);
    mainjeuballons(page,choix);
    *choix=0;
    }

     if((j1->x >15 && j1->x<165) && (j1->y>270 && j1->y<355 )||(j2->x >15 && j2->x<165) && (j2->y>270 && j2->y<355))
    {
    allegro_message("tour de: %s",j1->nom);
    *choix=2;
    mainjeuriviere(page,choix);
    if((j1->x >15 && j1->x<165) && (j1->y>270 && j1->y<355 ))
    {j1->x=0;
    j1->y= 0;}
    if((j2->x >15 && j2->x<165) && (j2->y>270 && j2->y<355))
    {j2->x=0;
     j2->y= 0;
    }
    allegro_message("tour de: %s",j2->nom);
    mainjeuriviere(page,choix);
    tourfonc(tour);
    *choix=0;
    }


}










int main()
{
    t_joueur * joueur1;
    t_joueur * joueur2;
    int choi=0;
    int* choix=&choi;

    printf("joueur 1 entrez votre nom\n");
    joueur1=(t_joueur*)malloc(sizeof(t_joueur));
    fgets(joueur1->nom, 25, stdin);

    printf("joueur 2 entrez votre nom\n");
    joueur2=(t_joueur*)malloc(sizeof(t_joueur));
    fgets(joueur2->nom, 25, stdin);

    BITMAP *page;
    BITMAP *carte;
    BITMAP *cowboy1;
    int width;


    allegro_init();
    install_keyboard();
    install_mouse();
    joueur1->x=400;
    joueur1->y=475;
    joueur2->x=350;
    joueur2->y=475;


    int tour=0;
    int* tour1=&tour;

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
 joueur1->cowboy=load_bitmap("cowboytest.bmp",NULL);
    if (!joueur1->cowboy)
    {
        allegro_message("pas pu trouver images/cowboy1.bmp");
        exit(EXIT_FAILURE);
    }


    joueur2->cowboy=load_bitmap("cowboytest.bmp",NULL);
    if (! joueur2->cowboy)
    {
        allegro_message("pas pu trouver images/cowboy1.bmp");
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

    clear_bitmap(page);






    while(!key[KEY_ESC])
    {
        clear_bitmap(page);
        blit(carte,page,0,0,0,0,SCREEN_W,SCREEN_H);



        choixattraction(page,tour1,joueur1,joueur2,choix);
          if(*tour1==1)
       {deplacements(joueur1,choix);

       }

        if(*tour1==0)
       {deplacements(joueur2,choix);

       }

       // delimitations(page);
        draw_sprite(page,joueur1->cowboy,joueur1->x,joueur1->y);
        draw_sprite(page,joueur2->cowboy,joueur2->x,joueur2->y);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        rest(50);
    }


free(page);
free(carte);



    return 0;
}END_OF_MAIN();
