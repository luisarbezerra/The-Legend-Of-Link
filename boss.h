#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include <allegro5/allegro.h>
#include <math.h>
#include "animation.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

typedef struct fogo{
    animation animacao;
    float x, y;
    bool vivo;
    int tempo;
}fogo;

void fogo_init_morto(fogo *f);
void fogo_init_vivo(fogo *f, int x, int y);
void fogo_update(fogo *f);
void fogo_draw (fogo *f);

typedef struct boss{
    float seno;
    animation animacao;
    int vida;
    int x,y;
    fogo f;
    ALLEGRO_SAMPLE *som_fogo;
}boss;

void boss_init(boss *b);
void boss_update(boss *b);
void boss_draw(boss *b);

#endif // BOSS_H_INCLUDED
