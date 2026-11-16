#include "Brique.h"

namespace
{
    constexpr Color COULEURS[] = {SKYBLUE, BLUE, GREEN, RED, YELLOW};
    constexpr int NBR_COULEURS = sizeof(COULEURS) / sizeof(COULEURS[0]);

    Color couleurAuHasard()
    {
        return COULEURS[GetRandomValue(0, NBR_COULEURS - 1)];
    }
}

//-----------------------------------------------------------------------------
Brique::Brique(float argDepartX, float argDepartY, float argLargeur, float argEpaisseur)
    : Jouet(argDepartX, argDepartY, argLargeur, argEpaisseur, couleurAuHasard())
{
}
