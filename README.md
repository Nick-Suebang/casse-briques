# Pong (casse-briques) en C++ avec raylib

Un casse-briques écrit en C++ avec la bibliothèque [raylib](https://www.raylib.com/).
Le même code se compile en programme pour ordinateur **et** en WebAssembly pour être joué directement dans un navigateur.

**Jouer en ligne :** https://nick-suebang.github.io/pong-game/

## Contrôles

- **Espace**, **Entrée** ou **clic** : commencer / rejouer
- **Flèche gauche / droite** : déplacer la raquette
- **Cliquer-glisser** la raquette avec la souris
- **R** : recommencer la partie
- **Q** : quitter (version ordinateur)

## Compiler pour le web

Prérequis : [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) et CMake 3.20+.

```bash
emcmake cmake -S . -B build-web -DCMAKE_BUILD_TYPE=Release
cmake --build build-web
```

Cela produit `index.html`, `index.js`, `index.wasm` et `index.data` dans `build-web/`.
Pour tester, servez ce dossier avec un serveur web (ouvrir le fichier directement ne fonctionne pas) :

```bash
python -m http.server 8000 --directory build-web
```

puis ouvrez http://localhost:8000.

## Compiler pour l'ordinateur

Prérequis : un compilateur C++17 et CMake 3.20+. raylib est téléchargé automatiquement.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Mise en ligne

Le workflow [`.github/workflows/deploy.yml`](.github/workflows/deploy.yml) compile le jeu en WebAssembly et le publie sur GitHub Pages à chaque push sur `main`.

## Structure du projet

```
.
├── CMakeLists.txt          # build ordinateur + web
├── main.cpp                # boucle de jeu, états (accueil, partie, fin)
├── Jouet.cpp/h             # classe de base : position, taille, couleur
├── Balle.cpp/h             # mouvement et rebonds
├── Raquette.cpp/h          # déplacement clavier / souris
├── Brique.cpp/h            # briques de couleur aléatoire
├── Affichage.cpp/h         # textes (police DS-DIGIT)
├── Son.cpp/h               # effets sonores
├── Utilitaires/
│   └── Configuration.cpp/h # constantes du jeu (singleton)
├── assets/                 # police et sons
└── web/shell.html          # page HTML qui accueille le jeu
```

## Auteur

- Nick Hariel
