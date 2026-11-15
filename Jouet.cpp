#include "Jouet.h"

//-----------------------------------------------------------------------------
Jouet::Jouet(float argDepartX, float argDepartY, float argLargeur, float argHauteur)
{
    // assigne ses arguments au x et y de position
    position = {argDepartX, argDepartY};
    taille = {argLargeur, argHauteur};
}

//-----------------------------------------------------------------------------
Rectangle Jouet::getHitBox() const
{
    return {position.x, position.y, taille.x, taille.y};
}

//-----------------------------------------------------------------------------
void Jouet::dessiner() const
{
    DrawRectangleRec(getHitBox(), couleur);
}

//-----------------------------------------------------------------------------
