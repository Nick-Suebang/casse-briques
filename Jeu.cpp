#include "Jeu.h"

#include <algorithm>
#include <string>

#include "Utilitaires/Configuration.h"

using namespace Configuration;

namespace
{
    constexpr float POSITION_DEPART_BALLE_Y{NBR_LIGNES_BRIQUE * (EPAISSEUR_BRIQUE + ESPACEMENT) + ECART_BALLE_BRIQUES};
    constexpr float POSITION_RAQUETTE_Y{HAUTEUR_FENETRE - MARGE_BAS_RAQUETTE};
    constexpr float MILIEU_ECRAN_Y{HAUTEUR_FENETRE / 2.0f};

    // Tailles de texte
    constexpr float TAILLE_TITRE{120};
    constexpr float TAILLE_POINTAGE{75};
    constexpr float TAILLE_RESULTAT{50};
    constexpr float TAILLE_CONSIGNE{40};
    constexpr float TAILLE_AIDE{30};

    // Le jeu ne rattrape pas plus de 0,1 s (par exemple quand l'onglet
    // était en arrière-plan), sinon la balle ferait un grand saut.
    constexpr float RETARD_MAXIMAL{0.1f};

    bool demandeDeDemarrer()
    {
        return IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    }
}

//-----------------------------------------------------------------------------
Jeu::Jeu()
    : affichage(LARGEUR_FENETRE),
      raquette(LARGEUR_FENETRE / 2.0f, POSITION_RAQUETTE_Y, LARGEUR_FENETRE),
      balle(LARGEUR_FENETRE / 2.0f, POSITION_DEPART_BALLE_Y)
{
    nouvellePartie();
}

//-----------------------------------------------------------------------------
void Jeu::nouvellePartie()
{
    pointage = 0;
    vies = VIES_DEPART;
    tenirRaquette = false;
    tempsAccumule = 0;

    raquette = Raquette(LARGEUR_FENETRE / 2.0f, POSITION_RAQUETTE_Y, LARGEUR_FENETRE);
    balle = Balle(LARGEUR_FENETRE / 2.0f, POSITION_DEPART_BALLE_Y);

    lesBriques.clear();
    for (int x = 0; x < NBR_RANGEES_BRIQUE; x++)
    {
        for (int y = 0; y < NBR_LIGNES_BRIQUE; y++)
        {
            float departX = x * (LARGEUR_BRIQUE + ESPACEMENT) + ESPACEMENT;
            float departY = y * (EPAISSEUR_BRIQUE + ESPACEMENT_VERTICAL) + HAUT_DES_BRIQUES;
            lesBriques.emplace_back(departX, departY, LARGEUR_BRIQUE, EPAISSEUR_BRIQUE);
        }
    }
}

//-----------------------------------------------------------------------------
void Jeu::image()
{
    switch (etat)
    {
        case Etat::Accueil:
            if (demandeDeDemarrer())
            {
                etat = Etat::EnJeu;
            }
            break;
        case Etat::Perdu:
        case Etat::Gagne:
            if (demandeDeDemarrer())
            {
                nouvellePartie();
                etat = Etat::EnJeu;
            }
            break;
        case Etat::EnJeu:
            if (IsKeyPressed(KEY_R))
            {
                nouvellePartie();
            }
            avancerLeTemps();
            break;
    }

    dessiner();
}

//-----------------------------------------------------------------------------
// Garde la vitesse du jeu original (PAS_PAR_SECONDE pas de simulation par
// seconde), quelle que soit la fréquence d'affichage de l'écran.
void Jeu::avancerLeTemps()
{
    const float dureeUnPas = 1.0f / PAS_PAR_SECONDE;
    tempsAccumule += std::min(GetFrameTime(), RETARD_MAXIMAL);
    while (tempsAccumule >= dureeUnPas && etat == Etat::EnJeu)
    {
        avancerUnPas();
        tempsAccumule -= dureeUnPas;
    }
}

//-----------------------------------------------------------------------------
void Jeu::avancerUnPas()
{
    deplacerRaquette();
    gererCollisions();
    if (etat == Etat::EnJeu)
    {
        balle.bouger();
    }
}

//-----------------------------------------------------------------------------
void Jeu::deplacerRaquette()
{
    // Au clavier
    if (IsKeyDown(KEY_LEFT))
    {
        raquette.bougerAGauche();
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        raquette.bougerADroite();
    }

    // À la souris : on attrape la raquette puis on la fait glisser
    if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        tenirRaquette = false;
        return;
    }
    Vector2 souris = GetMousePosition();
    if (tenirRaquette)
    {
        raquette.centrerSur(souris.x);
    }
    else if (CheckCollisionPointRec(souris, raquette.getHitBox()))
    {
        tenirRaquette = true;
    }
}

//-----------------------------------------------------------------------------
void Jeu::gererCollisions()
{
    const Rectangle zoneBalle = balle.getHitBox();

    // toucher le plancher
    if (zoneBalle.y > HAUTEUR_FENETRE)
    {
        son.jouerSonRate();
        balle.toucherPlancher();
        vies--;
        if (vies == 0)
        {
            etat = Etat::Perdu;
        }
        return;
    }

    // toucher le plafond
    if (zoneBalle.y < 0 && !balle.descend())
    {
        son.jouerSonRebond();
        balle.rebondirRaquetteOuPlafond();
    }

    // toucher un mur (seulement si la balle va vers ce mur)
    const bool murGauche = zoneBalle.x < 0 && !balle.vaADroite();
    const bool murDroit = zoneBalle.x + zoneBalle.width > LARGEUR_FENETRE && balle.vaADroite();
    if (murGauche || murDroit)
    {
        son.jouerSonRebond();
        balle.rebondirMurs();
    }

    // toucher la raquette (seulement quand la balle descend, pour
    // qu'elle ne reste pas coincée dans la raquette)
    if (balle.descend() && CheckCollisionRecs(zoneBalle, raquette.getHitBox()))
    {
        son.jouerSonReussi();
        balle.rebondirRaquetteOuPlafond();
        pointage++;
    }

    // toucher une brique : une seule par pas, sinon deux rebonds
    // s'annuleraient et la balle traverserait les briques
    auto briqueTouchee = std::find_if(lesBriques.begin(), lesBriques.end(), [&zoneBalle](const Brique &brique)
    {
        return CheckCollisionRecs(brique.getHitBox(), zoneBalle);
    });
    if (briqueTouchee != lesBriques.end())
    {
        son.jouerSonReussi();
        balle.rebondirRaquetteOuPlafond();
        lesBriques.erase(briqueTouchee);
        pointage++;
        if (lesBriques.empty())
        {
            etat = Etat::Gagne;
        }
    }
}

//-----------------------------------------------------------------------------
void Jeu::dessiner() const
{
    BeginDrawing();
    ClearBackground(BLACK);

    raquette.dessiner();
    for (const Brique &brique : lesBriques)
    {
        brique.dessiner();
    }

    switch (etat)
    {
        case Etat::Accueil:
            affichage.dessinerCentre("PONG", MILIEU_ECRAN_Y - 60, TAILLE_TITRE, WHITE);
            affichage.dessinerCentre("Cliquer ou appuyer sur Espace pour jouer", MILIEU_ECRAN_Y + 80, TAILLE_CONSIGNE, LIGHTGRAY);
            affichage.dessinerCentre("Fleches gauche / droite ou glisser la raquette", MILIEU_ECRAN_Y + 130, TAILLE_AIDE, GRAY);
            break;
        case Etat::EnJeu:
            balle.dessiner();
            affichage.dessinerTexte("Vies : " + std::to_string(vies) + " Pointage : " + std::to_string(pointage), {0, 0}, TAILLE_POINTAGE, WHITE);
            break;
        case Etat::Perdu:
        case Etat::Gagne:
            affichage.dessinerCentre(etat == Etat::Perdu ? "Partie perdue" : "Bravo !", MILIEU_ECRAN_Y - 60, TAILLE_TITRE, WHITE);
            affichage.dessinerCentre("Pointage : " + std::to_string(pointage), MILIEU_ECRAN_Y + 70, TAILLE_RESULTAT, LIGHTGRAY);
            affichage.dessinerCentre("Cliquer ou appuyer sur Espace pour rejouer", MILIEU_ECRAN_Y + 130, TAILLE_CONSIGNE, GRAY);
            break;
    }

    EndDrawing();
}
