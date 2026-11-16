#include "Jouet.h"

//-----------------------------------------------------------------------------
Jouet::Jouet(float argDepartX, float argDepartY, float argLargeur, float argHauteur, Color argCouleur)
    : position{argDepartX, argDepartY}, taille{argLargeur, argHauteur}, couleur{argCouleur}
{
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
