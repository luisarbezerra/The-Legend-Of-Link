#ifndef MORCEGO_H_INCLUDED
#define MORCEGO_H_INCLUDED

#include <allegro5/allegro.h>
#include <math.h>
#include "animation.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

typedef struct morcego{
    float x;
    float y;
    animation animacao;
    bool vivo;
}morcego;

void morcego_init_morto(morcego *m);
void morcego_init(morcego *m, int x, int y);
void morcego_update(morcego *m, int x, int y);
void morcego_draw(morcego *m);

#endif // MORCEGO_H_INCLUDED
