/*programa feito por Anderson Aparecido do Carmo Frasão
GRR20204069 
biblioteca para trabalhar com a terra*/

#include<allegro5/allegro5.h>
#include<allegro5/allegro_image.h>
#include<stdio.h>
#include<stdlib.h>
#include"geral.h"
#include"rock.h"
#include"terra.h"
#include"fx.h"

ALLEGRO_BITMAP* terra;

void terras_init()
/*iniciando as variaveis para a terra*/
{
	must_init(al_init_image_addon(), "image addon");
	terra = al_load_bitmap("./resources/terra.jpg");
	must_init(terra, "terra");
    for(int i = 0; i < TERRA_N; i++)
   	{
        terras[i].used = false;
        terras[i].ja_usou = false;
		terras[i].x = 0;
		terras[i].y = 0;
	}
}

void terras_update(POSSI **tela)
/*atualizando as terras*/
{
	int i = 0;
	for(int y = 48; y < BUFFER_H-16; y+=16)
	{
		for(int x = 16; x < BUFFER_W-16; x+=16)
		{
			if((!terras[i].used) && (!terras[i].ja_usou))
			{
				int aux = x;
        	    int aux1 = y;
        	    
				if((tela[aux1][aux].muro == 0) && (tela[aux1][aux].pedra == 0) && (tela[aux1][aux].moeda == 0) && (!terras[i].used))
				/*verificando se o local e apropriado para imprimir a terra*/
				{
					int l = 0;
					for(int i = 0; i <= 4; i++)
					{
						if ((aux >= 60) && (aux <= 76) && (aux1 >= 32) && (aux1 <= 40))
						/*separando o local para a entrada*/
						{
							l = 1;
							break;
						}
						else if((aux >= BUFFER_W-76) && (aux <= BUFFER_W-60) && (aux1 >= BUFFER_H-56) && (aux1 <= BUFFER_H-48))
						/*separando o local para a saida*/
						{
							l = 1;
							break;
						}
						else if((tela[aux1+(2*i)][aux].muro!=0) && (tela[aux1-(2*i)][aux].muro!=0) && (tela[aux1][aux+(2*i)].muro != 0) && (tela[aux1][aux-(2*i)].muro != 0) && (tela[aux1+(2*i)][aux].pedra != 0) && (tela[aux1-(2*i)][aux].pedra != 0) && (tela[aux1][aux+(2*i)].pedra != 0) && (tela[aux1][aux-(2*i)].pedra != 0) && (tela[aux1+(2*i)][aux].moeda != 0) && (tela[aux1-(2*i)][aux].moeda != 0) && (tela[aux1][aux+(2*i)].moeda != 0) && (tela[aux1][aux-(2*i)].moeda != 0))
						/*verificando se nao pode imprimir no local*/
						{
							l = 1;
							break;
						}
					}
					
					if(l == 0)
					{
						terras[i].x = aux;
						terras[i].y = aux1;
						terras[i].used = true;
						for(int a = aux1-8; a <= aux1+8; a++)
        	        	{
        	        		for(int b = aux-8; b <= aux+8; b++)
        	        		{
        	        			tela[a][b].terra = 1;
        	        		}
        	        	}
        	        	i++;
					}	
				}
				continue;
			}
		}
	}
}

void verifica_terra()
{
	for(int i = 0; i < TERRA_N; i++)
	{	
		if(((person.x == terras[i].x) && (person.y+4 == terras[i].y)) || ((person.x-4 == terras[i].x) && (person.y == terras[i].y)) || ((person.x == terras[i].x) && (person.y-4 == terras[i].y)) || ((person.x+4 == terras[i].x) && (person.y == terras[i].y)))
		/*se o player encostou na terra ela desaparece*/
		{
			terras[i].used = false;
			terras[i].ja_usou = true;
			for(int a = terras[i].y-8; a <= terras[i].y+8; a++)
        	{
        	    for(int b = terras[i].x-8; b <= terras[i].x+8; b++)
        	    {
        	        tela[a][b].terra = 0;
        		}
        	}
		}
	}
}

void terras_draw()
/*desenhando a terra*/
{
	for(int i = 0; i < TERRA_N; i++)
	{	
		if(!terras[i].used)
			continue;
		al_draw_bitmap(terra, terras[i].x, terras[i].y, 0);
	}
}

void destroi_terra()
{
	al_destroy_bitmap(terra);
}
