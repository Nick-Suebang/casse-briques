#ifndef PONG_JEU_H
#define PONG_JEU_H

#include <vector>

#include "Affichage.h"
#include "Balle.h"
#include "Brique.h"
#include "Raquette.h"
#include "Son.h"

// Une partie de casse-briques : états, règles, entrées et rendu.
// La fenêtre et l'audio de raylib doivent être ouverts avant sa création.
class Jeu
{
private:
    enum class Etat { Accueil, EnJeu, Perdu, Gagne };

    Affichage affichage;
    Son son;
    Raquette raquette;
    Balle balle;
    std::vector<Brique> lesBriques;

    Etat etat{Etat::Accueil};
    int pointage{0};
    int vies{0};
    bool tenirRaquette{false};
    float tempsAccumule{0};

    void nouvellePartie();

    void avancerLeTemps();

    // Un pas de simulation : entrées, collisions, déplacement
    void avancerUnPas();

    void deplacerRaquette();

    void gererCollisions();

    void dessiner() const;

public:
    Jeu();

    // Appelée une fois par image affichée
    void image();
};


#endif //PONG_JEU_H
