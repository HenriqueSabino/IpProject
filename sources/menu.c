#include <allegro.h>
#include "../headers/menu.h"

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



