#include "Son.h"

//-----------------------------------------------------------------------------
// Les sons sont chargés une seule fois au démarrage
// (InitAudioDevice doit avoir été appelé avant).
Son::Son()
    : sonRate{LoadSound("assets/rate.ogg")},
      sonRebond{LoadSound("assets/rebond.ogg")},
      sonReussi{LoadSound("assets/reussi.ogg")}
{
}

//-----------------------------------------------------------------------------
Son::~Son()
{
    UnloadSound(sonRate);
    UnloadSound(sonRebond);
    UnloadSound(sonReussi);
}

//-----------------------------------------------------------------------------
void Son::jouerSonRate()
{
    PlaySound(sonRate);
}

//-----------------------------------------------------------------------------
void Son::jouerSonRebond()
{
    PlaySound(sonRebond);
}

//-----------------------------------------------------------------------------
void Son::jouerSonReussi()
{
    PlaySound(sonReussi);
}
