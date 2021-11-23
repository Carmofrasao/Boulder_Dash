/*programa feito por Anderson Aparecido do Carmo Frasão
GRR20204069 
funcoes e estrutura para a biblioteca fx.c*/

#ifndef _FX_H
#define _FX_H

#include<allegro5/allegro5.h>
#include<allegro5/allegro_image.h>

#define EXPLOSION_FRAMES 4
#define SPARKS_FRAMES    3

typedef struct SPRITES
{
    ALLEGRO_BITMAP* _sheet;

    ALLEGRO_BITMAP* person;
    ALLEGRO_BITMAP* person_rock[2];
    ALLEGRO_BITMAP* life;

    ALLEGRO_BITMAP* rock_v[3];
    ALLEGRO_BITMAP* rock;

    ALLEGRO_BITMAP* explosion[EXPLOSION_FRAMES];
    ALLEGRO_BITMAP* sparks[SPARKS_FRAMES];

    ALLEGRO_BITMAP* powerup[4];
} SPRITES;

typedef struct FX
{
    int x, y;
    int frame;
    bool spark;
    bool used;
} FX;

void must_init(bool test, const char *description);
/*funcao para teste de inicializacao*/

void fx_init();

void audio_init();
/*inicializando musicas*/

void fx_add(bool spark, int x, int y);
/*funcao para o efeito de explosao*/

void fx_update();
/*atualizando os efeitos em tempo de execucao*/

void fx_draw();
/*desenhando os efeitos*/

void sprites_init();
/*distribuindo os efeitos para suas devidas variaveis*/

ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h);
/*inicializando os efeitos*/

void sprites_deinit();
/*destruindo os efeitos*/

void audio_deinit();
/*destruindo as musicas*/

#endif
