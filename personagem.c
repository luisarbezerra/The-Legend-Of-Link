#include "personagem.h"

void personagem_init(personagem * p){
    p->x = 120-8;
    p->y = 60;

    ALLEGRO_BITMAP *sprite = al_load_bitmap("Imagens/zelda.png");

    animation_init(&p->parada_b, sprite, 0, 0, 24, 32, 1, 0);
    animation_init(&p->parada_e, sprite, 0, 32, 24, 32, 1, 0);
    animation_init(&p->parada_c, sprite, 0, 64, 24, 32, 1, 0);
    animation_init(&p->parada_d, sprite, 0, 96, 24, 32, 1, 0);

    animation_init(&p->anda_b, sprite, 24, 0, 24, 32, 4, 0.2f);
    animation_init(&p->anda_e, sprite, 24, 32, 24, 32, 4, 0.2f);
    animation_init(&p->anda_c, sprite, 24, 64, 24, 32, 4, 0.2f);
    animation_init(&p->anda_d, sprite, 24, 96, 24, 32, 4, 0.2f);

    p->animacao_atual = &p->parada_b;
    p->direcao = 'b';

    flecha_init_morta(&p->f);
    p->som_flecha = al_load_sample("Som/LTTP_Arrow_Shoot.wav");
}

void personagem_update(personagem * p){
    ALLEGRO_KEYBOARD_STATE state;
    al_get_keyboard_state(&state);

    if (al_key_down(&state, ALLEGRO_KEY_LEFT) && p->x+8 > 32){
        p->x -= 1; // se quiser aumentar a velocidade, mudar este 1
        p->direcao = 'e';
    }
    if (al_key_down(&state, ALLEGRO_KEY_RIGHT) && p->x+16 < 240-32){
        p->x += 1;
        p->direcao = 'd';
    }
    if (al_key_down(&state, ALLEGRO_KEY_UP) && p->y+16 > 32){
        p->y -= 1;
        p->direcao = 'c';
    }
    if (al_key_down(&state, ALLEGRO_KEY_DOWN) && p->y+28 < 160-32){
        p->y += 1;
        p->direcao = 'b';
    }

    //Atirar
    if (al_key_down(&state, ALLEGRO_KEY_SPACE) && p->f.viva == false){
        flecha_init(&p->f, p->x+4, p->y, p->direcao);
        al_play_sample(p->som_flecha, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }

    //Esta apertando alguma direcao
    if(al_key_down(&state, ALLEGRO_KEY_LEFT) || al_key_down(&state, ALLEGRO_KEY_RIGHT) || al_key_down(&state, ALLEGRO_KEY_UP) || al_key_down(&state, ALLEGRO_KEY_DOWN)){
        if(p->direcao == 'c'){
            p->animacao_atual = &p->anda_c;
        }
        if(p->direcao == 'b'){
            p->animacao_atual = &p->anda_b;
        }
        if(p->direcao == 'e'){
            p->animacao_atual = &p->anda_e;
        }
        if(p->direcao == 'd'){
            p->animacao_atual = &p->anda_d;
        }
    }
    else{
        if(p->direcao == 'c'){
            p->animacao_atual = &p->parada_c;
        }
        if(p->direcao == 'b'){
            p->animacao_atual = &p->parada_b;
        }
        if(p->direcao == 'e'){
            p->animacao_atual = &p->parada_e;
        }
        if(p->direcao == 'd'){
            p->animacao_atual = &p->parada_d;
        }
    }

    animation_update(p->animacao_atual);

    flecha_update(&p->f);
}

void personagem_draw(personagem * p){
    animation_draw(p->animacao_atual, p->x, p->y);

    flecha_draw(&p->f);
}
