#ifndef PONG_BALLE_H
#define PONG_BALLE_H

#include "Jouet.h"

class Balle : public Jouet
{
private:
    Vector2 depart;
    float vitesseHorizontale;
    float vitesseVerticale;

public:
    Balle(float argDepartX, float argDepartY);

    void rebondirMurs();

    void rebondirRaquetteOuPlafond();

    void toucherPlancher();

    void bouger();

    [[nodiscard]] bool descend() const;

    [[nodiscard]] bool vaADroite() const;
};


#endif //PONG_BALLE_H
