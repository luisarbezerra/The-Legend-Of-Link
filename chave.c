#include "chave.h"

void chave_init(chave *c, int x, int y, bool viva){
    c->chave = al_load_bitmap("Imagens/chave.png");
    c->x = x;
    c->y = y;
    c->vivo = viva;
}

void chave_draw(chave *c){
    if(c->vivo == true){
        al_draw_bitmap(c->chave, c->x, c->y, 0);
    }
}
