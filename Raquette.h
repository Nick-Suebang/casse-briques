#ifndef PONG_RAQUETTE_H
#define PONG_RAQUETTE_H

#include "Jouet.h"

class Raquette : public Jouet
{
private:
    float largeurTerrain;

    // Garde la raquette entièrement dans le terrain
    void resterDansLeTerrain();
public:
    Raquette(float argCentreX, float argDepartY, float argLargeurTerrain);

    void bougerAGauche();

    void bougerADroite();

    void centrerSur(float argX);
};


#endif //PONG_RAQUETTE_H
