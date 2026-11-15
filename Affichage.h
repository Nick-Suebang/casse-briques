#ifndef PONG_AFFICHAGE_H
#define PONG_AFFICHAGE_H

#include <string>
#include "raylib.h"

class Affichage
{
private:
    Font police;
    std::string message;
    static constexpr float TAILLE{75};
public:
    Affichage();
    ~Affichage();
    Affichage(const Affichage &) = delete;
    Affichage &operator=(const Affichage &) = delete;

    void setMessage(const std::string &argMessage);

    // Dessine le message en haut à gauche
    void dessiner() const;

    // Dessine un texte centré horizontalement à la hauteur y
    void dessinerCentre(const std::string &texte, float y, float taille, Color couleur) const;
};


#endif //PONG_AFFICHAGE_H
