/*
 * SideShooter1.c
 *
 *  Created on: 13/08/2012
 *      Author: eryckson
 */

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>

#include "objects.h"

//GLOBALS==============================
const int WIDTH = 800;
const int HEIGHT = 400;
const int NUM_BULLETS = 5;
const int NUM_COMETS = 15;

enum KEYS
{
	UP, DOWN, LEFT, RIGHT, SPACE
};

bool keys[5] =
{ false, false, false, false, false };

//prototypes
struct SpaceShip InitShip(ALLEGRO_BITMAP *shipImage);
void DrawShip(struct SpaceShip ship);
struct SpaceShip MoveShipLeft(struct SpaceShip ship);
struct SpaceShip MoveShipUp(struct SpaceShip ship);
struct SpaceShip MoveShipDown(struct SpaceShip ship);
struct SpaceShip MoveShipRight(struct SpaceShip ship);

void DrawBullet(struct Bullet bullet[], int size);
void DrawComet(struct Comet comets[], int size);

struct SpaceShip ResetShipAnimation(struct SpaceShip ship, int position);

/* drop build configuration directory tail */
static ALLEGRO_PATH *get_resources_path(void)
{
	ALLEGRO_PATH *path;
	const char *last;

	path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	if (!path)
		return al_create_path("");

	/* If the last directory component is the name of an MSVC build
	 * configuration, then drop it.
	 */
	last = al_get_path_tail(path);
	if (last
			&& (0 == strcmp(last, "Debug") || 0 == strcmp(last, "Release")
					|| 0 == strcmp(last, "RelWithDebInfo")
					|| 0 == strcmp(last, "Profile")))
	{
		al_drop_path_tail(path);
	}

	return path;
}

int main(void)
{
	//primitive variable
	const int FPS = 60;
	bool done = false;
	bool redraw = true;
	bool isGameOver = false;

	//object variables
	struct SpaceShip ship;
	struct Bullet bullets[NUM_BULLETS];
	struct Comet comets[NUM_COMETS];

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *shipImage;
	ALLEGRO_BITMAP *cometImage;
	ALLEGRO_BITMAP *bulletImage;

	ALLEGRO_FONT *font = NULL;
	ALLEGRO_PATH *font_path;

	//Initialization Functions
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);		//create our display object

	if (!display)										//test display object
		return -1;

	// inicio inicializacao fontes
	al_init_image_addon();

	font_path = get_resources_path();
	al_set_path_filename(font_path, "a4_font.tga");

	al_init_font_addon();
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	font = al_load_bitmap_font(al_path_cstr(font_path, '/'));
	if (!font)
	{
		return 1;
	}

	al_destroy_path(font_path);
	// termino inicializacao fontes

	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	shipImage = al_load_bitmap("spaceship_by_arboris.png");
	al_convert_mask_to_alpha(shipImage, al_map_rgb(255, 0, 255));

	bulletImage = al_load_bitmap("bullets_by_arboris.png");
	al_convert_mask_to_alpha(bulletImage, al_map_rgb(255, 0, 255));

	cometImage = al_load_bitmap("asteroid-1-96.png");

	srand(time(NULL ));

	//Game Init
	ship = InitShip(shipImage);

	// init bullets
	int i = 0;
	while (i < NUM_BULLETS)
	{
		bullets[i].ID = BULLET;
		bullets[i].speed = 10;
		bullets[i].live = false;

		bullets[i].maxFrame = 143;
		bullets[i].curFrame = 0;
		bullets[i].frameCount = 0;
		bullets[i].frameDelay = 2;
		bullets[i].frameWidth = 20;
		bullets[i].frameHeight = 10;
		bullets[i].animationColumns = 1;

		bullets[i].animationRow = 1;

		bullets[i].image = bulletImage;

		i++;
	}

	// init comets
	i = 0;
	while (i < NUM_COMETS)
	{
		comets[i].ID = ENEMY;
		comets[i].live = false;
		comets[i].speed = 5;
		comets[i].boundx = 35;
		comets[i].boundy = 35;

		comets[i].maxFrame = 143;
		comets[i].curFrame = 0;
		comets[i].frameCount = 0;
		comets[i].frameDelay = 2;
		comets[i].frameWidth = 96;
		comets[i].frameHeight = 96;
		comets[i].animationColumns = 21;

		if (rand() % 2)
			comets[i].animationDirection = 1;
		else
			comets[i].animationDirection = -1;

		comets[i].image = cometImage;

		i++;
	}

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			if (keys[UP])
				ship = MoveShipUp(ship);
			else if (keys[DOWN])
				ship = MoveShipDown(ship);
			else
				ship = ResetShipAnimation(ship, 1);

			if (keys[LEFT])
				ship = MoveShipLeft(ship);
			else if (keys[RIGHT])
				ship = MoveShipRight(ship);
			else
				ship = ResetShipAnimation(ship, 2);

			if (!isGameOver)
			{
				//UpdateBullet
				int i = 0;
				while (i < NUM_BULLETS)
				{
					if (bullets[i].live)
					{
						bullets[i].x += bullets[i].speed;
						if (bullets[i].x > WIDTH)
							bullets[i].live = false;
					}

					i++;
				}

				// start comet
				i = 0;
				while (i < NUM_COMETS)
				{
					if (!comets[i].live)
					{
						if (rand() % 500 == 0)
						{
							comets[i].live = true;
							comets[i].x = WIDTH;
							comets[i].y = 30 + rand() % (HEIGHT - 60);

							break;
						}
					}

					i++;
				}

				// UpdateComet(Comet comets[], int size)
				i = 0;
				while (i < NUM_COMETS)
				{
					if (comets[i].live)
					{
						if (++comets[i].frameCount >= comets[i].frameDelay)
						{
							comets[i].curFrame += comets[i].animationDirection;
							if (comets[i].curFrame >= comets[i].maxFrame)
								comets[i].curFrame = 0;
							else if (comets[i].curFrame <= 0)
								comets[i].curFrame = comets[i].maxFrame - 1;

							comets[i].frameCount = 0;
						}

						comets[i].x -= comets[i].speed;
					}

					i++;
				}

				// collide bullet
				i = 0;
				while (i < NUM_BULLETS)
				{
					if (bullets[i].live)
					{
						int j = 0;
						while (j < NUM_COMETS)
						{
							if (comets[j].live)
							{
								if (bullets[i].x
										> (comets[j].x - comets[j].boundx)
										&& bullets[i].x
												< (comets[j].x
														+ comets[j].boundx)
										&& bullets[i].y
												> (comets[j].y
														- comets[j].boundy)
										&& bullets[i].y
												< (comets[j].y
														+ comets[j].boundy))
								{
									bullets[i].live = false;
									comets[j].live = false;

									ship.score++;
								}
							}

							j++;
						}
					}

					i++;
				}

				// collide comet
				i = 0;
				while (i < NUM_COMETS)
				{
					if (comets[i].live)
					{
						if (comets[i].x - comets[i].boundx
								< ship.x + ship.boundx
								&& comets[i].x + comets[i].boundx
										> ship.x - ship.boundx
								&& comets[i].y - comets[i].boundy
										< ship.y + ship.boundy
								&& comets[i].y + comets[i].boundy
										> ship.y - ship.boundy)
						{
							ship.lives--;
							comets[i].live = false;
						}
						else if (comets[i].x < 0)
						{
							comets[i].live = false;
							ship.lives--;
						}
					}

					i++;
				}

				if (ship.lives <= 0)
					isGameOver = true;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;

				//FireBullet
				int i = 0;
				while (i < NUM_BULLETS)
				{
					if (!bullets[i].live)
					{
						bullets[i].x = ship.x + 17;
						bullets[i].y = ship.y;
						bullets[i].live = true;
						break;
					}

					i++;
				}

				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			if (!isGameOver)
			{
				DrawShip(ship);
				DrawBullet(bullets, NUM_BULLETS);
				DrawComet(comets, NUM_COMETS);
				al_draw_textf(font, al_map_rgb(255, 0, 255), 5, 5, 0,
						"Player has %i lives left. Player has destroyed %i objects",
						ship.lives, ship.score);
			}
			else
			{
				al_draw_textf(font, al_map_rgb(0, 255, 255), WIDTH / 2,
						HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
						"Game Over. Final Score: %i", ship.score);
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	al_destroy_bitmap(bulletImage);
	al_destroy_bitmap(cometImage);
	al_destroy_bitmap(shipImage);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font);
	al_destroy_display(display);					//destroy our display object

	return 0;
}

struct SpaceShip InitShip(ALLEGRO_BITMAP *image)
{
	struct SpaceShip ship;

	ship.x = 20;
	ship.y = HEIGHT / 2;
	ship.ID = PLAYER;
	ship.lives = 3;
	ship.speed = 7;
	ship.boundx = 6;
	ship.boundy = 7;
	ship.score = 0;

	ship.maxFrame = 3;
	ship.curFrame = 0;
	ship.frameCount = 0;
	ship.frameDelay = 50;
	ship.frameWidth = 46;
	ship.frameHeight = 41;
	ship.animationColumns = 3;
	ship.animationDirection = 1;

	ship.animationRow = 1;

	ship.image = image;

	return ship;
}

struct SpaceShip ResetShipAnimation(struct SpaceShip ship, int position)
{
	if (position == 1)
		ship.animationRow = 1;
	else
		ship.curFrame = 0;

	return ship;
}

void DrawShip(struct SpaceShip ship)
{
	int fx = (ship.curFrame % ship.animationColumns) * ship.frameWidth;
	int fy = ship.animationRow * ship.frameHeight;

	al_draw_bitmap_region(ship.image, fx, fy, ship.frameWidth, ship.frameHeight,
			ship.x - ship.frameWidth / 2, ship.y - ship.frameHeight / 2, 0);

//	al_draw_filled_rectangle(ship.x, ship.y - 9, ship.x + 10, ship.y - 7,
//			al_map_rgb(255, 0, 0));
//	al_draw_filled_rectangle(ship.x, ship.y + 9, ship.x + 10, ship.y + 7,
//			al_map_rgb(255, 0, 0));
//
//	al_draw_filled_triangle(ship.x - 12, ship.y - 17, ship.x + 12, ship.y,
//			ship.x - 12, ship.y + 17, al_map_rgb(0, 255, 0));
//	al_draw_filled_rectangle(ship.x - 12, ship.y - 2, ship.x + 15, ship.y + 2,
//			al_map_rgb(0, 0, 255));
}

struct SpaceShip MoveShipLeft(struct SpaceShip ship)
{
	ship.curFrame = 2;

	ship.x -= ship.speed;
	if (ship.x < 0)
		ship.x = 0;

	return ship;
}

struct SpaceShip MoveShipUp(struct SpaceShip ship)
{
	ship.animationRow = 0;

	ship.y -= ship.speed;
	if (ship.y < 0)
		ship.y = 0;

	return ship;
}

struct SpaceShip MoveShipDown(struct SpaceShip ship)
{
	ship.animationRow = 2;

	ship.y += ship.speed;
	if (ship.y > HEIGHT)
		ship.y = HEIGHT;

	return ship;
}

struct SpaceShip MoveShipRight(struct SpaceShip ship)
{
	ship.curFrame = 1;

	ship.x += ship.speed;
	if (ship.x > 300)
		ship.x = 300;

	return ship;
}

void DrawBullet(struct Bullet bullet[], int size)
{
	int i = 0;
	while (i < size)
	{
		if (bullet[i].live)
		{
			int fx = (bullet[i].curFrame % bullet[i].animationColumns)
					* bullet[i].frameWidth;
			int fy = (bullet[i].curFrame % bullet[i].animationColumns)
					* bullet[i].frameHeight * bullet[i].animationRow;

			al_draw_bitmap_region(bullet[i].image, fx, fy, bullet[i].frameWidth,
					bullet[i].frameHeight,
					bullet[i].x - bullet[i].frameWidth / 2,
					bullet[i].y - bullet[i].frameHeight / 2, 0);

			/*al_draw_filled_circle(bullet[i].x, bullet[i].y, 2,
			 al_map_rgb(255, 255, 255));*/
		}

		i++;
	}
}

void DrawComet(struct Comet comets[], int size)
{
	int i = 0;
	while (i < size)
	{
		if (comets[i].live)
		{
			int fx = (comets[i].curFrame % comets[i].animationColumns)
					* comets[i].frameWidth;
			int fy = (comets[i].curFrame / comets[i].animationColumns)
					* comets[i].frameHeight;

			al_draw_bitmap_region(comets[i].image, fx, fy, comets[i].frameWidth,
					comets[i].frameHeight,
					comets[i].x - comets[i].frameWidth / 2,
					comets[i].y - comets[i].frameHeight / 2, 0);

			/*al_draw_filled_rectangle(comets[i].x - comets[i].boundx,
			 comets[i].y - comets[i].boundy,
			 comets[i].x + comets[i].boundx,
			 comets[i].y + comets[i].boundy,
			 al_map_rgba(255, 0, 255, 100));*/
		}

		i++;
	}
}
