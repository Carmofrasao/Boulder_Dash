/*programa feito por Anderson Aparecido do Carmo Frasão
GRR20204069 
biblioteca para trabalhar com as moedas*/

#include<allegro5/allegro5.h>
#include<allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include<stdio.h>
#include<stdlib.h>
#include"geral.h"
#include"rock.h"
#include"fx.h"
#include"coin.h"

#define COIN_W 8
#define COIN_H 8

ALLEGRO_BITMAP* moeda;

void moedas_init()
/*iniciando as variaveis relacionadas a moeda*/
{
	num_moeda = 0;
	must_init(al_init_image_addon(), "image addon");
	moeda = al_load_bitmap("./resources/moeda.png");
	must_init(moeda, "moeda");
    for(int i = 0; i < COIN_N; i++)
   	{
        moedas[i].used = false;
        moedas[i].ja_usou = false;
        moedas[i].caindo = false;
		moedas[i].x = 0;
		moedas[i].y = 0;
	}
	score = 0;
}

bool moedas_collide2(bool person, int x, int y, int w, int h)
/*verifica se uma pedra colidiu em outro objeto*/
{
    for(int i = 0; i < COIN_N; i++)
    {
        if((!moedas[i].used) || (!moedas[i].caindo))
            continue;

        int sw, sh;
        if(moedas->used)
        {
            sw = COIN_W;
            sh = COIN_H;
        }

        if(collide(x, y, x+w, y+h, moedas[i].x, moedas[i].y, moedas[i].x+sw, moedas[i].y+sh))
        {
            fx_add(true, moedas[i].x + (sw / 2), moedas[i].y + (sh / 2));
            moedas[i].used = false;
            for(int a = moedas[i].y-8; a <= moedas[i].y+8; a++)
			{
		    	for(int b = moedas[i].x-8; b <= moedas[i].x+8; b++)
		    	{
		    	    tela[a][b].moeda = 0;
		    	}
			}
            return true;
        }
    }

    return false;
}

bool moedas_collide(int x, int y, int w, int h)
/*verificando se houve colisao entre a moeda e outro objeto*/
{
    for(int i = 0; i < COIN_N; i++)
    {
        if(!moedas[i].used && moedas[i].ja_usou)
            continue;

        int sw, sh;
        if(moedas->used)
        {
            sw = COIN_W;
            sh = COIN_H;
        }

        if(collide(x, y, x+w, y+h, moedas[i].x, moedas[i].y, moedas[i].x+sw, moedas[i].y+sh))
		{
		    al_play_sample(pega_moeda, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		    moedas[i].used = false;
		    moedas[i].ja_usou = true;
		    for(int a = moedas[i].y-8; a <= moedas[i].y+8; a++)
		    {
		    	for(int b = moedas[i].x-8; b <= moedas[i].x+8; b++)
		    	{
		    	    tela[a][b].moeda = 0;
		    	}
		    }
		    return true;
		}
	}
    return false;
}

void moedas_update(POSSI **tela, int posi_moedax[], int posi_moeday[])
/*atualizando a moeda*/
{
	for(int i = 0; i < COIN_N; i++)
	{
		if((!moedas[i].used) && (!moedas[i].ja_usou))
		{
			int aux = posi_moedax[i];
            int aux1 = posi_moeday[i];
            
			moedas[i].x = aux;
			moedas[i].y = aux1;
			moedas[i].used = true;
			for(int a = aux1-8; a <= aux1+8; a++)
            {
            	for(int b = aux-8; b <= aux+8; b++)
                {
                	tela[a][b].moeda = 1;
                }
            }
			continue;
		}
	}
}

void verifica_moeda()
{
	for(int i = 0; i < COIN_N; i++)
	{
		if(!moedas[i].used && moedas[i].ja_usou)
			continue;
			
		/*verificando se esta caindo*/
		if((!moedas[i].caindo) && (tela[moedas[i].y+9][moedas[i].x].pessoa == 1))
       	{
       		
		}
		/*verificando se pode ir para o lado (tanto para a direita quanto para a esquerda)*/
		else if(((tela[moedas[i].y+9][moedas[i].x].pedra == 1) || (tela[moedas[i].y+9][moedas[i].x].moeda == 1)) && (tela[moedas[i].y][moedas[i].x-16].pedra == 0) && (tela[moedas[i].y][moedas[i].x-16].terra == 0) && (tela[moedas[i].y][moedas[i].x-16].moeda == 0) && (tela[moedas[i].y][moedas[i].x-16].muro == 0) && (tela[moedas[i].y+9][moedas[i].x-16].pedra == 0) && (tela[moedas[i].y+9][moedas[i].x-16].terra == 0) && (tela[moedas[i].y+9][moedas[i].x-16].moeda == 0) && (tela[moedas[i].y+9][moedas[i].x-16].muro == 0) && (tela[moedas[i].y][moedas[i].x-16].pessoa == 0))
		{
			if (!(frames % 4))
			{
            	for(int a = moedas[i].y-8; a <= moedas[i].y+8; a++)
        		{
            		for(int b = moedas[i].x-8; b <= moedas[i].x+8; b++)
            		{
            		    tela[a][b].moeda = 0;
            		}
        		}	
        
      			moedas[i].x -= 16;
      		
       			for(int a = moedas[i].y-8; a <= moedas[i].y+8; a++)
       			{	
       	    		for(int b = moedas[i].x-8; b <= moedas[i].x+8; b++)
       	    		{
       	    		    tela[a][b].moeda = 1;
       	    		}
    			}
    		}
		}
		else if (((tela[moedas[i].y+9][moedas[i].x].pedra == 1) || (tela[moedas[i].y+9][moedas[i].x].moeda == 1)) && (tela[moedas[i].y][moedas[i].x+20].pedra == 0) && (tela[moedas[i].y][moedas[i].x+20].terra == 0) && (tela[moedas[i].y][moedas[i].x+20].moeda == 0) && (tela[moedas[i].y][moedas[i].x+20].muro == 0) && (tela[moedas[i].y+9][moedas[i].x+20].pedra == 0) && (tela[moedas[i].y+9][moedas[i].x+20].terra == 0) && (tela[moedas[i].y+9][moedas[i].x+20].moeda == 0) && (tela[moedas[i].y+9][moedas[i].x+20].muro == 0) && (tela[moedas[i].y][moedas[i].x+20].pessoa == 0))
		{
			if(!(frames % 4))
			{
				for(int a = moedas[i].y-8; a <= moedas[i].y+8; a++)
        		{
            		for(int b = moedas[i].x-8; b <= moedas[i].x+8; b++)
            		{
            		    tela[a][b].moeda = 0;
            		}
        		}
        
      			moedas[i].x += 16;
      		
       			for(int a = moedas[i].y-8; a <= moedas[i].y+8; a++)
       			{	
       	    		for(int b = moedas[i].x-8; b <= moedas[i].x+8; b++)
       	    		{
       	    		    tela[a][b].moeda = 1;
       	    		}
    			}
    		}	
		}
		/*verificando se pode cair*/
		else if((tela[moedas[i].y+8][moedas[i].x].terra == 0) && (tela[moedas[i].y+8][moedas[i].x].muro == 0) && (tela[moedas[i].y+9][moedas[i].x].moeda == 0) && (moedas[i].y < BUFFER_H-32) && (tela[moedas[i].y+8][moedas[i].x].pedra == 0))
        {	
        	moedas[i].caindo = true;
            for(int a = moedas[i].y-8; a <= moedas[i].y+8; a++)
            {
                for(int b = moedas[i].x-8; b <= moedas[i].x+8; b++)
                {
                	tela[a][b].moeda = 0;
                }
            }
            moedas[i].y += 1;
            for(int a = moedas[i].y-8; a <= moedas[i].y+8; a++)
            {
                for(int b = moedas[i].x-8; b <= moedas[i].x+8; b++)
                {
                	tela[a][b].moeda = 1;
                }
            }
        }
        else
        {
        	moedas[i].caindo = false;
        }
    }
}

void moedas_draw()
/*desenhando a moeda*/
{
	for(int i = 0; i < COIN_N; i++)
	{
		if(!moedas[i].used && moedas[i].ja_usou)
			continue;
		al_draw_bitmap(moeda, moedas[i].x, moedas[i].y, 0);
	}
}

void destroi_moeda()
{
	al_destroy_bitmap(moeda);
}
