/*
 * learn01.c
 *
 *  Created on: 12/08/2012
 *      Author: eryckson
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>

struct line_coord
{
	float x1;
	float y1;
	float x2;
	float y2;
};

ALLEGRO_COLOR black;
ALLEGRO_COLOR white;
ALLEGRO_COLOR background;

struct line_coord linha1;
struct line_coord linha2;

static void desenharLinhas(void)
{
	al_draw_line(linha1.x1, linha1.y1, linha1.x2, linha1.y2, black, 0);
	al_draw_line(linha2.x1, linha2.y1, linha2.x2, linha2.y2, black, 0);
}

static void flip(float x1, float y1, float x2, float y2, float xc, float yc)
{
	al_clear_to_color(background);
	al_draw_rectangle(x1, y1, x2, y2, black, 0);

	desenharLinhas();

	al_draw_filled_circle(xc, yc, 8.0, white);
	al_flip_display();
}

static BOOL passaNaLinha(float xc, float yc)
{
	BOOL passaNa1 = FALSE;
	BOOL passaNa2 = FALSE;

	if (xc < linha1.x2 || yc < linha1.y1 || yc > linha1.y2)
	{
		passaNa1 = TRUE;
	}
	else if (xc > linha1.x2)
	{
		passaNa1 = TRUE;
	}

	if (xc < linha2.x2 || yc < linha2.y1 || yc > linha2.y2)
	{
		passaNa2 = TRUE;
	}
	else if (xc > linha2.x2)
	{
		passaNa2 = TRUE;
	}

	return (passaNa1 && passaNa2);
}

int main_2(int argc, char* argv[])
{
	ALLEGRO_DISPLAY* janela = NULL;

	ALLEGRO_BITMAP *dbuf;
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_EVENT event;

	float largura = 640;
	float altura = 480;

	float x1 = 100.5;
	float y1 = 100.5;
	float x2 = largura - 100.5;
	float y2 = altura - 100.5;

	float xc = x1 + 10;
	float yc = y1 + 10;

	linha1.x1 = x1 + 30;
	linha1.y1 = y1;
	linha1.x2 = linha1.x1;
	linha1.y2 = y2 - 200;

	linha2.x1 = x1 + 60;
	linha2.y1 = y1 + 30;
	linha2.x2 = linha2.x1;
	linha2.y2 = y2 - 100;

	if (!al_init())
	{
		fprintf(stderr, "Falha ao iniciar Allegro \n");
		return -1;
	}

	al_init_primitives_addon();
	al_install_keyboard();

	janela = al_create_display(largura, altura);
	if (!janela)
	{
		fprintf(stderr, "Falha ao criar a janela \n");
		return -1;
	}

		// definindo cores
	black = al_map_rgb_f(0.0, 0.0, 0.0);
	white = al_map_rgb_f(1.0, 1.0, 1.0);
	background = al_map_rgb_f(0.5, 0.5, 0.6);

	dbuf = al_create_bitmap(largura, altura);
	if (!dbuf)
	{
		fprintf(stderr, "Error creating double buffer\n");
		return 1;
	}

	al_set_target_bitmap(dbuf);
	al_set_target_backbuffer(janela);
	al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);
	al_draw_bitmap(dbuf, 0.0, 0.0, 0);

	flip(x1, y1, x2, y2, xc, yc);

	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());

	while (true)
	{
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				break;
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			{
				xc += 10;

				if (xc < x2 && passaNaLinha(xc, yc))
				{
					flip(x1, y1, x2, y2, xc, yc);
				}
				else
				{
					xc -= 10;
				}
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
			{
				xc -= 10;

				if (xc > x1 && passaNaLinha(xc, yc))
				{
					flip(x1, y1, x2, y2, xc, yc);
				}
				else
				{
					xc += 10;
				}
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_UP)
			{
				yc -= 10;

				if (yc > y1 && passaNaLinha(xc, yc))
				{
					flip(x1, y1, x2, y2, xc, yc);
				}
				else
				{
					yc += 10;
				}
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
			{
				yc += 10;

				if (yc < y2 && passaNaLinha(xc, yc))
				{
					flip(x1, y1, x2, y2, xc, yc);
				}
				else
				{
					yc -= 10;
				}
			}
		}
	}

	al_destroy_event_queue(queue);
	al_destroy_bitmap(dbuf);
	al_destroy_display(janela);

	return 0;
}
