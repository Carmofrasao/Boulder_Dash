/*programa feito por Anderson Aparecido do Carmo Frasão
GRR20204069 
funcoes para a biblioteca person.c*/

#ifndef _PERSON_H
#define _PERSON_H

void person_init();
/*inicializando as variaveis do player*/

void move_esquerda();
/*funcao para movimentar o player para a esquerda*/

void move_direita();
/*funcao para movimentar o player para a direita*/

void move_cima();
/*funcao para movimentar o player para cima*/

void move_baixo();
/*funcao para movimentar o player para baixo*/

void person_update();
/*atualiza o player*/

void person_draw();
/*desenha o player*/

void destroi_miner();

#endif
