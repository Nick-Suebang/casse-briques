#include "Balle.h"
#include "Utilitaires/Configuration.h"

//-----------------------------------------------------------------------------
Balle::Balle(float argDepartX, float argDepartY)
    : Jouet(argDepartX, argDepartY, Configuration::TAILLE_BALLE, Configuration::TAILLE_BALLE),
      depart{argDepartX, argDepartY},
      vitesseHorizontale{Configuration::VITESSE_BALLE},
      vitesseVerticale{Configuration::VITESSE_BALLE}
{
}

//-----------------------------------------------------------------------------
void Balle::rebondirMurs()
{
    vitesseHorizontale *= -1;
}

//-----------------------------------------------------------------------------
void Balle::rebondirRaquetteOuPlafond()
{
    vitesseVerticale *= -1;
}

//-----------------------------------------------------------------------------
void Balle::toucherPlancher()
{
    position = depart;
}

//-----------------------------------------------------------------------------
void Balle::bouger()
{
    position.x += vitesseHorizontale;
    position.y += vitesseVerticale;
}

//-----------------------------------------------------------------------------
bool Balle::descend() const
{
    return vitesseVerticale > 0;
}

//-----------------------------------------------------------------------------
bool Balle::vaADroite() const
{
    return vitesseHorizontale > 0;
}
