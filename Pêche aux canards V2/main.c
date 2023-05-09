#include <stdio.h>
#include <allegro.h>
#include <time.h>
#define NCANARD 10


typedef struct joueur
{
    int x,y;
    BITMAP* cowboy;
    int nbtickets;
    char nom[25];
    int score;

}t_joueur;

typedef struct canard
{
    int x, y;    // coordonnée (du coin sup. gauche)
    int dx, dy;// vecteur deplacement
    int tx, ty;
    BITMAP* poulet;
    BITMAP* pouleto;

}t_canard;




// (ré)initialiser vecteur déplacement aléatoire avec composantes non nulles
void vecDepAleaActeur(t_canard *coincoin)
{
    do
    {
        coincoin->dx = rand()%3;
        coincoin->dy = rand()%3;
    }
    while (coincoin->dx==0 || coincoin->dy==0);
}


t_canard * creerCanard ()
{
    t_canard *coincoin;

    coincoin = (t_canard*)malloc(1*sizeof(t_canard));
    coincoin->poulet = load_bitmap("C:\\Users\\eldou\\12\\Parc d'attraction\\Nom du jeu\\canard.bmp", NULL);
    coincoin->pouleto = create_bitmap(50,50);
    stretch_blit(coincoin->poulet, coincoin->pouleto,0,0,coincoin->poulet->w,coincoin->poulet->h,0,0,coincoin->pouleto->w,coincoin->pouleto->h);

    coincoin->tx = rand()%140+40;
    coincoin->ty = rand()%140+40;

    do {
        coincoin->x = rand() % (800 - coincoin->tx);
        coincoin->y = rand() % (600 - coincoin->ty);
    }while (coincoin->x < 415 && coincoin->y < 207);


    vecDepAleaActeur(coincoin);

    return coincoin;
}



void remplirTabActeurs(t_canard * tab[NCANARD])
{
    // On "accroche" NACTEUR nouveaux acteurs
    // à chaque case du tableau
    for (int i=0;i<NCANARD;i++)
        tab[i]=creerCanard();
}



int actualiserActeur(t_canard *coincoin, int scoreJ1)
{

    t_joueur *j1;
    t_joueur *j2;
    scoreJ1 == j1->score;

    // contrôle des bords : ici on décide de rebondir sur les bords
    if  (  ( coincoin->x < 0 && coincoin->dx < 0 ) || ( coincoin->x + coincoin->tx > 815 && coincoin->dx > 0) )
        coincoin->dx = -coincoin->dx;

    if  (  ( coincoin->y < 0 && coincoin->dy < 0 ) || ( coincoin->y + coincoin->ty > 600 && coincoin->dy > 0) )
        coincoin->dy = -coincoin->dy;



    if(mouse_b & 1) {
        if (mouse_x == coincoin->x && mouse_y == coincoin->y)

        {

            return 1;

            if ((coincoin->x < 435 && coincoin->dx < 0) && (coincoin->y < 225 && coincoin->dy < 0)) {
                coincoin->dx = coincoin->dx;
                coincoin->dy = coincoin->dy;
                scoreJ1++;

            }

        }
    }

    else {
            if ((coincoin->x <= 415 && coincoin->dx < 0) && (coincoin->y <= 207 && coincoin->dy < 0)) {
                coincoin->dx = -coincoin->dx;
                coincoin->dy = -coincoin->dy;
            }
        }


    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    coincoin->x = coincoin->x + coincoin->dx;
    coincoin->y = coincoin->y + coincoin->dy;

    return scoreJ1;

}





// Déterminer si les rectangles de 2 acteurs s'intersectent
// Retourne 0 si pas de collision
// Si collision alors retourne une valeur selon la position de a2 par rapport à a1
// 1 : plutôt à droite   2 : plutôt à gauche   3 : plutôt en bas   4 : plutôt en haut
int collisionActeurs(t_canard *a1, t_canard *a2)
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
void actualiserTabActeurs(t_canard * tab[NCANARD], int scoreJ1)
{
    int i,j,cote,appuye,mathieu;


    // Gérer les déplacements habituels...
    for (i=0;i<NCANARD;i++) {
        appuye = actualiserActeur(tab[i],scoreJ1);
        if (appuye == 1)
        {
            mathieu = i;
        }
    }


    // Contrôle des collisions : si on entre en collision avec un autre
    // et que la collision tend à nous rapprocher alors on rebondit
    for (i=0;i<NCANARD;i++) {
        if (appuye == 1) {
            if (i == mathieu - 1) {
                i = i + 2;
            }
        }
        for (j = i + 1; j < NCANARD; j++) {
            if (appuye == 1) {
                if (i == mathieu - 1) {
                    i = i + 2;
                }
            }
            if ((cote = collisionActeurs(tab[i], tab[j]))) {
                if ((cote == 1 && tab[i]->dx < 0) || (cote == 2 && tab[i]->dx > 0))
                    tab[i]->dx = -tab[i]->dx;
                if ((cote == 3 && tab[i]->dy < 0) || (cote == 4 && tab[i]->dy > 0))
                    tab[i]->dy = -tab[i]->dy;
                if ((cote == 1 && tab[j]->dx > 0) || (cote == 2 && tab[j]->dx < 0))
                    tab[j]->dx = -tab[j]->dx;
                if ((cote == 3 && tab[j]->dy > 0) || (cote == 4 && tab[j]->dy < 0))
                    tab[j]->dy = -tab[j]->dy;
            }
        }
    }




}



void interfaceTabActeurs(t_canard * tab[NCANARD])
{
    int i,mmx,mmy;
    t_canard *coincoin;

    // ESPACE pour figer tous les acteurs
    if (key[KEY_SPACE]){
        for (i=0;i<NCANARD;i++)
        {
            tab[i]->dx=0;
            tab[i]->dy=0;
        }
    }

    // ENTREE pour réinitialiser déplacement aléatoire tous les acteurs
    if (key[KEY_ENTER]){
        for (i=0;i<NCANARD;i++)
            vecDepAleaActeur(tab[i]);
    }


    // Mouvement mouse depuis le dernier appel à get_mouse_mickeys ?
    get_mouse_mickeys(&mmx,&mmy);

    // Si on clique et qu'un des rectangles est sous la souris,
    // on met son déplacement identique à celui de la souris
    if (mouse_b&1){

        for (i=0;i<NCANARD;i++)
        {
            coincoin=tab[i];
            if ( mouse_x >= coincoin->x && mouse_x <= coincoin->x + coincoin->tx &&
                 mouse_y >= coincoin->y && mouse_y <= coincoin->y + coincoin->ty )
            {

                coincoin->dx=mmx;
                coincoin->dy=mmy;
            }
        }

    }
}



// Dessiner un acteur sur une bitmap bmp
void dessinerActeur(BITMAP *bmp, t_canard *coincoin)
{
    draw_sprite(bmp,coincoin->pouleto,coincoin->x,coincoin->y);
}



void dessinerTabActeurs(BITMAP *bmp,t_canard * tab[NCANARD])
{
    for (int i=0;i<NCANARD;i++)
        dessinerActeur(bmp,tab[i]);

}



void affichage(BITMAP *titre, BITMAP *bmp, int xT, int yT, int xC, int yC, int x1R, int x2R, int y1R, int y2R,int xJ1,int yJ1, int xJ2, int yJ2)
{

    draw_sprite(bmp, titre, xT, yT); // Afficher l'image sur l'écran aux coordonnées (x, y)
    textout_ex(bmp, font, "CLIQUEZ ICI !", xC, yC, makecol(255, 0, 0), -1);
    rect(bmp, x1R, y1R, x2R, y2R, makecol(255, 0, 0));
    textout_ex(bmp, font, "JOUEUR 1 ", xJ1, yJ1, makecol(255, 255, 255), -1);
    textout_ex(bmp, font, "JOUEUR 2 ", xJ2, yJ2, makecol(255, 255, 255), -1);
}





int main() {

    t_canard * mesCanards[NCANARD];

    BITMAP *eau;
    BITMAP *poulet;
    BITMAP *pouleto;
    BITMAP *titre;
    int z = 1;
    int scoreJ1 = 0;

    int xT = 300;
    int yT = 200;
    int xC = 483;
    int yC =300;
    int x1R = 475;
    int x2R = 592;
    int y1R = 290;
    int y2R = 315;
    int xJ1 = 500;
    int yJ1 = 350;
    int xJ2 = 500;
    int yJ2 = 400;
    int score = 0;

    BITMAP *page;
    srand(time(NULL));

    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1100, 600, 0, 0) != 0) {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    show_mouse(screen);



    page=create_bitmap(800,600);
    clear_bitmap(page);


    eau = load_bitmap("C:\\Users\\eldou\\12\\Parc d'attraction\\Jeu\\map.bmp", NULL);

    titre = load_bitmap("C:\\Users\\eldou\\12\\Parc d'attraction\\Nom du jeu\\pECHE AUX CANARDS.bmp",NULL);

    if (!eau) {
        allegro_message("pas pu trouver/charger mon_image.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    if (!titre) {
        allegro_message("pas pu trouver/charger mon_image.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }



    while( z == 1 )
    {
        if(key[KEY_ESC])
        {
            allegro_exit();
        }

        else {
            affichage(titre, screen, xT, yT, xC, yC, x1R, x2R, y1R, y2R, xJ1, yJ1, xJ2, yJ2);


            if (mouse_b & 1) {
                z = 2;
            }


        }}

    clear_to_color(screen, makecol(0, 0, 0));

    remplirTabActeurs(mesCanards);

    time_t start_time, current_time;
    start_time = time(NULL); // temps de départ
    int s = 60;



    while (z==2 && s>0)
    {

        if(key[KEY_ESC])
        {
            allegro_exit();
        }

        else {

                current_time = time(NULL); // temps actuel
                int elapsed_time = (int)difftime(current_time, start_time); // temps écoulé depuis le départ, converti en entier
                s = 60 - elapsed_time;

                //clear_to_color(screen, makecol(0, 0, 0)); // efface l'écran
                textprintf_centre_ex(screen, font, 600, 50, makecol(255, 0, 0), -1, "Temps restant: %d s", s); // affiche le temps écoulé
                textprintf_ex(screen, font, 600, 200, makecol(255, 0, 0), -1,"Score J1 : %d", scoreJ1);
                rest(10); // pause pour réduire l'utilisation du processeur



            // EFFACER POSITIONs ACTUELLEs SUR LE BUFFER
            clear_to_color(page, makecol(255, 0, 255));



            blit(eau, page, 0, 0, 0, 0, 800, 600);


            // GESTION INTERFACE
            interfaceTabActeurs(mesCanards);

            // DETERMINER NOUVELLEs POSITIONs
            actualiserTabActeurs(mesCanards, scoreJ1);



            //attrapeTab(mesCanards);

            // AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
            dessinerTabActeurs(page, mesCanards);


            // AFFICHAGE DU BUFFER MIS A JOUR A L'ECRAN
            blit(page, screen, 0, 0, 0, 0, 800, 600);

            // ON FAIT UNE PETITE PAUSE
            //rest(15);


        }}

    clear_bitmap(screen);

    while (s<=0)
    {

        if(key[KEY_ESC])
        {
            allegro_exit();
        }

        textout_ex(screen, font,"SGSGSGDGDHDHD",500,200,makecol(255,0,0),-1);
        //rest(15);
    }

    allegro_exit();

    return 0;
}END_OF_MAIN();
