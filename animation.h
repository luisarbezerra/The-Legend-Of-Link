#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <allegro5/allegro.h>

typedef struct animation{
    ALLEGRO_BITMAP *sprite;
    float time;
    float speed;
    int length;
    int x, y, width, height;
}animation;

void animation_init(animation * a, ALLEGRO_BITMAP *s, int x, int y, int width, int height, int length, float speed);
void animation_update(animation * a);
void animation_draw(animation * a, int x, int y);


#endif // ANIMATION_H_INCLUDED
