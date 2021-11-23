#makefile para o jogo grafico, para a materia programação 2 (CI-1002)
#feito por Anderson Aparecido do Carmo Frasão
#GRR 20204069

CFLAGS = -Wall -g -std=gnu99 

PACKAGEFLAGS = pkg-config
ALLEGRO5FLAGS = allegro-5 allegro_font-5 allegro_ttf-5  allegro_image-5  allegro_audio-5 allegro_acodec-5 --libs --cflags

objs = main.o person.o terra.o rock.o coin.o fx.o

all: game

game: $(objs)
		gcc $(objs) -o game $$($(PACKAGEFLAGS) $(ALLEGRO5FLAGS)) 
	
main.o:	main.c 
	cc -c main.c $(CFLAGS)
person.o: person.c 
	cc -c person.c $(CFLAGS)
terra.o: terra.c
	cc -c terra.c $(CFLAGS) 
rock.o: rock.c 
	cc -c rock.c $(CFLAGS)
fx.o: fx.c
	cc -c fx.c $(CFLAGS)
coin.o: coin.c
	cc -c coin.c $(CFLAGS) 
			
clean:
	-rm -f *.o *~ 
	
purge: clean
	-rm -f game
