#ifndef CHAVE_H_INCLUDED
#define CHAVE_H_INCLUDED

#include <allegro5/allegro.h>
#include <math.h>

typedef struct chave{
    int x;
    int y;
    ALLEGRO_BITMAP * chave;
    bool vivo;
}chave;

void chave_init(chave *c, int x, int y, bool viva);
void chave_draw(chave *c);

#endif // CHAVE_H_INCLUDED
