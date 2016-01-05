#include "allegro_stuff.h"

void Init(allegro_stuff* a){
    //Coisas do alegro
    a->FPS = 60;
    a->SCREEN_W = 240;
    a->SCREEN_H = 160;
    a->SCREEN_RESIZE = 3;

    a->closed = false;

    a->display = NULL;
    a->event_queue = NULL;
    a->timer = NULL;
    a->redraw = true;

    al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);

    a->timer = al_create_timer(1.0 / a->FPS);
    a->display = al_create_display(a->SCREEN_W*a->SCREEN_RESIZE, a->SCREEN_H*a->SCREEN_RESIZE);

    al_clear_to_color(al_map_rgb(255, 0, 255));

    al_set_target_bitmap(al_get_backbuffer(a->display));

    a->event_queue = al_create_event_queue();

    al_register_event_source(a->event_queue, al_get_display_event_source(a->display));

    al_register_event_source(a->event_queue, al_get_timer_event_source(a->timer));

    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();

    al_start_timer(a->timer);

    a->apertando_enter = false;

    //Imagens
    a->fim_screen = al_load_bitmap("Imagens/fim.png");
    a->titulo_screen = al_load_bitmap("Imagens/titulo.png");
    a->gameover_screen = al_load_bitmap("Imagens/gameover.png");
    a->cena1 = al_load_bitmap("Imagens/tela1.png");
    a->cena2 = al_load_bitmap("Imagens/tela2.png");
    a->cena3 = al_load_bitmap("Imagens/telachefe.png");
    a->portatrancada = al_load_bitmap("Imagens/portatrancada.png");
    a->imagem_instrucoes = al_load_bitmap("Imagens/comandos.png");


    //Sons
    a->som_morcego = al_load_sample("Som/LTTP_Enemy_Kill.wav");
    a->som_chave = al_load_sample("Som/LTTP_Get_Key.wav");
    a->som_porta = al_load_sample("Som/LTTP_Door_Unlock.wav");
    a->musica = al_load_audio_stream("Som/Dungeon.ogg", 4, 1024);
    a->musica_titulo = al_load_audio_stream("Som/Title.ogg", 4, 1024);


    //Coisas do jogo
    personagem_init(&a->p);
    morcego_init(&a->m, 64, 100); //x e y do morcego
    boss_init (&a->b);

    chave_init(&a->ch, 128, 96, true);

    a->fim = false;
    a->titulo = true;
    a->gameover = false;
    a->pegouchave = false;
    a->abriuporta = false;

    a->salaatual = 1;

    al_attach_audio_stream_to_mixer(a->musica_titulo, al_get_default_mixer());
    al_set_audio_stream_playing(a->musica_titulo, true);
}

void Update(allegro_stuff * a){
    ALLEGRO_EVENT ev;
    al_wait_for_event(a->event_queue, &ev);

    if(ev.type == ALLEGRO_EVENT_TIMER){
        if(a->gameover == false && a->titulo == false && a->fim == false){
            personagem_update(&a->p);

            if (a->salaatual ==3){
                boss_update(&a->b);

                if(colidiu_flecha_boss(&a->p.f, &a->b) == true){
                    a->b.vida -=1;
                    a->p.f.viva = false;
                    al_play_sample(a->som_morcego, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                    if (a->b.vida <= 0){
                       a->fim = true;
                    }
                }

                if(colidiu_personagem_fogo(&a->p, &a->b.f) == true){
                    a->gameover = true;
                   }
            }

            if(a->salaatual == 2){
                morcego_update(&a->m, a->p.x+16, a->p.y+12);

                if(colidiu_personagem_morcego(&a->p, &a->m)){
                    a->gameover = true;
                }

                if(colidiu_flecha_morcego(&a->p.f, &a->m)){
                    a->p.f.viva = false;
                    a->m.vivo = false;
                    al_play_sample(a->som_morcego, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                }

                if(colidiu_personagem_chave(&a->p, &a->ch) && a->pegouchave == false){
                    a->ch.vivo = false;
                    a->pegouchave = true;
                    al_play_sample(a->som_chave, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                }
            }

            if(personagem_tentou_descer(&a->p)){
                if(a->salaatual == 1){
                    a->salaatual = 2;
                    a->p.y = 17;
                }
                else if(a->salaatual == 3){
                    a->salaatual = 1;
                    a->p.y = 17;
                }
            }

            if(personagem_tentou_subir(&a->p)){
                if(a->salaatual == 2){
                    a->salaatual = 1;
                    a->p.y = 97;
                }
                else if(a->salaatual == 1 && a->pegouchave == true){
                    a->salaatual = 3;
                    a->p.y = 97;
                    a->abriuporta = true;
                    al_play_sample(a->som_porta, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                }
            }
        }

        a->redraw = true;
    }
    else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        a->closed = true;
    }

    if(a->redraw && al_is_event_queue_empty(a->event_queue)) {
        a->redraw = false;

        al_clear_to_color(al_map_rgb(0,0,0));

        ALLEGRO_TRANSFORM transform;
        al_identity_transform(&transform);
        al_scale_transform(&transform, a->SCREEN_RESIZE, a->SCREEN_RESIZE);
        al_use_transform(&transform);

        ALLEGRO_KEYBOARD_STATE state;
        al_get_keyboard_state(&state);

//salvar o jogo
        if (al_key_down(&state, ALLEGRO_KEY_S)){
            salvar(a);
        }
//carregar o jogo
        if (al_key_down(&state, ALLEGRO_KEY_C)){
            carregar(a);
        }


        if(a->gameover == true){
            al_draw_bitmap(a->gameover_screen, 0, 0, 0);
        }
        else if (a->titulo == true){
            al_draw_bitmap(a->titulo_screen, 0, 0, 0);
            if (al_key_down(&state, ALLEGRO_KEY_ENTER)){
                a->titulo = false;
                a->instrucoes = true;
            }
        }
        else if (a->instrucoes == true){
            al_draw_bitmap(a->titulo_screen, 0, 0, 0);
            al_draw_bitmap(a->imagem_instrucoes, 20, 15, 0);
            if (al_key_down(&state, ALLEGRO_KEY_ENTER) && a->apertando_enter == false){
                a->instrucoes = false;
                al_set_audio_stream_playing(a->musica_titulo, false);
                al_attach_audio_stream_to_mixer(a->musica, al_get_default_mixer());
                al_set_audio_stream_playing(a->musica, true);
            }
        }
        else if (a->fim == true){
            al_draw_bitmap(a->fim_screen, 0, 0, 0);
        }
        else{
            //Desenhar o cenario
            if(a->salaatual == 1){
                al_draw_bitmap(a->cena1, 0, 0, 0);

                if(a->abriuporta == false){
                    al_draw_bitmap(a->portatrancada, 108, 16, 0);
                }
            }
            if(a->salaatual == 2){
                al_draw_bitmap(a->cena2, 0, 0, 0);
            }
            if(a->salaatual == 3){
                al_draw_bitmap(a->cena3, 0, 0, 0);
                boss_draw(&a->b);
            }

            personagem_draw(&a->p);

            if(a->salaatual == 2){
                morcego_draw(&a->m);
                chave_draw(&a->ch);
            }
        }

        al_flip_display();

        a->apertando_enter = al_key_down(&state, ALLEGRO_KEY_ENTER);
    }
}


bool colidiu_personagem_morcego(personagem *p, morcego *m){
    if(m->vivo == true){
        if(m->x+24-8 > p->x+8 && m->x+8 < p->x+16){ // se a direita do morcego for > que a esquerda do personagem e ao mesmo tempo a esq. é menor que a dir., é pq um tá dentro do outro horizontalmente.
            if(m->y+32-8 > p->y+16 && m->y+8 < p->y+28){ // // se a parte inferior do morcego for > que a superior do personagem e ao mesmo tempo a inferior do morcego é < que a superior do personagem, é pq um tá dentro do outro verticalmente.
                return true;
            }
        }
    }

    return false;
}

bool colidiu_flecha_morcego(flecha *f, morcego *m){
    if(f->viva == true && m->vivo == true){
        if(f->x+24-8 > m->x+8 && f->x+8 < m->x+16){
            if(f->y+32-8 > m->y+16 && f->y+8 < m->y+28){
                return true;
            }
        }
    }

    return false;
}

bool colidiu_personagem_chave(personagem *p, chave *ch){
    if(ch->vivo == true){
        if(ch->x+16-4 > p->x+8 && ch->x+4 < p->x+16){
            if(ch->y+16-4 > p->y+16 && ch->y+4 < p->y+28){
                return true;
            }
        }
    }

    return false;
}

bool personagem_tentou_descer(personagem *p){
    if(p->y >= 98 && p->x+16 > 112 && p->x+8 < 127){
        return true;
    }

    return false;
}

bool personagem_tentou_subir(personagem *p){
    if(p->y <= 16 && p->x+16 > 112 && p->x+8 < 127){
        return true;
    }

    return false;
}

bool colidiu_personagem_fogo(personagem *p, fogo *f){
    if(f->vivo == true){
        if(f->x+14 > p->x+8 && f->x+2 < p->x+16){
            if(f->y+14 > p->y+16 && f->y+2 < p->y+28){
                return true;
            }
        }
    }

    return false;
}

bool colidiu_flecha_boss(flecha *f, boss *b){
    if(f->viva == true){
        if(f->x+24-8 > b->x+9 && f->x+8 < b->x+23){
            if(f->y+32-8 > b->y+9 && f->y+8 < b->y+39){
                return true;
            }
        }
    }

    return false;
}

void salvar (allegro_stuff *a){
    FILE *f = fopen ("jogo.txt", "w");

    fprintf (f,"%i\n", a->salaatual);
    fprintf (f,"%f %f\n", a->p.x, a->p.y);
    fprintf (f, "%f %f\n", a->m.x, a->m.y);
    fprintf (f, "%d\n", a->ch.vivo);
    fprintf (f, "%d\n", a->pegouchave);
    fprintf (f, "%d\n", a->m.vivo);
    fprintf (f, "%d\n", a->abriuporta);

    fclose(f);

    a->closed = true;
}

void carregar (allegro_stuff *a){
    FILE *f = fopen ("jogo.txt", "r");

    int valor;

    fscanf (f, "%i", &valor);
    fscanf (f,"%f %f", &a->p.x, &a->p.y);
    fscanf (f, "%f %f", &a->m.x, &a->m.y);
    fscanf (f, "%d", &a->ch.vivo);
    fscanf (f, "%d", &a->pegouchave);
    fscanf (f, "%d", &a->m.vivo);
    fscanf (f, "%d", &a->abriuporta);

    a->salaatual = valor;

    printf("Sala: %d\n", a->salaatual);
    printf("Player: x = %f\ty = %f\n", a->p.x, a->p.y);

    fclose(f);

}
