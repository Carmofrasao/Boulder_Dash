/*programa feito por Anderson Aparecido do Carmo Frasão
GRR20204069 
biblioteca para trabalhar com as pedras*/

#include<allegro5/allegro5.h>
#include<allegro5/allegro_image.h>
#include<stdio.h>
#include<stdlib.h>
#include"geral.h"
#include"rock.h"
#include"fx.h"

#define ROCK_W 8
#define ROCK_H 8

ALLEGRO_BITMAP* pedra;

int between(int lo, int hi)
/*funcao para criar valores aleatorios*/
{
    return lo + (rand() % (hi - lo));
}

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
/*verifica se um objeto colidiu em outro*/
{
    if(ax1 > bx2) return false;
    if(ax2 < bx1) return false;
    if(ay1 > by2) return false;
    if(ay2 < by1) return false;

    return true;
}

bool rocks_collide(bool person, int x, int y, int w, int h)
/*verifica se uma pedra colidiu em outro objeto*/
{
    for(int i = 0; i < ROCK_N; i++)
    {
        if(!rocks[i].used)
            continue;

        int sw, sh;
        if(rocks->used)
        {
            sw = ROCK_W;
            sh = ROCK_H;
        }

        if(collide(x, y, x+w, y+h, rocks[i].x, rocks[i].y, rocks[i].x+sw, rocks[i].y+sh))
        {
            fx_add(true, rocks[i].x + (sw / 2), rocks[i].y + (sh / 2));
            rocks[i].used = false;
            for(int a = rocks[i].y-8; a <= rocks[i].y+8; a++)
			{
		    	for(int b = rocks[i].x-8; b <= rocks[i].x+8; b++)
		    	{
		    	    tela[a][b].pedra = 0;
		    	}
			}
            return true;
        }
    }

    return false;
}

void rocks_init()
/*iniciando as variaveis relacionadas as pedras*/
{
	must_init(al_init_image_addon(), "image addon");
	pedra = al_load_bitmap("./resources/pedra.png");
	must_init(pedra, "pedra");
    for(int i = 0; i < ROCK_N; i++)
    {
        rocks[i].used = false;
        rocks[i].caindo = false;
		rocks[i].x = 0;
		rocks[i].y = 0;
	}
}

void rocks_update(POSSI **tela)
/*atualizando as pedras*/
{
	FILE *coordenadas = fopen("./resources/coordenadas_pedras.txt", "r");
	if ( ! coordenadas )
  	{
		perror ("Erro ao abrir arquivo") ;
		exit (1) ;
	}
    for(int i = 0; i < ROCK_N; i++)
    {
        if(!rocks[i].used)
        {
            int aux = 0;
            int aux1 = 0;
            fscanf(coordenadas, "%d %d\n", &aux, &aux1);
			rocks[i].x = aux;
            rocks[i].y = aux1;
            rocks[i].used = true;
            for(int a = aux1-8; a <= aux1+8; a++)
            {
                for(int b = aux-8; b <= aux+8; b++)
                {
                	tela[a][b].pedra = 1;
                }
            }
        }
    }
    fclose(coordenadas);
}

void verifica_pedra()
{
	for(int i = 0; i < ROCK_N; i++)
    {
        if(!rocks[i].used)
            continue;
       	if((!rocks[i].caindo) && (tela[rocks[i].y+9][rocks[i].x].pessoa == 1))
       	/*verifica se esta caindo*/
       	{
       		
		}
		/*verifica se pode ir para o lado (tanto esquerda quanto direita)*/
		else if(((tela[rocks[i].y+9][rocks[i].x].pedra == 1) || (tela[rocks[i].y+9][rocks[i].x].moeda == 1)) && (tela[rocks[i].y][rocks[i].x-16].pedra == 0) && (tela[rocks[i].y][rocks[i].x-16].terra == 0) && (tela[rocks[i].y][rocks[i].x-16].moeda == 0) && (tela[rocks[i].y][rocks[i].x-16].muro == 0) && (tela[rocks[i].y+9][rocks[i].x-16].pedra == 0) && (tela[rocks[i].y+9][rocks[i].x-16].terra == 0) && (tela[rocks[i].y+9][rocks[i].x-16].moeda == 0) && (tela[rocks[i].y+9][rocks[i].x-16].muro == 0) && (tela[rocks[i].y][rocks[i].x-16].pessoa == 0))
		{
			if (!(frames % 4))
			{
            	for(int a = rocks[i].y-8; a <= rocks[i].y+8; a++)
        		{
            		for(int b = rocks[i].x-8; b <= rocks[i].x+8; b++)
            		{
            		    tela[a][b].pedra = 0;
            		}
        		}	
        
      			rocks[i].x -= 16;
      		
       			for(int a = rocks[i].y-8; a <= rocks[i].y+8; a++)
       			{	
       	    		for(int b = rocks[i].x-8; b <= rocks[i].x+8; b++)
       	    		{
       	    		    tela[a][b].pedra = 1;
       	    		}
    			}
    		}
		}
		else if (((tela[rocks[i].y+9][rocks[i].x].pedra == 1) || (tela[rocks[i].y+9][rocks[i].x].moeda == 1)) && (tela[rocks[i].y][rocks[i].x+20].pedra == 0) && (tela[rocks[i].y][rocks[i].x+20].terra == 0) && (tela[rocks[i].y][rocks[i].x+20].moeda == 0) && (tela[rocks[i].y][rocks[i].x+20].muro == 0) && (tela[rocks[i].y+9][rocks[i].x+20].pedra == 0) && (tela[rocks[i].y+9][rocks[i].x+20].terra == 0) && (tela[rocks[i].y+9][rocks[i].x+20].moeda == 0) && (tela[rocks[i].y+9][rocks[i].x+20].muro == 0) && (tela[rocks[i].y][rocks[i].x+20].pessoa == 0))
		{
			if(!(frames % 4))
			{
				for(int a = rocks[i].y-8; a <= rocks[i].y+8; a++)
        		{
            		for(int b = rocks[i].x-8; b <= rocks[i].x+8; b++)
            		{
            		    tela[a][b].pedra = 0;
            		}
        		}
        
      			rocks[i].x += 16;
      		
       			for(int a = rocks[i].y-8; a <= rocks[i].y+8; a++)
       			{	
       	    		for(int b = rocks[i].x-8; b <= rocks[i].x+8; b++)
       	    		{
       	    		    tela[a][b].pedra = 1;
       	    		}
    			}
    		}	
		}
		/*verifica se pode cair*/
		else if((tela[rocks[i].y+8][rocks[i].x].terra == 0) && (tela[rocks[i].y+9][rocks[i].x].muro == 0) && (tela[rocks[i].y+8][rocks[i].x].moeda == 0) && (rocks[i].y < BUFFER_H-32) && (tela[rocks[i].y+9][rocks[i].x].pedra == 0))
        {	
        	rocks[i].caindo = true;
            for(int a = rocks[i].y-8; a <= rocks[i].y+8; a++)
            {
                for(int b = rocks[i].x-8; b <= rocks[i].x+8; b++)
                {
                	tela[a][b].pedra = 0;
                }
            }
            rocks[i].y += 1;
            for(int a = rocks[i].y-8; a <= rocks[i].y+8; a++)
            {
                for(int b = rocks[i].x-8; b <= rocks[i].x+8; b++)
                {
                	tela[a][b].pedra = 1;
                }
            }
        }
        else
        {
        	rocks[i].caindo = false;
        }
    }
}

void rocks_draw()
/*desenhando as pedras*/
{
    for(int i = 0; i < ROCK_N; i++)
    {
        if(!rocks[i].used)
            continue;
    	al_draw_bitmap(pedra, rocks[i].x, rocks[i].y, 0);
    }
}

void destroi_rock()
{
	al_destroy_bitmap(pedra);
}
