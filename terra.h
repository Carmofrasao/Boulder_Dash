/*programa feito por Anderson Aparecido do Carmo Frasão
GRR20204069 
funcoes para a biblioteca terra.*/

#ifndef _TERRA_H
#define _TERRA_H

void terras_init();
/*iniciando as variaveis para a terra*/

void terras_update(POSSI **tela);
/*atualizando as terras*/

void verifica_terra();

void terras_draw();
/*desenhando a terra*/

void destroi_terra();

#endif
