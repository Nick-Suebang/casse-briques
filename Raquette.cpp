#include "Raquette.h"

//-----------------------------------------------------------------------------
Raquette::Raquette(float argDepartX, float argDepartY) : Jouet(argDepartX, argDepartY, 50, 5)
{
}

//-----------------------------------------------------------------------------
void Raquette::bougerAGauche()
{
    position.x -= vitesse;
}

//-----------------------------------------------------------------------------
void Raquette::bougerADroite()
{
    position.x += vitesse;
}

//-----------------------------------------------------------------------------
void Raquette::setPositionX(float argPosition)
{
    position.x = argPosition;
}

//-----------------------------------------------------------------------------
