#ifndef PONG_CONFIGURATION_H
#define PONG_CONFIGURATION_H

// Constantes du jeu, connues à la compilation.
namespace Configuration
{
    // Fenêtre et simulation
    constexpr int LARGEUR_FENETRE{1024};
    constexpr int HAUTEUR_FENETRE{764};
    constexpr int PAS_PAR_SECONDE{400};
    constexpr int VIES_DEPART{3};

    // Briques
    constexpr int NBR_LIGNES_BRIQUE{5};
    constexpr int NBR_RANGEES_BRIQUE{10};
    constexpr float LARGEUR_BRIQUE{static_cast<float>(LARGEUR_FENETRE) / (NBR_RANGEES_BRIQUE + 1)};
    constexpr float EPAISSEUR_BRIQUE{20};
    constexpr float ESPACEMENT{LARGEUR_BRIQUE / (NBR_RANGEES_BRIQUE + 1)};
    constexpr float ESPACEMENT_VERTICAL{10};
    constexpr float HAUT_DES_BRIQUES{90};

    // Raquette
    constexpr float LARGEUR_RAQUETTE{50};
    constexpr float EPAISSEUR_RAQUETTE{5};
    constexpr float VITESSE_RAQUETTE{1.3f};
    constexpr float MARGE_BAS_RAQUETTE{20};

    // Balle
    constexpr float TAILLE_BALLE{10};
    constexpr float VITESSE_BALLE{1.2f};
    constexpr float ECART_BALLE_BRIQUES{100};
}

#endif //PONG_CONFIGURATION_H
