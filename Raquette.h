#ifndef PONG_RAQUETTE_H
#define PONG_RAQUETTE_H

#include "Jouet.h"

class Raquette : public Jouet
{
private:
    float vitesse{1.3f};
public:
    Raquette(float argDepartX, float argDepartY);

    void bougerAGauche();

    void bougerADroite();

    void setPositionX(float argPosition);
};


#endif //PONG_RAQUETTE_H
