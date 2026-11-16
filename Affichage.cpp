#include "Affichage.h"

namespace
{
    // La police est chargée à la plus grande taille utilisée pour rester nette
    constexpr int TAILLE_POLICE{120};
    constexpr float ESPACEMENT_LETTRES{1};
}

//-----------------------------------------------------------------------------
Affichage::Affichage(float argLargeurZone)
    : police{LoadFontEx("assets/DS-DIGIT.ttf", TAILLE_POLICE, nullptr, 0)},
      largeurZone{argLargeurZone}
{
    SetTextureFilter(police.texture, TEXTURE_FILTER_BILINEAR);
}

//-----------------------------------------------------------------------------
Affichage::~Affichage()
{
    UnloadFont(police);
}

//-----------------------------------------------------------------------------
void Affichage::dessinerTexte(const std::string &texte, Vector2 position, float taille, Color couleur) const
{
    DrawTextEx(police, texte.c_str(), position, taille, ESPACEMENT_LETTRES, couleur);
}

//-----------------------------------------------------------------------------
void Affichage::dessinerCentre(const std::string &texte, float y, float taille, Color couleur) const
{
    Vector2 dimensions = MeasureTextEx(police, texte.c_str(), taille, ESPACEMENT_LETTRES);
    dessinerTexte(texte, {(largeurZone - dimensions.x) / 2, y}, taille, couleur);
}
