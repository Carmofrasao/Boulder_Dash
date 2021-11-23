/*programa feito por Anderson Aparecido do Carmo Frasão
GRR20204069 
biblioteca para os efeitos especiais*/

#include<allegro5/allegro5.h>
#include<allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include<stdio.h>
#include"fx.h"
#include"geral.h"

#define PERSON_ROCK_W 2
#define PERSON_ROCK_H 9

#define LIFE_W 6
#define LIFE_H 6

#define ROCK_W 16
#define ROCK_H 16

#define EXPLOSION_FRAMES 4
#define SPARKS_FRAMES    3

#define ROCK_PEDRA_W      16
#define ROCK_PEDRA_H      16

#define FX_N 128
FX fx[FX_N];

SPRITES sprites;

void must_init(bool test, const char *description)
/*funcao para teste de inicializacao*/
{
    if(test) return;

    printf("Não foi possivel inicializar %s\n", description);
    exit(1);
}

void fx_init()
{
    for(int i = 0; i < FX_N; i++)
        fx[i].used = false;
}

void audio_init()
/*inicializando musicas*/
{
    must_init(al_install_audio(), "audio");
	must_init(al_init_acodec_addon(), "audio codecs");
	must_init(al_reserve_samples(4), "reserve samples");

    carregamento = al_load_sample("./resources/carregamento.wav");
	must_init(carregamento, "carregamento");

	final = al_load_sample("./resources/final.wav");
	must_init(final, "final");

	morte = al_load_sample("./resources/morte.wav");
	must_init(morte, "morte");

	pega_moeda = al_load_sample("./resources/pega_moeda.wav");
	must_init(pega_moeda, "pega_moeda");
}

void fx_add(bool spark, int x, int y)
/*funcao para o efeito de explosao*/
{
    if(!spark)
        al_play_sample(morte, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

    for(int i = 0; i < FX_N; i++)
    {
        if(fx[i].used)
            continue;

        fx[i].x = x;
        fx[i].y = y;
        fx[i].frame = 0;
        fx[i].spark = spark;
        fx[i].used = true;
        return;
    }
}

void fx_update()
/*atualizando os efeitos em tempo de execucao*/
{
    for(int i = 0; i < FX_N; i++)
    {
        if(!fx[i].used)
            continue;

        fx[i].frame++;

        if((!fx[i].spark && (fx[i].frame == (EXPLOSION_FRAMES * 2)))
        || ( fx[i].spark && (fx[i].frame == (SPARKS_FRAMES * 2)))
        )
            fx[i].used = false;
    }
}

void fx_draw()
/*desenhando os efeitos*/
{
    for(int i = 0; i < FX_N; i++)
    {
        if(!fx[i].used)
            continue;

        int frame_display = fx[i].frame / 2;
        ALLEGRO_BITMAP* bmp =
            fx[i].spark
            ? sprites.sparks[frame_display]
            : sprites.explosion[frame_display]
        ;

        int x = fx[i].x - (al_get_bitmap_width(bmp) / 2);
        int y = fx[i].y - (al_get_bitmap_height(bmp) / 2);
        al_draw_bitmap(bmp, x, y, 0);
    }
}

void sprites_init()
/*distribuindo os efeitos para suas devidas variaveis*/
{
    sprites._sheet = al_load_bitmap("./resources/spritesheet.png");
    must_init(sprites._sheet, "spritesheet");

    sprites.person = sprite_grab(0, 0, PERSON_W, PERSON_H);

    sprites.life = sprite_grab(0, 14, LIFE_W, LIFE_H);

    sprites.person_rock[0] = sprite_grab(13, 0, PERSON_ROCK_W, PERSON_ROCK_H);
    sprites.person_rock[1] = sprite_grab(16, 0, PERSON_ROCK_W, PERSON_ROCK_H);

    sprites.rock_v[0] = sprite_grab(19, 10, ROCK_PEDRA_W, ROCK_PEDRA_H);

    sprites.rock = sprite_grab(13, 10, ROCK_W, ROCK_H);

    sprites.explosion[0] = sprite_grab(33, 10, 9, 9);
    sprites.explosion[1] = sprite_grab(43, 9, 11, 11);
    sprites.explosion[2] = sprite_grab(46, 21, 17, 18);
    sprites.explosion[3] = sprite_grab(46, 40, 17, 17);

    sprites.sparks[0] = sprite_grab(34, 0, 10, 8);
    sprites.sparks[1] = sprite_grab(45, 0, 7, 8);
    sprites.sparks[2] = sprite_grab(54, 0, 9, 8);

    sprites.powerup[0] = sprite_grab(0, 49, 9, 12);
    sprites.powerup[1] = sprite_grab(10, 49, 9, 12);
    sprites.powerup[2] = sprite_grab(20, 49, 9, 12);
    sprites.powerup[3] = sprite_grab(30, 49, 9, 12);
}

ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h)
/*inicializando os efeitos*/
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprites._sheet, x, y, w, h);
    must_init(sprite, "sprite grab");
    return sprite;
}

void sprites_deinit()
/*destruindo os efeitos*/
{
    al_destroy_bitmap(sprites.person);

    al_destroy_bitmap(sprites.person_rock[0]);
    al_destroy_bitmap(sprites.person_rock[1]);

    al_destroy_bitmap(sprites.rock_v[0]);

    al_destroy_bitmap(sprites.sparks[0]);
    al_destroy_bitmap(sprites.sparks[1]);
    al_destroy_bitmap(sprites.sparks[2]);

    al_destroy_bitmap(sprites.explosion[0]);
    al_destroy_bitmap(sprites.explosion[1]);
    al_destroy_bitmap(sprites.explosion[2]);
    al_destroy_bitmap(sprites.explosion[3]);

    al_destroy_bitmap(sprites.powerup[0]);
    al_destroy_bitmap(sprites.powerup[1]);
    al_destroy_bitmap(sprites.powerup[2]);
    al_destroy_bitmap(sprites.powerup[3]);

    al_destroy_bitmap(sprites._sheet);
}

void audio_deinit()
/*destruindo as musicas*/
{
    al_destroy_sample(carregamento);
	al_destroy_sample(final);
	al_destroy_sample(morte);
	al_destroy_sample(pega_moeda);
}
