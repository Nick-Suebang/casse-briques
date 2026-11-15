#include "Affichage.h"
#include "Utilitaires/Configuration.h"

//-----------------------------------------------------------------------------
Affichage::Affichage()
{
    // Pour choisir une police
    police = LoadFontEx("assets/DS-DIGIT.ttf", (int) TAILLE, nullptr, 0);
    SetTextureFilter(police.texture, TEXTURE_FILTER_BILINEAR);
}

//-----------------------------------------------------------------------------
Affichage::~Affichage()
{
    UnloadFont(police);
}

//-----------------------------------------------------------------------------
void Affichage::setMessage(const std::string &argMessage)
{
    message = argMessage;
}

//-----------------------------------------------------------------------------
void Affichage::dessiner() const
{
    DrawTextEx(police, message.c_str(), {0, 0}, TAILLE, 1, WHITE);
}

//-----------------------------------------------------------------------------
void Affichage::dessinerCentre(const std::string &texte, float y, float taille, Color couleur) const
{
    Vector2 dimensions = MeasureTextEx(police, texte.c_str(), taille, 1);
    float x = (Configuration::getInstance()->LARGEUR_FENETRE - dimensions.x) / 2;
    DrawTextEx(police, texte.c_str(), {x, y}, taille, 1, couleur);
}

//-----------------------------------------------------------------------------
