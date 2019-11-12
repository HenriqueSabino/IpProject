#include <allegro.h>
#include "../headers/menu.h"

int menu(int timer)
{
    //Variáveis
	int  chx  =  315, chy = 347 , time = 0, som = 0;
	int  px = 315, py[2]= {347, 400};

	//bitmaps
	BITMAP *menu  = load_bitmap(LOGO_PATH , NULL);
	BITMAP *chave = load_bitmap(ARROW_PATH , NULL);
	BITMAP *buff  = create_bitmap(  64 * 16, 64 * 9 );

	//SONS
	SAMPLE *select = load_sample(SELECT_SOUND);
	SAMPLE *intro  = load_sample(INTRO_SOUND);
	SAMPLE *buble  = load_sample(ENTER_SOUND);

	//funções
	//install_int_ex(tempo, MSEC_TO_TIMER(150));

	//Introdução
	play_sample(intro, 255, 128, 1000, 1);

	while(!key[KEY_ESC])
	{
		//entradas
		if(key[KEY_RIGHT])
		{
            som = 1;
        }

		if(key[KEY_DOWN ])
		{
        	if(chy == py[0])
			{
                chy = py[1];
                som = 1;
            }
        }

		if(key[KEY_LEFT ])
		{
            som = 1;
        }

		if(key[KEY_UP   ])
		{
        	if(chy == py[1])
			{
                chy = py[0];
                som = 1;
            }
        }

		if(key[KEY_ENTER])
		{
            if(chy == py[0])
			{
                stop_sample(intro);
                play_sample(buble, 255, 128, 1000, 0);
			}
			else
			{
                // executar função de saida
                return 0;
            }
		}

		if(timer % 2 != 0)
        {
			draw_sprite(buff, chave, chx, chy);
		}

		//RELOGIO
		//delay = timer;

		if(som == 1 )
		{
            play_sample(select, 255, 128, 1000, 0);
            som = 0;
        }

		draw_sprite(screen, buff, 0, 0);
		clear(buff);
		draw_sprite(buff,  menu, 0, 0);
	}
	destroy_bitmap(buff  );
	destroy_bitmap(menu  );
	destroy_bitmap(chave );
	destroy_sample(select);
	destroy_sample(intro );
}

void deathscreen()
{
	int som = 0;
	
	BITMAP *deathscreen  = load_bitmap(DEATHSCREEN_PATH , NULL);
	BITMAP *buff  = create_bitmap( 64 * 16, 64 * 9 );

	//SONS
	SAMPLE *select = load_sample(SELECT_SOUND);
	SAMPLE *ending  = load_sample(DEATH_SOUND);

	//funções

	//Introdução
	play_sample(ending, 255, 128, 1000, 1);

	while(!key[KEY_ESC])
	{
		//entradas
		if(key[KEY_ENTER])
		{       
            stop_sample(ending);
            som = 1;
		}

		if(som == 1 )
		{
            play_sample(select, 255, 128, 1000, 0);
            som = 0;
		}

		draw_sprite(screen, buff, 0, 0);
		clear(buff);
		draw_sprite(buff,  deathscreen, 0, 0);
	}
	destroy_bitmap(buff  );
	destroy_bitmap(deathscreen  );
	destroy_sample(select);
	destroy_sample(ending );
}



