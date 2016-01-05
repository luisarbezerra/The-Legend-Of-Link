#ifndef ALLEGRO_STUFF_H_INCLUDED
#define ALLEGRO_STUFF_H_INCLUDED

#include <allegro5/allegro.h>
#include "personagem.h"
#include "flecha.h"
#include "morcego.h"
#include "chave.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "boss.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct allegro_stuff{
    //Coisas do allegro
    float FPS;
    int SCREEN_W;
    int SCREEN_H;
    int SCREEN_RESIZE;

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;

    ALLEGRO_AUDIO_STREAM *musica;
    ALLEGRO_AUDIO_STREAM *musica_titulo;

    ALLEGRO_SAMPLE *som_morcego;
    ALLEGRO_SAMPLE *som_chave;
    ALLEGRO_SAMPLE *som_porta;


    bool redraw;
    bool closed;

    bool apertando_enter;

    //Imagens
    ALLEGRO_BITMAP * fim_screen;
    ALLEGRO_BITMAP * titulo_screen;
    ALLEGRO_BITMAP * gameover_screen;
    ALLEGRO_BITMAP * cena1;
    ALLEGRO_BITMAP * cena2;
    ALLEGRO_BITMAP * cena3;
    ALLEGRO_BITMAP * portatrancada;
    ALLEGRO_BITMAP * imagem_instrucoes;

    //Coisas do jogo
    personagem p;
    morcego m;
    chave ch;
    boss b;

    bool fim;
    bool titulo;
    bool instrucoes;
    bool gameover;
    bool pegouchave;
    bool abriuporta;

    int salaatual;

}allegro_stuff;

void Init(allegro_stuff* a);
void Update(allegro_stuff* a);
void Destroy(allegro_stuff* a);

bool colidiu_personagem_morcego(personagem *p, morcego *m);
bool colidiu_flecha_morcego(flecha *f, morcego *m);
bool colidiu_personagem_chave(personagem *p, chave *ch);

bool personagem_tentou_descer(personagem *p);
bool personagem_tentou_subir(personagem *p);

bool colidiu_personagem_fogo(personagem *p, fogo *f);
bool colidiu_flecha_boss(flecha *f, boss *b);

void salvar (allegro_stuff *a); // salva o jogo
void carregar (allegro_stuff *a); // carrega o jogo

#endif // ALLEGRO_STUFF_H_INCLUDED
