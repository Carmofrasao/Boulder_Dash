/*programa feito por Anderson Aparecido do Carmo Frasão
GRR20204069 
funcoes e estrutura para todo o programa*/

#ifndef _GERAL_H
#define _GERAL_H

#include <allegro5/allegro_audio.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro5.h>
#include<allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>

#define BUFFER_W 640
#define BUFFER_H 368
#define TERRA_N (BUFFER_W/16) * (BUFFER_H/16)

#define COIN_N 25
#define ROCK_N 36

#define PERSON_W 8
#define PERSON_H 8

typedef enum TERRA_TYPE
{
	TERRA_TYPE_TERRA,
	TERRA_TYPE_N
} TERRA_TYPE;

typedef struct terrao
{
	int x, y;
	TERRA_TYPE type;
	bool used;
	bool ja_usou;
} terrao;
/*estrutura para a terra*/
terrao terras[TERRA_N];

typedef struct POSSI
{
	int muro;
	int terra;
	int pedra;
	int moeda;
	int porta;
	int pessoa;
}POSSI;
/*estrutura para as possibilidades de objetos que estarao na tela*/
POSSI **tela;

typedef struct PERSON
{
    int x, y;
    int respawn_timer;
    int invincible_timer;
    int lado;
    bool vivo;
} PERSON;
/*estrutura para o player*/
PERSON person;

typedef struct coin
{
	int x, y;
	bool used;
	bool ja_usou;
	bool caindo;
} coin;
/*estrutura para a moeda*/
coin moedas[COIN_N];

typedef struct ROCK
{
    int x, y;
    bool used;
    bool caindo;
} ROCK;
/*estrutura para as pedras*/
ROCK rocks[ROCK_N];

long score;
int num_moeda;
float time_left;
long frames;

ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* buffer;

ALLEGRO_BITMAP* porta;
ALLEGRO_BITMAP* muro_prin;
ALLEGRO_BITMAP* muro_sec;
ALLEGRO_BITMAP* texture_menu;
ALLEGRO_BITMAP* surpresa;
ALLEGRO_FONT *score_text, *pause_text;

ALLEGRO_TIMER* timer;
ALLEGRO_TIMER *miner_timer;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_DISPLAY* disp;
ALLEGRO_EVENT event;

ALLEGRO_SAMPLE* final;
ALLEGRO_SAMPLE* morte;
ALLEGRO_SAMPLE* pega_moeda;
ALLEGRO_SAMPLE* carregamento;

#endif
