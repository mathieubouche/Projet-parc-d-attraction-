#include <stdio.h>
#include <allegro.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct tcase {
    int x;
    int y;
    bool val;
    int col;
    bool checked;
} t_case;
typedef struct joueur
{
    int x,y;
    BITMAP* cowboy;
    int nbtickets;
    char nom[25];
    int score[9];

}t_joueur;


int genNote(t_case *partition[500][4]) {
    int xnote;
    int temp;
    temp = rand() % 4;
    if (temp == 0) {
        xnote = 250;
        partition[0][0]->val = 1;
    }
    if (temp == 1) {
        xnote = 350;
        partition[0][1]->val = 1;
    }
    if (temp == 2) {
        xnote = 450;
        partition[0][2]->val = 1;
    }
    if (temp == 3) {
        xnote = 550;
        partition[0][3]->val = 1;
    }

    return xnote;
}

void couleursDesFafa(t_case *partition[500][4]) {
    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (partition[i][j]->x == 250) {
                partition[i][j]->col = makecol(255, 0, 0);
            } else if (partition[i][j]->x == 350) {
                partition[i][j]->col = makecol(0, 255, 0);
            } else if (partition[i][j]->x == 450) {
                partition[i][j]->col = makecol(0, 0, 255);
            } else if (partition[i][j]->x == 550) {
                partition[i][j]->col = makecol(255, 255, 0);
            }

        }

    }
}

void genPartition(t_case *partition[500][4]){
    clear(screen);
    BITMAP* fond = load_bitmap("fond.bmp",NULL);
    blit(fond,screen,0,0,0,0,800,600);

    rectfill(screen,250,0,270,500,0);
    rectfill(screen,350,0,370,500,0);
    rectfill(screen,450,0,470,500,0);
    rectfill(screen,550,0,570,500,0);
    hline(screen,250,500,570, makecol(255,0,0));
    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 4; ++j) {
            partition[i][j]->val = 0;
        }
    }
    for (int i = 0; i < 500; ++i) {
        partition[i][0]->y = i;
        partition[i][0]->x = 250;
    }
    for (int i = 0; i < 500; ++i) {
        partition[i][1]->y = i;
        partition[i][1]->x = 350;
    }
    for (int i = 0; i < 500; ++i) {
        partition[i][2]->y = i;
        partition[i][2]->x = 450;
    }
    for (int i = 0; i < 500; ++i) {
        partition[i][3]->y = i;
        partition[i][3]->x = 550;
    }

    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 4; ++j) {
            partition[i][j]->checked = false;
        }

    }


}

void afnote(t_case *partition[500][4]) {


    BITMAP* croche= load_bitmap("croche.bmp",NULL);
    BITMAP* doublecroche= load_bitmap("double_croche.bmp",NULL);


    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (partition[i][j]->val == 1) {
                rectfill(screen, partition[i-1][j]->x, partition[i-1][j]->y, partition[i-1][j]->x + 20,
                         partition[i-1][j]->y + 20,0);

                draw_sprite(screen,(j%2==0)?croche:doublecroche,partition[i][j]->x,partition[i][j]->y);


                //rectfill(screen, partition[i][j]->x, partition[i][j]->y, partition[i][j]->x + 20,
                //partition[i][j]->y + 20,partition[i][j]->col);
            }


        }
    }

}

int glissement(t_case *partition[500][4]) {
    int tempo[500][4];

    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 4; ++j) {
            tempo[i][j] = partition[i][j]->val;
            partition[i][j]->val = 0;
        }
    }
    for (int i = 1; i < 500; ++i) {
        for (int j = 0; j < 4; ++j) {
            partition[i][j]->val = tempo[i - 1][j];

        }
    }

    for (int i = 0; i < 4; ++i) {
        if(partition[499][i]->val==1)
            return 0;
    }
    return 1;
}

int verif(t_case *partition[500][4]) {
    int y_max = -1;
    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (partition[i][j]->val == 1) {
                y_max = (i > y_max) ? i : y_max;   // connaissance de l'opérateur ternaire vient de gpt
            }
        }
    }
    return y_max;
}


int main() {
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0) != 0) {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }





    srand(time(NULL));

    t_case *partition[500][4];
    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 4; ++j) {
            partition[i][j] = (t_case *) malloc(sizeof(t_case));
        }
    }


    int cpt = 0;
    int y_max;
    int tobogan=1;
    int tour1 = 1;
    t_joueur joueur1;
    t_joueur joueur2;

    scanf("%s",joueur1.nom);
    scanf("%s",joueur2.nom);

    allegro_message("appuyer sur les touches pour éliminer les notes");
    allegro_message("respectivement: g, h, j, et k");
    allegro_message("appuyer très brièvement sur les touches, elles sont giga sensibles ;)");
    allegro_message("tour de %s",joueur1.nom);

    float tps1J1;
    float tps2J1;
    float tps1;
    float tps1J2;
    float tps2J2;
    float tps2;

    genPartition(partition);
    tps1J1=clock();
    while (tour1 == 1) {


        if (cpt % 50 == 1)
            genNote(partition);
        tobogan= glissement(partition);
        if(tobogan==0) {tour1 = 0;allegro_message("perdu!!");}
        couleursDesFafa(partition);
        afnote(partition);



        if(key[KEY_G]){
            y_max= verif(partition);
            if(partition[y_max][0]->val==1 && partition[y_max][0]->checked==false){
                partition[y_max][0]->val=0;
                partition[y_max][0]->checked=true;
                rectfill(screen,partition[y_max-1][0]->x,partition[y_max-1][0]->y,partition[y_max-1][0]->x+20,partition[y_max-1][0]->y+21,0);
                rest(25);
            }
            else if(partition[y_max][0]->val==0){
                allegro_message("perdu!!");
                tour1=0;
            }

        }
        else if(key[KEY_H]){
            y_max= verif(partition);
            if(partition[y_max][1]->val==1 && partition[y_max][1]->checked==false){
                partition[y_max][1]->val=0;
                partition[y_max][1]->checked=true;
                rectfill(screen,partition[y_max-1][1]->x,partition[y_max-1][1]->y,partition[y_max-1][1]->x+20,partition[y_max-1][1]->y+21,0);
                rest(25);
            }
            else if(partition[y_max][1]->val==0){
                allegro_message("perdu!!");
                tour1=0;
            }

        }
        else if(key[KEY_J]){
            y_max= verif(partition);
            if(partition[y_max][2]->val==1 && partition[y_max][2]->checked==false){
                partition[y_max][2]->val=0;
                partition[y_max][2]->checked=true;
                rectfill(screen,partition[y_max-1][2]->x,partition[y_max-1][2]->y,partition[y_max-1][2]->x+20,partition[y_max-1][2]->y+21,0);
                rest(25);
            }
            else if(partition[y_max][2]->val==0){
                allegro_message("perdu!!");
                tour1=0;
            }
        }
        else if(key[KEY_K]){
            y_max= verif(partition);
            if(partition[y_max][3]->val==1 && partition[y_max][3]->checked==false){
                partition[y_max][3]->val=0;
                partition[y_max][3]->checked=true;
                rectfill(screen,partition[y_max-1][3]->x,partition[y_max-1][3]->y,partition[y_max-1][3]->x+20,partition[y_max-1][3]->y+21,0);
                rest(25);
            }
            else if(partition[y_max][3]->val==0){
                allegro_message("perdu!!");
                tour1=0;
            }
        }

        cpt++;
        rest(1);


    }
    tps2J1=clock();
    tps1=tps2J1-tps1J1;


    allegro_message("tour de %s",joueur2.nom);
    genPartition(partition);
    int tour2=1;
    int tobogan2=1;
    tps1J2=clock();
    while (tour2 == 1) {


        if (cpt % 50 == 1)
            genNote(partition);
        tobogan2= glissement(partition);
        if(tobogan2==0) {tour2 = 0;allegro_message("perdu!!");}
        couleursDesFafa(partition);
        afnote(partition);



        if(key[KEY_G]){
            y_max= verif(partition);
            if(partition[y_max][0]->val==1 && partition[y_max][0]->checked==false){
                partition[y_max][0]->val=0;
                partition[y_max][0]->checked=true;
                rectfill(screen,partition[y_max-1][0]->x,partition[y_max-1][0]->y,partition[y_max-1][0]->x+20,partition[y_max-1][0]->y+21,0);
                rest(25);
            }
            else if(partition[y_max][0]->val==0){
                allegro_message("perdu!!");
                tour2=0;
            }

        }
        else if(key[KEY_H]){
            y_max= verif(partition);
            if(partition[y_max][1]->val==1 && partition[y_max][1]->checked==false){
                partition[y_max][1]->val=0;
                partition[y_max][1]->checked=true;
                rectfill(screen,partition[y_max-1][1]->x,partition[y_max-1][1]->y,partition[y_max-1][1]->x+20,partition[y_max-1][1]->y+21,0);
                rest(25);
            }
            else if(partition[y_max][1]->val==0){
                allegro_message("perdu!!");
                tour2=0;
            }

        }
        else if(key[KEY_J]){
            y_max= verif(partition);
            if(partition[y_max][2]->val==1 && partition[y_max][2]->checked==false){
                partition[y_max][2]->val=0;
                partition[y_max][2]->checked=true;
                rectfill(screen,partition[y_max-1][2]->x,partition[y_max-1][2]->y,partition[y_max-1][2]->x+20,partition[y_max-1][2]->y+21,0);
                rest(25);
            }
            else if(partition[y_max][2]->val==0){
                allegro_message("perdu!!");
                tour2=0;
            }
        }
        else if(key[KEY_K]){
            y_max= verif(partition);
            if(partition[y_max][3]->val==1 && partition[y_max][3]->checked==false){
                partition[y_max][3]->val=0;
                partition[y_max][3]->checked=true;
                rectfill(screen,partition[y_max-1][3]->x,partition[y_max-1][3]->y,partition[y_max-1][3]->x+20,partition[y_max-1][3]->y+21,0);
                rest(25);
            }
            else if(partition[y_max][3]->val==0){
                allegro_message("perdu!!");
                tour2=0;
            }
        }

        cpt++;
        rest(1);


    }
    tps2J2=clock();
    tps2=tps2J2-tps1J2;


    allegro_message("%s a gagné!!",(tps1>tps2) ? joueur1.nom : joueur2.nom);
    (tps1>tps2) ? joueur1.nbtickets++ : joueur2.nbtickets++;

    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 4; ++j) {
            free(partition[i][j]);
        }
    }
    readkey();
    return 0;
}

END_OF_MAIN()
