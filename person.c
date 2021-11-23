/*programa feito por Anderson Aparecido do Carmo Frasão
GRR20204069 
biblioteca para trabalhar com o player*/

#include<allegro5/allegro5.h>
#include<allegro5/allegro_image.h>
#include<stdio.h>
#include<stdlib.h>
#include"fx.h"
#include"rock.h"
#include"person.h"
#include"terra.h"
#include"coin.h"
#include"geral.h"

#define PERSON_SPEED 16
#define PERSON_MAX_X (BUFFER_W - 3.5*PERSON_W)
#define PERSON_MAX_Y (BUFFER_H - 4*PERSON_H)

#define KEY_SEEN     1
#define KEY_RELEASED 2

unsigned char key[ALLEGRO_KEY_MAX];

float x, y;

ALLEGRO_BITMAP* miner;

void person_init()
/*inicializando as variaveis do player*/
{
	memset(key, 0, sizeof(key));
	x = 100;
    y = 100;
	must_init(al_init_image_addon(), "image addon");
	miner = al_load_bitmap("./resources/miner.png");
	must_init(miner, "miner");
    person.x = 64;
    person.y = 64;
    person.respawn_timer = 10;
    person.invincible_timer = 0;
    person.lado = 0;
    person.vivo = true;
}

void move_esquerda()
/*funcao para movimentar o player para a esquerda*/
{
	int aux = -1;
	int l;
	for(int i = 0; i < ROCK_N; i++)
	/*buscando alguma rocha do lado esquerdo*/
    {
    	for(l = 0; l < 16; l++)
    	{
    		for(int k = 0; k < 4; k++)
    		{
    			if((person.x-l == rocks[i].x) && ((person.y+k == rocks[i].y) || (person.y-k == rocks[i].y)))
    			{
    				aux = i;
    				break;
    			}
    		}
    	}
	}
	if((aux > -1) && (tela[person.y][person.x-16-l].pedra == 0) && (tela[person.y][person.x-16-l].terra == 0) && (tela[person.y][person.x-16-l].moeda == 0) && (tela[person.y][person.x-16-l].muro == 0))
	/*se tiver rocha, verifica se pode movimentala mais para a esquerda*/
	{
		person.lado = 0;
    	if (!(frames % 4))
    	{
    		for(int a = person.y-8; a <= person.y+8; a++)
            {	
               	for(int b = person.x-8; b <= person.x+8; b++)
               	{
               		tela[a][b].pessoa = 0;
               	}
            }
            for(int a = rocks[aux].y-8; a <= rocks[aux].y+8; a++)
        	{
            	for(int b = rocks[aux].x-8; b <= rocks[aux].x+8; b++)
            	{
            	    tela[a][b].pedra = 0;
            	}
        	}
        
      		person.x = person.x - PERSON_SPEED;
      		rocks[aux].x -= PERSON_SPEED;
      			
      		for(int a = person.y-8; a <= person.y+8; a++)
       	    {
       	        for(int b = person.x-8; b <= person.x+8; b++)
       	        {
       	        	tela[a][b].pessoa = 1;
       	        }
       	    }
       		for(int a = rocks[aux].y-8; a <= rocks[aux].y+8; a++)
       		{	
       	    	for(int b = rocks[aux].x-8; b <= rocks[aux].x+8; b++)
       	    	{
       	    	    tela[a][b].pedra = 1;
       	    	}
    		}
    	}
    }
	else if((tela[person.y][person.x-11].muro == 0) && (tela[person.y][person.x-9].pedra == 0))
	/*caso nao tenha rocha, verifica se pode andar para a esquerda*/
   	{
   		int l = 0;
   		for(int i = 0; i <= 4; i++)
   		{
   			if ((tela[person.y+(2*i)][person.x-11].muro != 0) && (tela[person.y-(2*i)][person.x-11].muro != 0) && (tela[person.y+(2*i)][person.x-11].pedra != 0) && (tela[person.y-(2*i)][person.x-11].pedra != 0))
   			{
   				l = 1;
   				break;
   			}
   		}
   		if(l == 0)
    	{
    		person.lado = 0;
    		if (!(frames % 4))
    		{
    			for(int a = person.y-8; a <= person.y+8; a++)
            	{	
                	for(int b = person.x-8; b <= person.x+8; b++)
                	{
                		tela[a][b].pessoa = 0;
                	}
            	}
       			person.x = person.x - PERSON_SPEED;
       			for(int a = person.y-8; a <= person.y+8; a++)
            	{
                	for(int b = person.x-8; b <= person.x+8; b++)
                	{
                		tela[a][b].pessoa = 1;
                	}
            	}
            }
       	}
       	else
    	{
    		person.x = person.x;
    	}
    }
}

void move_direita()
/*funcao para movimentar o player para a direita*/
{
	int aux = -1;
	int l;
	for(int i = 0; i < ROCK_N; i++)
	/*buscando alguma rocha do lado direito*/
    {
    	for(l = 0; l < 23; l++)
    	{
    		for(int k = 0; k < 4; k++)
    		{
    			if((person.x+l == rocks[i].x) && ((person.y+k == rocks[i].y) || (person.y-k == rocks[i].y)))
    			{	
    				aux = i;
    				break;
    			}
    		}
    	}
	}
	if((aux > -1) && (tela[person.y][person.x+20+l].pedra == 0) && (tela[person.y][person.x+20+l].terra == 0) && (tela[person.y][person.x+20+l].moeda == 0) && (tela[person.y][person.x+20+l].muro == 0))
	/*se tiver rocha, verifica se pode movimentala mais para a direita*/
	{
		person.lado = 1;
    	if (!(frames % 4))
    	{
    		for(int a = person.y-8; a <= person.y+8; a++)
       	    {	
       	       	for(int b = person.x-8; b <= person.x+8; b++)
       	       	{
       	       		tela[a][b].pessoa = 0;
       	       	}
       	    }
       	    for(int a = rocks[aux].y-8; a <= rocks[aux].y+8; a++)
       		{
       	    	for(int b = rocks[aux].x-8; b <= rocks[aux].x+8; b++)
       	    	{
       	    	    tela[a][b].pedra = 0;
       	    	}
      		}
        		
      		person.x = person.x + PERSON_SPEED;
      		rocks[aux].x += PERSON_SPEED;
       		
       		for(int a = person.y-8; a <= person.y+8; a++)
            {
                for(int b = person.x-8; b <= person.x+8; b++)
                {
                	tela[a][b].pessoa = 1;
                }
            }
        	for(int a = rocks[aux].y-8; a <= rocks[aux].y+8; a++)
        	{	
        	   	for(int b = rocks[aux].x-8; b <= rocks[aux].x+8; b++)
        	    {
        	        tela[a][b].pedra = 1;
        	    }
    		}
    	}
	}
	else if((tela[person.y][person.x+4].muro == 0) && (tela[person.y][person.x+16].pedra == 0))
	/*caso nao tenha rocha, verifica se pode andar para a direita*/
    {
    	int l = 0;
    	for(int i = 0; i <= 4; i++)
    	{
    		if ((tela[person.y+(2*i)][person.x+4].muro != 0) && (tela[person.y-(2*i)][person.x+4].muro != 0) && (tela[person.y+(2*i)][person.x+16].pedra != 0) && (tela[person.y-(2*i)][person.x+16].pedra != 0))
    		{
    			l = 1;
    			break;
    		}
    	}
    	if(l == 0)
    	{
    		person.lado = 1;
    		if (!(frames % 4))
    		{
    			for(int a = person.y-8; a <= person.y+8; a++)
            	{	
                	for(int b = person.x-8; b <= person.x+8; b++)
                	{
                		tela[a][b].pessoa = 0;
                	}
            	}
       			person.x = person.x + PERSON_SPEED;
       			for(int a = person.y-8; a <= person.y+8; a++)
            	{
                	for(int b = person.x-8; b <= person.x+8; b++)
                	{
                		tela[a][b].pessoa = 1;
                	}
            	}
            }
       	}
       	else
    	{
    		person.x = person.x;
    	}
    }
}

void move_cima()
/*funcao para movimentar o player para cima*/
{
	int n = 0;
	if (person.lado == 0)
		n = 10;
	else
		n = 0;
	if((tela[person.y-9][person.x+n].muro == 0) && (tela[person.y-9][person.x].pedra == 0))
	/*verifica se pode andar para cima*/
	{
		int l = 0;
    	for(int i = 0; i <= 4; i++)
    	{
    		if ((tela[person.y-9][person.x-(2*i)].pedra != 0) && (tela[person.y-9][person.x+(2*i)].pedra != 0))
    		{
    			l = 1;
    			break;
    		}
    	}
    	if(l == 0)
   		{ 
    		if(!(frames % 4)) 
   			{
   				for(int a = person.y-8; a <= person.y+8; a++)
            	{	
                	for(int b = person.x-8; b <= person.x+8; b++)
                	{
                		tela[a][b].pessoa = 0;
                	}
            	}
       			person.y = person.y - PERSON_SPEED;
				for(int a = person.y-8; a <= person.y+8; a++)
            	{	
                	for(int b = person.x-8; b <= person.x+8; b++)
                	{
                		tela[a][b].pessoa = 1;
                	}
            	}
			}
   		}
    	else
    	{
    		person.y = person.y;
    	}
    }
}

void move_baixo()
/*funcao para movimentar o player para baixo*/
{
	int n = 0;
	if (person.lado == 0)
		n = 10;
	else
		n = 0;
	if((tela[person.y+9][person.x+n].muro == 0) && (tela[person.y+9][person.x].pedra == 0))
	/*verifica se pode andar para baixo*/
	{
		int l = 0;
    	for(int i = 0; i <= 4; i++)
    	{
    		if ((tela[person.y][person.x-(2*i)].pedra != 0) && (tela[person.y+9][person.x+(2*i)].pedra != 0))
    		{
    			l = 1;
    			break;
    		}
    	}
    	if(l == 0)
   		{
   			if(!(frames % 4)) 
   			{
   				for(int a = person.y-8; a <= person.y+8; a++)
            	{	
                	for(int b = person.x-8; b <= person.x+8; b++)
                	{
                		tela[a][b].pessoa = 0;
                	}
            	}
       			person.y = person.y + PERSON_SPEED;
				for(int a = person.y-8; a <= person.y+8; a++)
            	{	
                	for(int b = person.x-8; b <= person.x+8; b++)
                	{
                		tela[a][b].pessoa = 1;
                	}
            	}
			}
		}
		else
    	{
    		person.y = person.y;
    	}
    }
}

void person_update()
/*atualiza o player*/
{
    if(person.respawn_timer)
    /*se morreu*/
    {
    	person.x = 60;
    	person.y = 64;
        person.respawn_timer--;
        return;
    }

	for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
    	key[i] &= KEY_SEEN;
	
    if(person.x < 12)
        person.x = 12;
    if(person.y < 48)
        person.y = 48;

    if(person.x >= PERSON_MAX_X)
        person.x = PERSON_MAX_X;
    if(person.y > PERSON_MAX_Y)
        person.y = PERSON_MAX_Y;

    if(person.invincible_timer)
    {
    	person.x = 60;
    	person.y = 64;
        person.invincible_timer--;
	}
    else
    {
        if(rocks_collide(true, person.x, person.y, PERSON_W, PERSON_H))
        /*verifica se colidiu*/
        {
            int x = person.x + (PERSON_W / 2);
            int y = person.y + (PERSON_H / 2);
            fx_add(false, x, y);
            fx_add(false, x+4, y+2);
            fx_add(false, x-2, y-4);
            fx_add(false, x+1, y-5);
			person.vivo = false;
            person.respawn_timer = 10;
            person.invincible_timer = 180;
        }
        if (moedas_collide2(true, person.x, person.y, PERSON_W, PERSON_H))
    	{
            int x = person.x + (PERSON_W / 2);
            int y = person.y + (PERSON_H / 2);
            fx_add(false, x, y);
            fx_add(false, x+4, y+2);
            fx_add(false, x-2, y-4);
            fx_add(false, x+1, y-5);
			person.vivo = false;
            person.respawn_timer = 10;
            person.invincible_timer = 180;
        }
        if(moedas_collide(person.x, person.y, PERSON_W, PERSON_H))
        {
			score += 10;
			num_moeda++;	
        }
    }   
}

void person_draw()
/*desenha o player*/
{
    if(person.respawn_timer)
    {
        return;
    }
    if(((person.invincible_timer / 2) % 3) == 1)
    {
        return;
	}
	
	if(person.lado == 1)
    {
    	al_draw_bitmap(miner, person.x, person.y, ALLEGRO_FLIP_HORIZONTAL);
    }
    else
    {
    	al_draw_bitmap(miner, person.x, person.y, 0);
    }
}

void destroi_miner()
{
	al_destroy_bitmap(miner);
}
