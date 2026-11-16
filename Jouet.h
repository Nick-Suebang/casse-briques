#ifndef PONG_JOUET_H
#define PONG_JOUET_H

#include "raylib.h"

// Élément rectangulaire du jeu (balle, raquette, brique).
class Jouet
{
protected:
    Vector2 position;
    Vector2 taille;
    Color couleur;
public:
    Jouet(float argDepartX, float argDepartY, float argLargeur, float argHauteur, Color argCouleur = WHITE);
    virtual ~Jouet() = default;

    [[nodiscard]] Rectangle getHitBox() const;

    void dessiner() const;
};


#endif //PONG_JOUET_H
