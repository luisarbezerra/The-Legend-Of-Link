#include "morcego.h"

void morcego_init_morto(morcego *m){
    m->vivo = false;
    m->x = 0;
    m->y = 0;
}

void morcego_init(morcego *m, int x, int y){
    ALLEGRO_BITMAP *sprite = al_load_bitmap("Imagens/morcego.png");
    animation_init(&m->animacao, sprite, 0, 0, 24, 24, 6, 0.3);

    m->vivo = true;
    m->x = x; // quando o morcego é criado, recebemos o x e y
    m->y = y;
}

void morcego_update(morcego *m, int x, int y){
    //Seguir personagem
    if(m->vivo == true){
        if(m->x+12 < x){
            m->x += 0.4; // para mudar a velocidade, muda-se aqui.
        }
        if(m->x+12 > x){
            m->x -= 0.4;
        }
        if(m->y+12 < y){
            m->y += 0.4;
        }
        if(m->y+12 > y){
            m->y -= 0.4;
        }

        animation_update(&m->animacao);
    }
}

void morcego_draw(morcego *m){
    if(m->vivo == true){
        animation_draw(&m->animacao, m->x, m->y);
    }
}

