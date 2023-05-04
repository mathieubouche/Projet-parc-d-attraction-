#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include <time.h>


#define FRAME 9

void show_mouse(BITMAP *bmp);

int course(BITMAP *canasson[FRAME], BITMAP *fond, int segment, int troiz, int quatre) {
    int i = 0, x = 280, y = 100;
    int xd=30;
    while ((x < 630) && (segment == 1)) {
        clear_bitmap(screen);
        blit(fond, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        draw_sprite_h_flip(screen, canasson[i % FRAME], x, y);
        draw_sprite_h_flip(screen,canasson[i%FRAME],x,y+20);
        draw_sprite_h_flip(screen,canasson[i%FRAME],x-35,y);
        draw_sprite_h_flip(screen,canasson[i%FRAME],x-35,y+20);
        rest(100);
        i++;
        x += 10;
    }
    segment++;
    while ((x < 770) && (y < 220) && (segment == 2)) {
        clear_bitmap(screen);
        blit(fond, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        draw_sprite_h_flip(screen, canasson[i % FRAME], x, y);
        draw_sprite_h_flip(screen,canasson[i%FRAME],x,y+20);
        draw_sprite_h_flip(screen,canasson[i%FRAME],x-35,y);
        draw_sprite_h_flip(screen,canasson[i%FRAME],x-35,y+20);
        rest(100);
        i++;
        x += 10;
        y += 10;
    }
    segment++;
    while ((y < 415) && (segment == 3)) {
        clear_bitmap(screen);
        blit(fond, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        draw_sprite_h_flip(screen, canasson[i % FRAME], x, y);
        draw_sprite_h_flip(screen,canasson[i%FRAME],x,y+20);
        draw_sprite_h_flip(screen,canasson[i%FRAME],x-35,y);
        draw_sprite_h_flip(screen,canasson[i%FRAME],x-35,y+20);

        rest(100);
        i++;
        y += 10;
    }
    draw_sprite_v_flip(screen,canasson[2],763,410);         // accident, les deux chevaux de derrière se rentrent dedans et tombent
    draw_sprite_v_flip(screen,canasson[2],763-35,410+20);

    allegro_message("les chevaux %d et %d sont tombés",troiz, quatre);

    segment++;
    while ((x > 405) && (y < 480) && (segment == 4)) {
        clear_bitmap(screen);
        blit(fond, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        draw_sprite(screen, canasson[i % FRAME], x, y);
        draw_sprite(screen,canasson[i%FRAME],x,y+20);
        draw_sprite_v_flip(screen,canasson[2],763,410);
        draw_sprite_v_flip(screen,canasson[2],763-35,410+20);
        rest(100);
        i++;
        x -= 10;
        y += 10;
    }
    segment++;
    while ((x > 256) && (y == 480) && (segment == 5)) {
        clear_bitmap(screen);
        blit(fond, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        draw_sprite(screen, canasson[i % FRAME], x, y);
        draw_sprite(screen,canasson[i%FRAME],x,y+20);
        draw_sprite_v_flip(screen,canasson[2],763,410);
        draw_sprite_v_flip(screen,canasson[2],763-35,410+20);
        rest(100);
        i++;
        x -= 10;
        //y-=1;
    }
    segment++;
    while ((x > 30) && (y > 370) && (segment == 6)) {
        clear_bitmap(screen);
        blit(fond, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        draw_sprite(screen, canasson[i % FRAME], x, y);
        draw_sprite(screen,canasson[i%FRAME],x,y+20);
        draw_sprite_v_flip(screen,canasson[2],763,410);
        draw_sprite_v_flip(screen,canasson[2],763-35,410+20);
        rest(100);
        i++;
        x -= 10;
        y -= 5;
    }
    segment++;
    while ((x == 30) && (y > 220) && (segment == 7)) {
        clear_bitmap(screen);
        blit(fond, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        draw_sprite(screen, canasson[i % FRAME], x, y);
        draw_sprite(screen,canasson[i%FRAME],x,y+20);
        draw_sprite_v_flip(screen,canasson[2],763,410);
        draw_sprite_v_flip(screen,canasson[2],763-35,410+20);
        rest(100);
        i++;
        //x -= 10;
        y -= 10;
    }
    segment++;
    while ((xd < 280) && (y > 110) && (segment == 8)) {  // dans une dernière accéleration le cheval gagnant prend de l'avance et franchi la ligne d'arrivé en premier
        clear_bitmap(screen);
        blit(fond, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        draw_sprite_h_flip(screen, canasson[i % FRAME], x, y);
        draw_sprite_h_flip(screen,canasson[(i+3)%FRAME],xd,y+20);
        draw_sprite_v_flip(screen,canasson[2],763,410);
        draw_sprite_v_flip(screen,canasson[2],763-35,410+20);
        rest(100);
        i++;
        xd+=10;
        x += 15;
        y -= 5;
    }
    segment++;
    if (segment==9) return 0;
}   // animation simple des chevaux, deux arrivent au bout.

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
    BITMAP *fond;
    fond = load_bitmap("piste.bmp", NULL);
    if (!fond) {
        allegro_message("0");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


    BITMAP *canasson[FRAME];//declaration et chargement des différentes images de l'animation d'un cheval
    canasson[0] = load_bitmap("un-prime.bmp", NULL);if (!canasson[0]) {
        allegro_message("1");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    canasson[1] = load_bitmap("deux-prime.bmp", NULL);if (!canasson[1]) {
        allegro_message("2");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    canasson[2] = load_bitmap("trois-prime.bmp", NULL);if (!canasson[2]) {
        allegro_message("3");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    canasson[3] = load_bitmap("quatre-prime.bmp", NULL);if (!canasson[3]) {
        allegro_message("4");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    canasson[4] = load_bitmap("cinq-prime.bmp", NULL);if (!canasson[4]) {
        allegro_message("5");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    canasson[5] = load_bitmap("six-prime.bmp", NULL);if (!canasson[5]) {
        allegro_message("6");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    canasson[6] = load_bitmap("sept-prime.bmp", NULL);if (!canasson[6]) {
        allegro_message("7");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    canasson[7] = load_bitmap("huit-prime.bmp", NULL);if (!canasson[7]) {
        allegro_message("8");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    canasson[8] = load_bitmap("neuf-prime.bmp", NULL);if (!canasson[8]) {
        allegro_message("9");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


    // paris des deux joueurs :

    BITMAP *pariJ1 = load_bitmap("pari1.bmp", NULL);if (!pariJ1) {
        allegro_message("-1");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    BITMAP *pariJ2 = load_bitmap("pari2.bmp", NULL);if (!pariJ2) {
        allegro_message("-1");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    int premier, deuxieme, troiz, derDeDer;
    srand(time(NULL));
    premier = rand() % 4 + 1;
    deuxieme = rand() % 4 + 1;
    while (deuxieme == premier) {
        deuxieme = rand() % 4 + 1;
    }
    troiz = rand() % 4 + 1;
    while (troiz == premier || troiz == deuxieme) {
        troiz = rand() % 4 + 1;
    }
    derDeDer = rand() % 4 + 1;
    while (derDeDer == premier || derDeDer == deuxieme || derDeDer == troiz) {
        derDeDer = rand() % 4 + 1;
    }
    allegro_message("les paris suivants ont pour vocation de determiner le numéro du cheval gagnant");





    int bet1 = 0, bet2 = 0;
    //une première fenêtre s'ouvre pour le joueur 1 avec 4 options, une pour chaque cheval, la selection se fait grâce à la souris
    blit(fond, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


    //pari du joueur 1,
    do {
        draw_sprite(screen, pariJ1, 290, 250);
        show_mouse(screen);
        if ((mouse_b & 1) &&
            (((mouse_x < 319) && (mouse_x > 303)) && ((mouse_y < 334) && (mouse_y > 318)))) { //equivalent du bouton 1
            bet1 = 1;
        } else if ((mouse_b & 1) && (((mouse_x < 382) && (mouse_x > 366)) &&
                                     ((mouse_y < 334) && (mouse_y > 318)))) {//equivalent du bouton 2
            bet1 = 2;
        }
        if ((mouse_b & 1) &&
            (((mouse_x < 450) && (mouse_x > 434)) && ((mouse_y < 334) && (mouse_y > 318)))) {//equivalent du bouton 3
            bet1 = 3;
        }
        if ((mouse_b & 1) &&
            (((mouse_x < 526) && (mouse_x > 510)) && ((mouse_y < 334) && (mouse_y > 318)))) {//equivalent du bouton 4
            bet1 = 4;
        }
    } while ((bet1 != 1) && (bet1 != 2) && (bet1 != 3) && (bet1 != 4));

    rest(500);


    // pari du joueur 2, meme déroulé que pour le joueur 1
    do {

        draw_sprite(screen, pariJ2, 290, 250);
        show_mouse(screen);
        if ((mouse_b & 1) &&
            (((mouse_x < 319) && (mouse_x > 303)) && ((mouse_y < 334) && (mouse_y > 318)))) {//equivalent du bouton 1
            bet2 = 1;
        }
        if ((mouse_b & 1) &&
            (((mouse_x < 382) && (mouse_x > 366)) && ((mouse_y < 334) && (mouse_y > 318)))) {//equivalent du bouton 1
            bet2 = 2;
        }
        if ((mouse_b & 1) &&
            (((mouse_x < 450) && (mouse_x > 434)) && ((mouse_y < 334) && (mouse_y > 318)))) {//equivalent du bouton 1
            bet2 = 3;
        }
        if ((mouse_b & 1) &&
            (((mouse_x < 526) && (mouse_x > 510)) && ((mouse_y < 334) && (mouse_y > 318)))) {//equivalent du bouton 1
            bet2 = 4;
        }

    } while ((bet2 != 1) && (bet2 != 2) && (bet2 != 3) && (bet2 != 4));


    //l'animation de la course étant tout le temps la meme, le pari est inutile dés la deuxieme parti, pour pallier cela le numéro attribué aux chevaux
    // est random, c'est qui est fait en dessous




    course(canasson, fond, 1,troiz,derDeDer); //l'animation de la course

    // à la fin de la course, les résultats sont donnés
    allegro_message("le numéro du cheval gagnant etait %d",premier);
    if(bet1==premier){
        allegro_message("2 ticket en plus pour le joueur 1!! ");
    }
    if(bet2==premier){
        allegro_message("2 ticket en plus pour le joueur 2!! ");
    }
    else if(premier!=bet1 && premier!=bet2){
        allegro_message("personne ne remporte de ticket supplémentaire");
    }


    readkey();
    allegro_exit();
    return 0;

}END_OF_MAIN()
