/*programa feito por Anderson Aparecido do Carmo Frasão
GRR20204069
funcoes para a biblioteca coin.c*/

#ifndef _COIN_H
#define _COIN_H

void moedas_init();
/*iniciando as variaveis relacionadas a moeda*/

bool moedas_collide2(bool person, int x, int y, int w, int h);

bool moedas_collide(int x, int y, int w, int h);
/*verificando se houve colisao entre a moeda e outro objeto*/

void moedas_update(POSSI **tela, int posi_moedax[], int posi_moeday[]);
/*atualizando a moeda*/

void verifica_moeda();

void moedas_draw();
/*desenhando a moeda*/

void destroi_moeda();

#endif
