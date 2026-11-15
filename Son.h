#ifndef PONG_SON_H
#define PONG_SON_H

#include "raylib.h"

class Son
{
private:
    Sound sonRate;
    Sound sonRebond;
    Sound sonReussi;
public:
    Son();
    ~Son();
    Son(const Son &) = delete;
    Son &operator=(const Son &) = delete;

    void jouerSonRate();
    void jouerSonRebond();
    void jouerSonReussi();
};


#endif //PONG_SON_H
