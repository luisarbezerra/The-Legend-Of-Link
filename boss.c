#include "boss.h"


// FOGUINHO
void fogo_init_morto(fogo *f){

    ALLEGRO_BITMAP *sprite = al_load_bitmap("Imagens/fogo.png");
    animation_init(&f->animacao, sprite, 0, 0, 16, 16, 1, 0);

    f->x = 0;
    f->y = 0;
    f->vivo = false;
    f->tempo = 0;

}

void fogo_init_vivo(fogo *f, int x, int y){

    f->x = x;
    f->y = y;
    f->vivo = true;
    f->tempo = 60;

}

void fogo_update(fogo *f){

    if (f->vivo == true){
        f->y = f->y + 1.5; //velocidade que ele se desloca em y para baixo

        f->tempo = f->tempo - 1;
        if (f->tempo<=0){
            f->vivo = false;
        }
    }

}

void fogo_draw(fogo *f){
    if(f->vivo == true){
         animation_draw(&f->animacao, f->x, f->y);
    }
}

// BOSS
void boss_init(boss *b){
    b->seno=3*M_PI/4;

    fogo_init_morto(&b->f);

    ALLEGRO_BITMAP *sprite = al_load_bitmap("Imagens/boss.png");
    animation_init(&b->animacao, sprite, 0, 0, 32, 42, 3, 0.2);

    b->vida=3;

    b->som_fogo = al_load_sample("Som/LTTP_Boss_Fireball.wav");
}

void boss_update(boss *b){
    b->seno=b->seno+0.05; // aumentar velocidade boss aqui
    fogo_update(&b->f);
    b->x= 104 + sin(b->seno)*50;
    b-> y= 12;
    if (b->f.vivo == false){
        fogo_init_vivo(&b->f, 104 + sin(b->seno)*50, 12+16 );
        al_play_sample(b->som_fogo, 0.8, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }

    animation_update(&b->animacao);
}

void boss_draw(boss *b){
    animation_draw(&b->animacao, 104+ sin(b->seno)*50, 12);
    fogo_draw(&b->f);
}
