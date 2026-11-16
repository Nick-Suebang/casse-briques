#include "raylib.h"
#include "Jeu.h"
#include "Utilitaires/Configuration.h"

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>

namespace
{
    void imageNavigateur(void *argJeu)
    {
        static_cast<Jeu *>(argJeu)->image();
    }
}
#endif

//-----------------------------------------------------------------------------
int main()
{
    InitWindow(Configuration::LARGEUR_FENETRE, Configuration::HAUTEUR_FENETRE, "Pong");
    InitAudioDevice();
    SetExitKey(KEY_NULL);

#if defined(__EMSCRIPTEN__)
    // Dans le navigateur, c'est la page qui appelle image() à chaque
    // rafraîchissement d'écran, et main() ne se termine jamais vraiment :
    // le jeu doit donc survivre à la fin de main().
    static Jeu jeu;
    emscripten_set_main_loop_arg(imageNavigateur, &jeu, 0, 1);
#else
    // Pour trouver le dossier assets/ à côté de l'exécutable
    ChangeDirectory(GetApplicationDirectory());
    SetTargetFPS(60);
    {
        // Le jeu est détruit à la fin de ce bloc, avant la fermeture de
        // l'audio et de la fenêtre dont ses sons et sa police dépendent.
        Jeu jeu;
        while (!WindowShouldClose() && !IsKeyPressed(KEY_Q))
        {
            jeu.image();
        }
    }
    CloseAudioDevice();
    CloseWindow();
#endif
    return 0;
}
