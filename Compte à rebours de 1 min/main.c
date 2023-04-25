#include <allegro.h>

int main()
{
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // Montrer la souris à l'écran
    show_mouse(screen);

    int seconds = 60; // Initialisation du compte à rebours à 60 secondes
    int counter = 0; // Initialisation du compteur pour la mise à jour du compte à rebours

    while(seconds > 0)
    {
        clear_to_color(screen, makecol(0, 0, 0)); // Effacement de l'écran

        textprintf_ex(screen, font, 100, 100, makecol(255, 255, 255), -1, "Compte a rebours : %d", seconds); // Affichage du compte à rebours

        if(counter == 60)
        {
            seconds--; // Décrémentation du compte à rebours
            counter = 0; // Réinitialisation du compteur
        }

        counter++; // Incrémentation du compteur

        rest(1000/60); // Attente pour la mise à jour du compte à rebours

        if(key[KEY_ESC]) // Condition d'arrêt de la boucle
            break;
    }
    readkey();
    allegro_exit(); // Fermeture d'Allegro

    return 0;
}END_OF_MAIN();
