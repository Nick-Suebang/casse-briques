#include "Raquette.h"
#include "Utilitaires/Configuration.h"

//-----------------------------------------------------------------------------
Raquette::Raquette(float argCentreX, float argDepartY, float argLargeurTerrain)
    : Jouet(argCentreX - Configuration::LARGEUR_RAQUETTE / 2, argDepartY,
            Configuration::LARGEUR_RAQUETTE, Configuration::EPAISSEUR_RAQUETTE),
      largeurTerrain{argLargeurTerrain}
{
}

//-----------------------------------------------------------------------------
void Raquette::bougerAGauche()
{
    position.x -= Configuration::VITESSE_RAQUETTE;
    resterDansLeTerrain();
}

//-----------------------------------------------------------------------------
void Raquette::bougerADroite()
{
    position.x += Configuration::VITESSE_RAQUETTE;
    resterDansLeTerrain();
}

//-----------------------------------------------------------------------------
void Raquette::centrerSur(float argX)
{
    position.x = argX - taille.x / 2;
    resterDansLeTerrain();
}

//-----------------------------------------------------------------------------
void Raquette::resterDansLeTerrain()
{
    if (position.x < 0)
    {
        position.x = 0;
    }
    else if (position.x + taille.x > largeurTerrain)
    {
        position.x = largeurTerrain - taille.x;
    }
}
