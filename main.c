/*programa feito por Anderson Aparecido do Carmo Frasão
GRR20204069 */

#include<allegro5/allegro5.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include<stdio.h>
#include<stdlib.h>
#include"fx.h"
#include"rock.h"
#include"person.h"
#include"coin.h"
#include"terra.h"
#include"geral.h"

#define KEY_SEEN     1
#define KEY_RELEASED 2

#define M_FPS 4.0

#define DISP_SCALE 2
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

typedef enum{
	BT_U,
	BT_D,
	BT_L,
	BT_R,
	BT_PLAY,
	BT_PAUSE,
	BT_FIM,
	BT_N
} STATES;

int posi_moedax[] = {128, 128, 128, 128, 128, 240, 240, 240, 240, 240, 352, 352, 352, 352, 352, 464, 464, 464, 464, 464, 576, 576, 576, 576, 576};
int posi_moeday[] = {80,  112, 176, 224, 272, 80,  112, 176, 224, 272, 80,  112, 176, 224, 272, 80,  112, 176, 224, 272, 80,  112, 176, 224, 272};

bool keys[4] = {false, false, false, false};

unsigned char key[ALLEGRO_KEY_MAX];

void keyboard_init()
{
    memset(key, 0, sizeof(key));
}

void keyboard_update(ALLEGRO_EVENT* event)
/*atualizando o teclado*/
{
    switch(event->type)
    {
        case ALLEGRO_EVENT_TIMER:
            for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event->keyboard.keycode] &= KEY_RELEASED;
            break;
    }
}

void disp_init()
/*iniciando o display*/
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    disp = al_create_display(DISP_W, DISP_H);
    must_init(disp, "display");

    buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    must_init(buffer, "bitmap buffer");
}

void disp_deinit()
/*destruindo o display*/
{
    al_destroy_bitmap(buffer);
    al_destroy_display(disp);
}

void disp_pre_draw()
/*atualizando o display*/
{
    al_set_target_bitmap(buffer);
}

void disp_post_draw()
/*atualizando o display*/
{
    al_set_target_backbuffer(disp);
    al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

    al_flip_display();
}

void inicia_variaveis()
{
	must_init(al_init(), "allegro");
	must_init(al_init_font_addon(),"font");
    must_init(al_init_ttf_addon(), "ttf");	
	must_init(al_install_keyboard(), "keyboard");

	timer = al_create_timer(1.0 / 60.0);
	miner_timer = al_create_timer(1.0 / M_FPS);
	must_init(timer, "timer");
	must_init(miner_timer, "miner timer");
	
	queue = al_create_event_queue();
	must_init(queue, "queue");
	
	disp_init();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	
	/*colocando imagens no jogo*/
	must_init(al_init_image_addon(), "image addon");
	
	muro_prin = al_load_bitmap("./resources/esmeralda.png");
	must_init(muro_prin, "muro_prin");
	
	muro_sec = al_load_bitmap("./resources/muro.jpg");
	must_init(muro_sec, "muro_sec");
	
	porta = al_load_bitmap("./resources/porta.png");
	must_init(porta, "porta");
	
	texture_menu = al_load_bitmap("./resources/logo.png");
	must_init(texture_menu, "logo");
	
	surpresa = al_load_bitmap("./resources/surpresa.jpeg");
	must_init(surpresa, "surpresa");
	
	/*alocando memoria para a matriz que representa a tela*/
	tela = (POSSI**) malloc(BUFFER_H * sizeof(POSSI*));
	if(tela == NULL)
	{
		perror ("Memoria insuficiente");
	}
	for(int i = 0; i < BUFFER_H; i++)
	{
		tela[i] = (POSSI*) malloc(BUFFER_W * sizeof(POSSI));
		if(tela[i] == NULL)
		{
			perror ("Memoria insuficiente");
		}
	}
	
	/*inicializando a matriz que representa a tela*/
	for(int i = 0; i < BUFFER_H; i++)
	{	
		for(int l = 0; l < BUFFER_W; l++)
		{
			tela[i][l].muro = 0;
			tela[i][l].terra = 0;
			tela[i][l].pedra = 0;
			tela[i][l].pessoa = 0;
			tela[i][l].moeda = 0;
			tela[i][l].porta = 0;
		}
	}
	
	time_left = 150;
	
	final = NULL;
	morte = NULL;
	pega_moeda = NULL;
	carregamento = NULL;	
	
	/*iniciando os objetos do jogo*/
	rocks_init();
	moedas_init();
	audio_init();
	sprites_init();
	terras_init();
	person_init();
	
	/*colocando fonte de texto no jogo*/
	score_text = al_load_font("./resources/zig.ttf", 20, 0);
	must_init(score_text, "zig score");
	pause_text = al_load_font("./resources/zig.ttf", 30, 0);
	must_init(pause_text, "zig pause");
	
	al_register_event_source(queue, al_get_timer_event_source(miner_timer));
}

void destroi()
/*destruindo as variaveis criadas*/
{
	al_destroy_bitmap(muro_prin);
	al_destroy_bitmap(muro_sec);
	
	al_destroy_font(score_text);
	al_destroy_font(pause_text);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	
	audio_deinit();
	
	al_uninstall_audio();
	al_is_audio_installed(); 
	al_init_acodec_addon();
	
	destroi_rock();
	destroi_miner();
	destroi_moeda();
	destroi_terra();
	al_destroy_bitmap(porta);
	al_destroy_bitmap(texture_menu);
	al_destroy_bitmap(surpresa);
	
	for(int i = 0; i < BUFFER_H; i++)
	{
		free(tela[i]);
	}
	free(tela);
}

void print_muro_p()
/*imprimindo o muro lateral e o marcando na matriz*/
{
	for(int i = 0; i < BUFFER_W; i++)
	{
		for (int k = 32; k < 48; k++)
			tela[k][i].muro = 1;
		for (int z = BUFFER_H-16; z < BUFFER_H; z++)
			tela[z][i].muro = 1;
	}
	for(int l = 32; l < BUFFER_H; l++)
	{
		for (int k = 0; k < 16; k++)
			tela[l][k].muro = 1;
		for (int z = BUFFER_W-32; z < BUFFER_W-16; z++)
			tela[l][z].muro = 1;
	}
	for(int i = 0; i < BUFFER_W; i+=16)
    {
    	al_draw_bitmap(muro_prin, i, 32, 0);
    	al_draw_bitmap(muro_prin, i, BUFFER_H-16, 0);
	}
	for(int l = 32; l < BUFFER_H; l+=16)
    {
		al_draw_bitmap(muro_prin, 0, l, 0);
		al_draw_bitmap(muro_prin, BUFFER_W-16, l, 0);
	}
}

void print_muro_s()
/*imprimindo o muro central e o marcando na matriz*/
{
	for(int i = 0; i < BUFFER_W-213; i++)
	{
		for (int k = 120; k <= 136; k++)
			tela[k][i].muro = 1;
	}
	for(int l = BUFFER_W-16; l > 214; l--)
	{
		for (int k = 248; k <= 264; k++)
			tela[k][l].muro = 1;
	}
	for(int i = 16; i < BUFFER_W-208; i+=16)
	{
		al_draw_bitmap(muro_sec, i, 128, 0);
	}
	for(int l = BUFFER_W-32; l > 208; l-=16)
	{
		al_draw_bitmap(muro_sec, l, 256, 0);
	}
	
	al_draw_bitmap(porta, BUFFER_W-64, BUFFER_H-48, 0);
	for(int l = BUFFER_H-56; l <= BUFFER_H-40; l++)
    {
    	for (int i = BUFFER_W-72; i <= BUFFER_W-56; i++)
    	{
    		tela[l][i].porta = 1;
    	}
    }
}

void reset()
/*funcao para resetar o jogo caso morra ou acabe o tempo ou acabe o jogo*/
{
	fx_add(true, person.x + (PERSON_W / 2), person.y + (PERSON_H / 2));
	for(int i = 0; i < TERRA_N; i++)
   	{
   		if((!terras[i].used) && (terras[i].ja_usou))
   		{
        	terras[i].used = true;
        	terras[i].ja_usou = false;
			for(int a = terras[i].y-8; a <= terras[i].y+8; a++)
       		{
        		for(int b = terras[i].x-8; b <= terras[i].x+8; b++)
        		{
        		 	tela[a][b].terra = 1;
       			}
    		}
    	}
	}
	terras_update(tela);
	for(int i = 0; i < COIN_N; i++)
   	{
   		for(int a = moedas[i].y-8; a <= moedas[i].y+8; a++)
        {
           	for(int b = moedas[i].x-8; b <= moedas[i].x+8; b++)
           	{
           	    tela[a][b].moeda = 0;
           	}
        }
       	moedas[i].used = true;
        moedas[i].ja_usou = false;
		moedas[i].x = posi_moedax[i];
		moedas[i].y = posi_moeday[i];
		for(int a = moedas[i].y-8; a <= moedas[i].y+8; a++)
        {
           	for(int b = moedas[i].x-8; b <= moedas[i].x+8; b++)
           	{
           	    tela[a][b].moeda = 1;
           	}
        }
	}
	FILE *coordenadas = fopen("./resources/coordenadas_pedras.txt", "r");
	if ( ! coordenadas )
  	{
		perror ("Erro ao abrir arquivo") ;
		exit (1) ;
	}
	for(int i = 0; i < ROCK_N; i++)
    {
		for(int a = rocks[i].y-8; a <= rocks[i].y+8; a++)
		{
		    for(int b = rocks[i].x-8; b <= rocks[i].x+8; b++)
		    {
		        tela[a][b].pedra = 0;
		    }
		}
		fscanf(coordenadas, "%d %d\n", &rocks[i].x, &rocks[i].y);
		rocks[i].used = true;
		for(int a = rocks[i].y-8; a <= rocks[i].y+8; a++)
		{
		    for(int b = rocks[i].x-8; b <= rocks[i].x+8; b++)
		    {
		        tela[a][b].pedra = 1;
		    }
		}
	}
	time_left = 150;
	num_moeda = 0;
	score = 0;
	person.vivo = true;
	for(int i = 0; i < 4; i++)
	{
		keys[i] = false;
	}
}

int main()
{	
	inicia_variaveis();
	FILE *rank = fopen("./resources/score_acumulado.txt", "r");
	if ( ! rank )
  	{
		perror ("Erro ao abrir arquivo") ;
		exit (1) ;
	}
	
	long vet_rank[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	for(int i = 0; i < 10; i++)
	{
		fscanf(rank,"%ld\n", &vet_rank[i]);
	}
	
	freopen ("./resources/score_acumulado.txt", "w+", rank);
	
	bool done = false;
	bool redraw = true;
	int estado = BT_PAUSE;
	
	al_start_timer(timer);
	al_start_timer(miner_timer);
	
	/*tela de inicio do jogo*/
	al_play_sample(carregamento, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    while(estado != BT_PLAY)
    {
        al_wait_for_event(queue,&event);
        al_draw_bitmap(texture_menu, (BUFFER_W/2)-50, (BUFFER_H/2)-100, 0);
        al_draw_textf(pause_text, al_map_rgb(147,81,178), BUFFER_W+25, BUFFER_H/2+400, ALLEGRO_ALIGN_CENTER, "PRESSIONE ESPAÇO PARA JOGAR.");
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(event.keyboard.keycode == ALLEGRO_KEY_SPACE) estado = BT_PLAY;
            if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) break;
        }
    }
	
	//logica do jogo
	while(1)
	{	
		al_wait_for_event(queue,&event);
		
		if(estado == BT_PLAY && event.timer.source == miner_timer)
		/*controle do jogo*/
        {
            if(keys[BT_U]) move_cima(tela);
            else if(keys[BT_D]) move_baixo(tela);
            else if(keys[BT_R]) move_direita(tela);
            else if(keys[BT_L]) move_esquerda(tela);
            redraw = true;
		}
		if(estado == BT_PLAY)
		/*atualizacao do jogo*/
		{
    		keyboard_update(&event);
    		fx_update();
    		person_update(tela);
    		moedas_update(tela, posi_moedax, posi_moeday);
    		rocks_update(tela);
    		terras_update(tela);
    		time_left -= 0.0166666667;
    	}
    	if((time_left <= 0) || (!person.vivo))
    	/*se morrer ou acabar o tempo*/
    	{
    		for(int i = 0; i < 10; i++)
    		{
    			if(vet_rank[i] < score)
    			{
    				vet_rank[9] = 0;
    				for(int l = 9; l > i; l--)
    				{
    					vet_rank[l] = vet_rank[l-1];
    				}
    				vet_rank[i] = score;
    				break;
    			}
    		}
    		if(time_left <= 0)
    		{
    			person.respawn_timer = 10;
    		}
    		reset();
    	}
    	
    	if(tela[person.y][person.x].porta == 1)  
    	/*se chegar ao final do jogo*/
    	{
    		for(int i = 0; i < 10; i++)
    		{
    			if(vet_rank[i] < score)
    			{
    				vet_rank[9] = 0;
    				for(int l = 9; l > i; l--)
    				{
    					vet_rank[l] = vet_rank[l-1];
    				}
    				vet_rank[i] = score;
    				break;
    			}
    		}
    		estado = BT_FIM;
    		al_play_sample(final, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }
        while(estado == BT_FIM)
        /*tela do fim do jogo*/
        {
        	al_wait_for_event(queue,&event);
        	al_draw_textf(pause_text, al_map_rgb(255,223,0), BUFFER_W/2+350, BUFFER_H/2-150, ALLEGRO_ALIGN_CENTER, "PARABENS, VOCE CHEGOU AO FIM DO JOGO.");	
        	for(int i = 0; i < 5; i++)
        	{
        		al_draw_textf(pause_text, al_map_rgb(255,223,0), BUFFER_W, BUFFER_H/2-(150-(i*50))+100, ALLEGRO_ALIGN_CENTER, "%d: %.6ld", i+1, vet_rank[i]);
    		}
    		for(int i = 5; i < 10; i++)
        	{
        		al_draw_textf(pause_text, al_map_rgb(255,223,0), BUFFER_W, BUFFER_H/2-(150-(i*50))+100, ALLEGRO_ALIGN_CENTER, "%d: %.6ld", i+1, vet_rank[i]);
    		}
    		al_draw_textf(pause_text, al_map_rgb(255,223,0), BUFFER_W/2+300, BUFFER_H/2+475, ALLEGRO_ALIGN_CENTER, "PRESSIONE ESPAÇO PARA REINICIAR.");
    		al_flip_display();
    		al_clear_to_color(al_map_rgb(0,0,0));	
    		if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        	{
           		if(event.keyboard.keycode == ALLEGRO_KEY_SPACE) 
           		/*reiniciar o jogo*/
            	{
            		person.respawn_timer = 10;
            		reset();
            		estado = BT_PLAY;
            	}		
            	if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            	{
            		for(int i = 0; i < 10; i++)
					{
						fprintf(rank,"%ld\n", vet_rank[i]);
					}
            		break;
            	}
        		/*sair*/
        	}
        }
    		
    	if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    	{
    		done = true;
    	}
    	else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:     keys[BT_U] = true; 	break;
                case ALLEGRO_KEY_DOWN:   keys[BT_D]= true;		break;
                case ALLEGRO_KEY_RIGHT:  keys[BT_R]= true; 		break;
                case ALLEGRO_KEY_LEFT:   keys[BT_L]= true;		break;
                case ALLEGRO_KEY_F1: 	 estado = BT_PAUSE; 	break;
                case ALLEGRO_KEY_SPACE:  estado = BT_PLAY;  	break;
            }

        }
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
        	for(int i = 0; i < 10; i++)
			{
				fprintf(rank,"%ld\n", vet_rank[i]);
			}
            break;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:    keys[BT_U] = false;    	break;
                case ALLEGRO_KEY_DOWN:  keys[BT_D]= false;   	break;
                case ALLEGRO_KEY_RIGHT: keys[BT_R]= false;  	break;
                case ALLEGRO_KEY_LEFT: 	keys[BT_L]= false;    	break;
            }
		}
		if(estado == BT_PAUSE)
		/*tela de pause*/
        {
            al_draw_textf(pause_text, al_map_rgb(255,223,0), BUFFER_W/2+350, BUFFER_H/2-150, ALLEGRO_ALIGN_CENTER, "JOGO PAUSADO.");
            al_draw_textf(pause_text, al_map_rgb(255,223,0), BUFFER_W/2-150, BUFFER_H/2-50, ALLEGRO_ALIGN_CENTER, "INSTRUÇÕES:");
            al_draw_textf(pause_text, al_map_rgb(255,223,0), BUFFER_W/2+300, BUFFER_H/2, ALLEGRO_ALIGN_CENTER, "UTILIZE AS SETAS PARA MOVIMENTAR O");
            al_draw_textf(pause_text, al_map_rgb(255,223,0), BUFFER_W/2+10, BUFFER_H/2+50, ALLEGRO_ALIGN_CENTER, "PERSONAGEM");
            al_draw_textf(pause_text, al_map_rgb(255,223,0), BUFFER_W/2+230, BUFFER_H/2+100, ALLEGRO_ALIGN_CENTER, "FEITO POR ANDERSON APARECIDO");
            al_draw_textf(pause_text, al_map_rgb(255,223,0), BUFFER_W/2+70, BUFFER_H/2+150, ALLEGRO_ALIGN_CENTER, "DO CARMO FRASAO");
            al_draw_textf(pause_text, al_map_rgb(255,223,0), BUFFER_W/2+260, BUFFER_H/2+250, ALLEGRO_ALIGN_CENTER, "CHEGUE A PARTE INFERIO DIREITA ");
            al_draw_textf(pause_text, al_map_rgb(255,223,0), BUFFER_W/2+245, BUFFER_H/2+300, ALLEGRO_ALIGN_CENTER, "(PORTA) PARA FINALIZAR O JOGO!");
            
            al_draw_textf(pause_text, al_map_rgb(255,223,0), BUFFER_W-50, BUFFER_H/2+450, ALLEGRO_ALIGN_CENTER, "PRESSIONE ESPAÇO PARA VOLTAR.");
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }

        if(done)
            break;
    	
		if(estado == BT_PLAY && redraw && al_is_event_queue_empty(queue))
		{
			disp_pre_draw();
    		al_clear_to_color(al_map_rgb(0, 0, 0));
    		
    		for(int i = 0; i < BT_N; i++)
            {
                
               	if(estado == BT_PLAY)
               	/*desenhando o jogo*/
               	{
               		al_draw_bitmap(surpresa, 8, BUFFER_H-200, 0);
               		verifica_terra();
                	terras_draw();
                	print_muro_p();
        			print_muro_s();
        			verifica_pedra();
                	rocks_draw();
                	verifica_moeda();
                	moedas_draw();
                	person_draw();
                	fx_draw();
                	al_draw_textf(score_text, al_map_rgb(255,223,0), BUFFER_W-78, 4, ALLEGRO_ALIGN_RIGHT, "SCORE: %.6ld", score);
                	al_draw_textf(score_text, al_map_rgb(255,223,0), BUFFER_W/2, 4, ALLEGRO_ALIGN_RIGHT, "TIME: %.0f", time_left);
                	al_draw_textf(score_text, al_map_rgb(255,223,0), 128, 4, ALLEGRO_ALIGN_RIGHT, "%d-%d", num_moeda, COIN_N);
				}
			}
			
			disp_post_draw();		
    		redraw = false;
		}	
	}
	
	destroi();
	
	for(int i = 0; i < 10; i++)
	{
		fprintf(rank,"%ld\n", vet_rank[i]);
	}
	fclose(rank);

	return 0;
}
