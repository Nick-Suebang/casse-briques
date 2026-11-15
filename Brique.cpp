#include "Brique.h"

Brique::Brique(float departX, float departY, float largeur, float epaisseur) : Jouet(departX, departY, largeur, epaisseur)
{
    const Color COULEURS[5] = {SKYBLUE, BLUE, GREEN, RED, YELLOW};
    couleur = COULEURS[GetRandomValue(0, 4)];
}
