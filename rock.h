/*programa feito por Anderson Aparecido do Carmo Frasão
GRR20204069 
funcoes para a biblioteca rock.c*/

#ifndef _ROCK_H
#define _ROCK_H

#include"geral.h"

int between(int lo, int hi);
/*funcao para criar valores aleatorios*/

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);
/*verifica se um objeto colidiu em outro*/

bool rocks_collide(bool person, int x, int y, int w, int h);
/*verifica se uma pedra colidiu em outro objeto*/

void rocks_init();
/*iniciando as variaveis relacionadas as pedras*/

void rocks_update(POSSI **tela);
/*atualizando as pedras*/

void verifica_pedra();

void rocks_draw();
/*desenhando as pedras*/

void destroi_rock();

#endif
