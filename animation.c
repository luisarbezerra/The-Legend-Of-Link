#include "animation.h"

// a função inicializa os dados da animação.
void animation_init(animation * a, ALLEGRO_BITMAP *s, int x, int y, int width, int height, int length, float speed){
    a->sprite = s;
    a->time = 0;
    a->speed = speed;
    a->length = length;
    a->x = x;
    a->y = y;
    a->width = width;
    a->height = height;
}

void animation_update(animation * a){
    a->time += a->speed; //adiciono velocidade ao tempo
}

// transformação do tempo de float em um inteiro para saber qual é o quadro atual. a posição do quadro atual é a largura * o quadro que eu quero.
void animation_draw(animation * a, int x, int y){
    al_draw_bitmap_region(a->sprite, a->x + ((int)(a->time) % a->length)*a->width, a->y, a->width, a->height, x, y, 0);
}
