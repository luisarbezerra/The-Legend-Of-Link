#include "flecha.h"

void flecha_init_morta(flecha * f){
    ALLEGRO_BITMAP *sprite = al_load_bitmap("Imagens/flecha.png");

    animation_init(&f->d, sprite, 16, 0, 16, 32, 1, 0);
    animation_init(&f->e, sprite, 0, 0, 16, 32, 1, 0);
    animation_init(&f->c, sprite, 32, 0, 16, 32, 1, 0);
    animation_init(&f->b, sprite, 48, 0, 16, 32, 1, 0);

    f->x = 0;
    f->y = 0;
    f->direcao = 'd';
    f->duracao = 0;
    f->viva = false;
}

void flecha_init(flecha *f, int x, int y, char direcao){
    f->x = x;
    f->y = y;
    f->direcao = direcao;
    f->duracao = 40; //aumentar qnt tempo que ela fica viva

    if(f->direcao == 'd'){
        f->atual = &f->d;
    }
    if(f->direcao == 'e'){
        f->atual = &f->e;
    }
    if(f->direcao == 'c'){
        f->atual = &f->c;
    }
    if(f->direcao == 'b'){
        f->atual = &f->b;
    }

    f->viva = true;
}

void flecha_update(flecha *f){
    if (f->direcao == 'd'){
        f->x = f->x + 2; // mexe na velocidade dela
    }

    if (f->direcao == 'e'){
        f->x = f->x - 2;
    }

    if (f->direcao == 'c'){
        f->y = f->y - 2;
    }

    if (f->direcao == 'b'){
        f->y = f->y + 2;
    }

    f->duracao -= 1;

    if(f->duracao <= 0){
        f->viva = false;
    }
}

void flecha_draw(flecha *f){
    if(f->viva == true){
        animation_draw(f->atual, f->x, f->y);
    }
}
