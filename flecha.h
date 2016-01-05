#ifndef FLECHA_H_INCLUDED
#define FLECHA_H_INCLUDED

#include <allegro5/allegro.h>
#include <math.h>
#include "animation.h"

typedef struct flecha{
    bool viva;
    animation c, b, d, e;
    animation *atual;
    int x;
    int y;
    char direcao;
    int duracao;
}flecha;

void flecha_init_morta(flecha * f);
void flecha_init(flecha *f, int x, int y, char direcao);
void flecha_update(flecha *f);
void flecha_draw(flecha *f);

#endif // FLECHA_H_INCLUDED
