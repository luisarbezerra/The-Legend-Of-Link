#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED

#include <allegro5/allegro.h>
#include <math.h>
#include "animation.h"
#include "flecha.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

typedef struct personagem{
    flecha f;

    float x, y;

    char direcao;

    animation parada_c, parada_b, parada_e, parada_d;
    animation anda_c, anda_b, anda_e, anda_d;
    animation * animacao_atual;

    ALLEGRO_SAMPLE *som_flecha;
}personagem;

void personagem_init(personagem * p);
void personagem_update(personagem * p);
void personagem_draw(personagem * p);

#endif // PERSONAGEM_H_INCLUDED
