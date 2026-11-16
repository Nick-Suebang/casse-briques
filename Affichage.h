#ifndef PONG_AFFICHAGE_H
#define PONG_AFFICHAGE_H

#include <string>
#include "raylib.h"

// Dessine les textes du jeu avec la police DS-DIGIT.
class Affichage
{
private:
    Font police;
    float largeurZone;
public:
    explicit Affichage(float argLargeurZone);
    ~Affichage();
    Affichage(const Affichage &) = delete;
    Affichage &operator=(const Affichage &) = delete;

    void dessinerTexte(const std::string &texte, Vector2 position, float taille, Color couleur) const;

    // Dessine un texte centré horizontalement à la hauteur y
    void dessinerCentre(const std::string &texte, float y, float taille, Color couleur) const;
};


#endif //PONG_AFFICHAGE_H
