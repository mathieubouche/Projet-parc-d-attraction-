#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro.h>

#define size 41

typedef struct {
    int val;
    int pos_x;
    int pos_y;
} t_case;

typedef struct joueur
{
    int x,y;
    BITMAP* cowboy;
    int nbtickets;
    char nom[25];
    int score[9];

}t_joueur;


void cassemur(t_case *grid[size][size]) {
    // on parcourt la grille, si la case est un mur, il a 1 chance sur 100 d'être transformé en passage, dans le main on appele cassmur 100 fois
    for (int i = 1; i < size - 1; ++i) {
        for (int j = 1; j < size - 1; ++j) {
            int prob = rand() % 100 + 1;

            if (i % 2 == 0 && j % 2 == 0)
                continue;
            if (grid[i][j]->val == 0) {
                if (prob == 1) {

                    grid[i][j]->val = 1;
                }
            }

        }

    }
}

int choixDepart(t_case *grid[size][size]) {
    int y = (rand() % 10 + 1) + 5;

    grid[y][0]->val = -2;
    //mise en place d'un rectangle de 7 par 3 a cote de l'entree pour eviter des murs inopportuns
    grid[y - 3][1]->val = 1;
    grid[y - 2][1]->val = 1;
    grid[y - 1][1]->val = 1;
    grid[y][1]->val = 1;
    grid[y + 3][1]->val = 1;
    grid[y + 2][1]->val = 1;
    grid[y + 1][1]->val = 1;
    grid[y - 3][2]->val = 1;
    grid[y - 2][2]->val = 1;
    grid[y - 1][2]->val = 1;
    grid[y][2]->val = 1;
    grid[y + 3][2]->val = 1;
    grid[y + 2][2]->val = 1;
    grid[y + 1][2]->val = 1;
    grid[y - 3][3]->val = 1;
    grid[y - 2][3]->val = 1;
    grid[y - 1][3]->val = 1;
    grid[y][3]->val = 1;
    grid[y + 3][3]->val = 1;
    grid[y + 2][3]->val = 1;
    grid[y + 1][3]->val = 1;
    return y;
}

int choixArrivee(t_case *grid[size][size]) {
    int y = (rand() % 10 + 1) + 25;

    grid[y][40]->val = -2;
    //mise en place d'un rectangle de 7 par 3 a cote de l'arrivee pour eviter des murs inopportuns
    grid[y - 3][37]->val = 1;
    grid[y - 2][37]->val = 1;
    grid[y - 1][37]->val = 1;
    grid[y][37]->val = 1;
    grid[y + 3][37]->val = 1;
    grid[y + 2][37]->val = 1;
    grid[y + 1][37]->val = 1;
    grid[y - 3][38]->val = 1;
    grid[y - 2][38]->val = 1;
    grid[y - 1][38]->val = 1;
    grid[y][38]->val = 1;
    grid[y + 3][38]->val = 1;
    grid[y + 2][38]->val = 1;
    grid[y + 1][38]->val = 1;
    grid[y - 3][39]->val = 1;
    grid[y - 2][39]->val = 1;
    grid[y - 1][39]->val = 1;
    grid[y][39]->val = 1;
    grid[y + 3][39]->val = 1;
    grid[y + 2][39]->val = 1;
    grid[y + 1][39]->val = 1;

    return y;
}


void blito(t_case *grid[size][size], BITMAP *lab) {
    BITMAP *log = load_bitmap("log.bmp", NULL);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (grid[i][j]->val == 0) {
                draw_sprite(lab, log, grid[i][j]->pos_x, grid[i][j]->pos_y);
            }
        }
    }
    destroy_bitmap(log);
}

void genLab(t_case *grid[size][size], BITMAP *lab) {
    //mise en place de la grille du style:
    //# # # # # # #
    //#   #   #   #
    //# # # # # # #
    //#   #   #   #
    //# # # # # # #
    // avec mur=0 et passage=1
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i % 2 == 0) {
                grid[i][j]->val = 0;
                grid[i][j]->pos_x = 200 + (j * 10);
                grid[i][j]->pos_y = 100 + (i * 10);
            } else if (i % 2 == 1 && j % 2 == 0) {
                grid[i][j]->val = 0;
                grid[i][j]->pos_x = 200 + (j * 10);
                grid[i][j]->pos_y = 100 + (i * 10);
            } else if (i % 2 == 1 && j % 2 == 1) {
                grid[i][j]->val = 1;
                grid[i][j]->pos_x = 200 + (j * 10);
                grid[i][j]->pos_y = 100 + (i * 10);
            }
        }
    }
    for (int k = 0; k < 100; k++) {
        cassemur(grid);
    }
}

int victoire(int y,int x, int ya){
    if (y==ya && x==40)
        return 1;
    else
        return 0;
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

    t_joueur joueur1;
    t_joueur joueur2;



    // but du jeu
    allegro_message("le but du jeu suivant est de résoudre en un minimum de deplacement le labyrinte, il est identique pour les 2 joueurs");


    BITMAP *fond = load_bitmap("fond.bmp", NULL);
    BITMAP *lab;
    lab = create_bitmap(800, 600);
    blit(fond, lab, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    srand(time(NULL));

    t_case *grid[size][size];
    for (int i = 0; i < size; i++) { // allocation de la grille de base
        for (int j = 0; j < size; j++) {
            grid[i][j] = (t_case *) malloc(sizeof(t_case));
        }
    }
    int yd, ya;// position verticale d'arrivée et de départ
    genLab(grid, lab);
    yd = choixDepart(grid);
    ya=choixArrivee(grid);
    blito(grid, lab);// affichage des murs de manière un peu plus approprié que des dièses
    save_bitmap("lab.bmp", lab, NULL);
    clear_to_color(screen, makecol(255, 255, 255));
    blit(lab, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


    BITMAP *perso1 = load_bitmap("perso1.bmp", NULL); int cpt1=0;
    BITMAP *perso2 = load_bitmap("perso2.bmp", NULL); int cpt2=0;

    draw_sprite(screen, perso1, grid[yd][0]->pos_x, grid[yd][0]->pos_y);
    int xperso = 0, yperso = yd; // initialisation des coo du joueur 1
    // variables pour garder l'etat des touches
    int haut = 0;
    int bas = 0;
    int gauche = 0;
    int droite = 0;
    int victoir=0;
    while (victoir==0) { // tour du joueur 1
        // Effacer l'écran
        clear_to_color(screen, makecol(255, 255, 255));
        blit(lab, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (keypressed()) {
            if (key[KEY_UP] && !haut) {
                // Vérifier si le mouvement est valide vers le haut
                if (yperso > 0 && grid[yperso - 1][xperso]->val != 0) {
                    // coo et nb de coup mis a jour
                    yperso--;
                    cpt1++;
                    haut = 1; // touche enfoncée
                }
            } else if (!key[KEY_UP]) {
                haut = 0; // touche relachée
            }

            if (key[KEY_DOWN] && !bas) {
                if (yperso < size - 1 && grid[yperso + 1][xperso]->val != 0) {
                    yperso++;
                    cpt1++;
                    bas = 1;
                }
            } else if (!key[KEY_DOWN]) {
                bas = 0;
            }

            if (key[KEY_LEFT] && !gauche) {
                if (xperso > 0 && grid[yperso][xperso - 1]->val != 0) {
                    xperso--;
                    cpt1++;
                    gauche = 1;
                }
            } else if (!key[KEY_LEFT]) {
                gauche = 0;
            }

            if (key[KEY_RIGHT] && !droite) {
                if (xperso < size - 1 && grid[yperso][xperso + 1]->val != 0) {
                    xperso++;
                    cpt1++;
                    droite = 1;
                }
            } else if (!key[KEY_RIGHT]) {
                droite = 0;
            }
        }

        // affichage du perso1 à ses nouvelles coo
        draw_sprite(screen, perso1, grid[yperso][xperso]->pos_x, grid[yperso][xperso]->pos_y);

        // rafraichir l'écran
        vsync();
        blit(screen, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(5);
        victoir= victoire(yperso,xperso,ya);//detection de l'arrivée
    }
    allegro_message("%s est arrivé!",joueur1.nom);




    draw_sprite(screen, perso2, grid[yd][0]->pos_x, grid[yd][0]->pos_y);
    int xperso2 = 0, yperso2 = yd;//coordonnées du joueur 2
    haut = 0;
    bas = 0;
    gauche = 0;
    droite = 0;
    victoir=0;
    while (victoir==0) {//tour du joueur 2
        // Effacer l'écran
        clear_to_color(screen, makecol(255, 255, 255));
        blit(lab, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


        if (keypressed()) {
            if (key[KEY_UP] && !haut) {
                // pas de mur
                if (yperso2 > 0 && grid[yperso2 - 1][xperso2]->val != 0) {
                    // coo et nombre de coup mis a jour
                    yperso2--;
                    cpt2++;
                    haut = 1; // touche enfoncée
                }
            } else if (!key[KEY_UP]) {
                haut = 0; // touche relevée
            }

            if (key[KEY_DOWN] && !bas) {
                // pas de mur
                if (yperso2 < size - 1 && grid[yperso2 + 1][xperso2]->val != 0) {
                    // nombre de coup et coo mis a jour
                    yperso2++;
                    cpt2++;
                    bas = 1;
                }
            } else if (!key[KEY_DOWN]) {
                bas = 0;
            }

            if (key[KEY_LEFT] && !gauche) {
                // pas de mur ?
                if (xperso2 > 0 && grid[yperso2][xperso2 - 1]->val != 0) {
                    // coo et nombre de coup mis a jour
                    xperso2--;
                    cpt2++;
                    gauche = 1;
                }
            } else if (!key[KEY_LEFT]) {
                gauche = 0;
            }

            if (key[KEY_RIGHT] && !droite) {
                // pas de mur?
                if (xperso2 < size - 1 && grid[yperso2][xperso2 + 1]->val != 0) {
                    // coo et nombre de coup mis a jour
                    xperso2++;
                    cpt2++;
                    droite = 1;
                }
            } else if (!key[KEY_RIGHT]) {
                droite = 0;
            }
        }

        // affichage de perso1 à ses nouvelles coordonnées sur la grille
        draw_sprite(screen, perso2, grid[yperso2][xperso2]->pos_x, grid[yperso2][xperso2]->pos_y);

        // rafraichir l'écran
        vsync();
        blit(screen, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(5);
        victoir= victoire(yperso2,xperso2,ya);
    }
    allegro_message("%s est arrivé!",joueur2.nom);


    rest(5000);


    // comparaison du nombre de mouvement par joueur et declaration du vainqueur
    if(cpt1>cpt2){ allegro_message("Victoire de %s!!",joueur2.nom);joueur2.nbtickets+=2; }
    if(cpt1<cpt2){ allegro_message("Victoire de %s!!",joueur1.nom);joueur1.nbtickets+=2; }
    else {allegro_message("Meme nombre de coup pour les 2 joueurs");joueur2.nbtickets+=1;joueur1.nbtickets+=1; }




    //libération de la mémoire
    destroy_bitmap(lab);
    destroy_bitmap(perso1);
    destroy_bitmap(perso2);
    destroy_bitmap(fond);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            free(grid[i][j]);
        }
    }

    readkey();
    return 0;

}

END_OF_MAIN()
