#ifndef PONG_JOUET_H
#define PONG_JOUET_H

#include "raylib.h"

class Jouet
{
protected:
    Vector2 position;
    Vector2 taille;
    Color couleur{WHITE};
public:
    Jouet(float argDepartX, float argDepartY, float argLargeur, float argHauteur);

    [[nodiscard]] Rectangle getHitBox() const;

    void dessiner() const;
};


#endif //PONG_JOUET_H
