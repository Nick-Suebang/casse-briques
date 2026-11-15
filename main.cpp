#include <memory>
#include <string>
#include <vector>

#include "raylib.h"
#include "Raquette.h"
#include "Balle.h"
#include "Affichage.h"
#include "Brique.h"
#include "Son.h"
#include "Utilitaires/Configuration.h"

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#endif

// Dans le navigateur, c'est la page web qui appelle notre fonction image()
// à chaque rafraîchissement d'écran : l'état du jeu doit donc vivre en dehors
// de main(), dans ces variables globales.
namespace
{
    enum class Etat { Accueil, EnJeu, GameOver, Gagne };

    Configuration *configuration = Configuration::getInstance();

    std::unique_ptr<Raquette> raquette;
    std::unique_ptr<Balle> balle;
    std::unique_ptr<Affichage> affichage;
    std::unique_ptr<Son> son;
    std::vector<std::unique_ptr<Brique>> lesBriques;

    Etat etat{Etat::Accueil};
    int pointage{0};
    int vies{3};
    bool tenirRaquette{false};
    float tempsAccumule{0};

    //-------------------------------------------------------------------------
    void nouvellePartie()
    {
        pointage = 0;
        vies = 3;
        tenirRaquette = false;
        tempsAccumule = 0;

        raquette = std::make_unique<Raquette>(configuration->LARGEUR_FENETRE / 2, configuration->HAUTEUR_FENETRE - 20);
        balle = std::make_unique<Balle>(configuration->LARGEUR_FENETRE / 2, configuration->NBR_LIGNES_BRIQUE * (configuration->EPAISSEUR_BRIQUE + configuration->ESPACEMENT) + 100);

        lesBriques.clear();
        for (int x = 0; x < configuration->NBR_RANGEES_BRIQUE; x++)
        {
            for (int y = 0; y < configuration->NBR_LIGNES_BRIQUE; y++)
            {
                lesBriques.push_back(std::make_unique<Brique>(x * (configuration->LARGEUR_BRIQUE + configuration->ESPACEMENT) + configuration->ESPACEMENT, y * (configuration->EPAISSEUR_BRIQUE + 10) + 90, configuration->LARGEUR_BRIQUE, configuration->EPAISSEUR_BRIQUE));
            }
        }
    }

    //-------------------------------------------------------------------------
    // Un pas de simulation (le jeu original tournait à FPS pas par seconde).
    void avancerUnPas()
    {
        // Pour déplacer la raquette à gauche ou à droite
        if (IsKeyDown(KEY_LEFT))
        {
            raquette->bougerAGauche();
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            raquette->bougerADroite();
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 souris = GetMousePosition();
            if (tenirRaquette)
            {
                raquette->setPositionX(souris.x);
            }
            else if (CheckCollisionPointRec(souris, raquette->getHitBox()))
            {
                tenirRaquette = true;
            }
        }
        else
        {
            tenirRaquette = false;
        }

        // Gestion des collisions
        // toucher le plancher
        if (balle->getHitBox().y > configuration->HAUTEUR_FENETRE)
        {
            son->jouerSonRate();
            balle->toucherPlancher();
            vies--;
            if (vies == 0)
            {
                etat = Etat::GameOver;
                return;
            }
        }

        // toucher le plafond
        if (balle->getHitBox().y < 0)
        {
            son->jouerSonRebond();
            balle->rebondirRaquetteOuPlafond();
        }

        // toucher un mur
        if (balle->getHitBox().x < 0 || balle->getHitBox().x + 10 > configuration->LARGEUR_FENETRE)
        {
            son->jouerSonRebond();
            balle->rebondirMurs();
        }

        // toucher la raquette (seulement quand la balle descend, pour
        // qu'elle ne reste pas coincée dans la raquette)
        if (balle->descend() && CheckCollisionRecs(balle->getHitBox(), raquette->getHitBox()))
        {
            son->jouerSonReussi();
            balle->rebondirRaquetteOuPlafond();
            pointage++;
        }

        // toucher une brique
        bool resteDesBriques = false;
        for (auto &brique : lesBriques)
        {
            if (brique != nullptr)
            {
                if (CheckCollisionRecs(brique->getHitBox(), balle->getHitBox()))
                {
                    son->jouerSonReussi();
                    balle->rebondirRaquetteOuPlafond();
                    brique.reset();
                    pointage++;
                }
                else
                {
                    resteDesBriques = true;
                }
            }
        }
        if (!resteDesBriques)
        {
            etat = Etat::Gagne;
            return;
        }

        balle->bouger();
    }

    //-------------------------------------------------------------------------
    void dessiner()
    {
        BeginDrawing();
        ClearBackground(BLACK);

        raquette->dessiner();
        if (etat == Etat::EnJeu)
        {
            balle->dessiner();
        }
        for (const auto &brique : lesBriques)
        {
            if (brique != nullptr)
            {
                brique->dessiner();
            }
        }

        const float milieu = configuration->HAUTEUR_FENETRE / 2.0f;
        switch (etat)
        {
            case Etat::Accueil:
                affichage->dessinerCentre("PONG", milieu - 60, 120, WHITE);
                affichage->dessinerCentre("Cliquer ou appuyer sur Espace pour jouer", milieu + 80, 40, LIGHTGRAY);
                affichage->dessinerCentre("Fleches gauche / droite ou glisser la raquette", milieu + 130, 30, GRAY);
                break;
            case Etat::EnJeu:
                affichage->setMessage("Vies : " + std::to_string(vies) + " Pointage : " + std::to_string(pointage));
                affichage->dessiner();
                break;
            case Etat::GameOver:
            case Etat::Gagne:
                affichage->dessinerCentre(etat == Etat::GameOver ? "Game Over" : "Bravo !", milieu - 60, 120, WHITE);
                affichage->dessinerCentre("Pointage : " + std::to_string(pointage), milieu + 70, 50, LIGHTGRAY);
                affichage->dessinerCentre("Cliquer ou appuyer sur Espace pour rejouer", milieu + 130, 40, GRAY);
                break;
        }

        EndDrawing();
    }

    //-------------------------------------------------------------------------
    // Appelée une fois par image affichée (environ 60 fois par seconde).
    void image()
    {
        const bool demarrer = IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        switch (etat)
        {
            case Etat::Accueil:
                if (demarrer)
                {
                    etat = Etat::EnJeu;
                }
                break;
            case Etat::GameOver:
            case Etat::Gagne:
                if (demarrer)
                {
                    nouvellePartie();
                    etat = Etat::EnJeu;
                }
                break;
            case Etat::EnJeu:
            {
                if (IsKeyPressed(KEY_R))
                {
                    nouvellePartie();
                }
                // On garde la vitesse du jeu original (FPS pas par seconde)
                // quelle que soit la fréquence d'affichage de l'écran.
                const float dureeUnPas = 1.0f / configuration->FPS;
                float dt = GetFrameTime();
                if (dt > 0.1f)
                {
                    dt = 0.1f; // évite un saut si l'onglet était en arrière-plan
                }
                tempsAccumule += dt;
                while (tempsAccumule >= dureeUnPas && etat == Etat::EnJeu)
                {
                    avancerUnPas();
                    tempsAccumule -= dureeUnPas;
                }
                break;
            }
        }

        dessiner();
    }
}

//-----------------------------------------------------------------------------
int main()
{
    InitWindow(configuration->LARGEUR_FENETRE, configuration->HAUTEUR_FENETRE, "Pong");
    InitAudioDevice();
    SetExitKey(KEY_NULL);

#if !defined(__EMSCRIPTEN__)
    // Pour trouver le dossier assets/ à côté de l'exécutable
    ChangeDirectory(GetApplicationDirectory());
#endif

    affichage = std::make_unique<Affichage>();
    son = std::make_unique<Son>();
    nouvellePartie();

#if defined(__EMSCRIPTEN__)
    emscripten_set_main_loop(image, 0, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose() && !IsKeyPressed(KEY_Q))
    {
        image();
    }

    lesBriques.clear();
    son.reset();
    affichage.reset();
    CloseAudioDevice();
    CloseWindow();
#endif
    return 0;
}
