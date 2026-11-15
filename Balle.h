#ifndef PONG_BALLE_H
#define PONG_BALLE_H

#include "Jouet.h"

class Balle : public Jouet
{
private:
    float departX;
    float departY;
    float vitesseHorizontale{1.2f};
    float vitesseVerticale{1.2f};

public:
    Balle(float argDepartX, float argDepartY);

    void rebondirMurs();

    void rebondirRaquetteOuPlafond();

    void toucherPlancher();

    void bouger();

    [[nodiscard]] bool descend() const;
};


#endif //PONG_BALLE_H
