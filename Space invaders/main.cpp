#include "Libraries.h"

#define FPS 120

void easter_egg(ALLEGRO_DISPLAY* display)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(al_load_bitmap("easter.png"), (1920/2)-250, (1080/2)-200, 0);
	al_flip_display();
	al_rest(5);
}

double transformation(double& res_y)
{
	//ALLEGRO_TRANSFORM scaling;
	//ALLEGRO_MONITOR_INFO info;
	//ALLEGRO_DISPLAY_MODE info;
	al_get_display_mode(0 , &info);
	/*int res_monitor_x; 
	double res_monitor_y;
	al_get_monitor_info(0, &info);
	res_monitor_x = info.x2 - info.x1;
	res_monitor_y = info.y2 - info.y1;
	res_x = res_monitor_x / (double)LARGHEZZA;
	res_y = res_monitor_y / (double)ALTEZZA;*/

	res_y = info.height;

	return info.width;
}


int main(int argc, char **argv)
{
	double ALTEZZA = 1080;
	double LARGHEZZA = transformation(ALTEZZA);
	
	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERRORE", "ERRORE", "NON INIZIALIZZATO", "OK", ALLEGRO_MESSAGEBOX_ERROR);
	}
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();

	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	ALLEGRO_DISPLAY* display = al_create_display(LARGHEZZA, ALTEZZA);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_KEYBOARD_STATE keyState; //o creo un puntatore o passo alle funzioni l'indirizzo di memoria con &
	al_register_event_source(queue, al_get_keyboard_event_source()); 
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));
	//al_register_event_source(queue, al_get_display_event_source(display)); //per chiudere la finestra premendo X
	al_start_timer(timer);

	ALLEGRO_BITMAP* esc = al_load_bitmap("ESC.PNG");
	ALLEGRO_BITMAP* sfondo = al_load_bitmap("sfondo.png");

	Player giocatore(3,2,5.0); 

	const unsigned righe = 5;
	const unsigned colonne = 9;
	Nemico* nemico[righe][colonne];

	//crea i nemici
	for (unsigned i = 0; i < righe; i++)
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			if (i == 0) nemico[i][j] = new Nemico3;
			else if(i == 1) nemico[i][j] = new Nemico2;
			else if (i > 1) nemico[i][j] = new Nemico1;
		}
	}

	for (unsigned i = 0; i < righe; i++)
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			cout << " " << nemico[i][j]->getTipo() << " ";
		}
		cout << endl;
	}

	//inizializza le coordinate dei nemici
	for (unsigned j = 1; j < colonne; j++)
	{
			nemico[0][j]->x = nemico[0][j - 1]->x + al_get_bitmap_width(nemico[0][j]->getEnemyImage()) + 70 ;
	}

	for (unsigned i = 1; i < righe; i++)
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			if (j == 0)
			{
				nemico[i][j]->y = nemico[i - 1][j]->y + al_get_bitmap_width(nemico[i][j]->getEnemyImage()) ;
			}
			else
			{
				nemico[i][j]->x = nemico[i][j - 1]->x + al_get_bitmap_width(nemico[i][j]->getEnemyImage()) +70;
				nemico[i][j]->y = nemico[i - 1][j]->y + al_get_bitmap_width(nemico[i][j]->getEnemyImage());
			}
		}
	}
	cout << endl << endl;
	
	//al_hide_mouse_cursor(display); //è tutto una truffa!
	//ALLEGRO_MIXER* mixer = al_create_mixer()
	/*ALLEGRO_SAMPLE* song = al_load_sample("11 Exist.ogg");
	al_reserve_samples(1);
	ALLEGRO_SAMPLE_INSTANCE* canzone = al_create_sample_instance(song);
	al_set_sample_instance_playmode(canzone, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(canzone, al_get_default_mixer());
	al_play_sample_instance(canzone);*/

	bool easter[3] = { false };
	bool close = false;
	bool motion = true;
	bool shoot = false;

	unsigned l = 0; //serve per cambiare riga quando viene distrutto un nemico
	bool leggi = false;
	Weapon* arma = nullptr;

	while (!close) 
	{
		DIRECTION direction = OTHER;
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);
		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) close = true; //chiude la finestra premendo X

		if (easter[0] && easter[1] && easter[2])
		{
			close = true;
			easter_egg(display);
		}

		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			cout << "x " << evento.mouse.x;
			cout << " y " << evento.mouse.y << endl;
		}
		/*if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if ((evento.mouse.button & 1)) close = true; //1 rappresenta il tasto sinistro del mouse
		}*/

		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(sfondo, 0, 0, 0);

		if (evento.type == ALLEGRO_EVENT_TIMER)
		{
			al_get_keyboard_state(&keyState);
			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) close = true;
			//if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) giocatore.y += giocatore.getPlayerSpeed();
			//if (al_key_down(&keyState, ALLEGRO_KEY_UP)) giocatore.y -= giocatore.getPlayerSpeed();
			if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) { giocatore.x -= giocatore.getPlayerSpeed(); direction = LEFT; }
			if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) { giocatore.x += giocatore.getPlayerSpeed(); direction = RIGHT; }
			
			if (al_key_down(&keyState, ALLEGRO_KEY_SPACE) && !shoot) 
			{ 
				shoot = true;
				arma = new Weapon;
				arma->x = giocatore.x + 72;
				arma->y = giocatore.getY();
			}
			if (shoot)
			{
				arma->y -= arma->getSpeed();
				al_draw_bitmap(arma->getWeaponImage(), arma->x, arma->y, 1);
				//cout <<"Y "<< arma->y << endl;
				if (arma->y <= 0  && arma != nullptr)
				{
					shoot = false;
					delete arma;
					arma = nullptr;
				}
			}
			if (al_key_down(&keyState, ALLEGRO_KEY_C)) easter[0] = true;
			if (al_key_down(&keyState, ALLEGRO_KEY_A)) easter[1] = true;
			if (al_key_down(&keyState, ALLEGRO_KEY_O)) easter[2] = true;
			
			/*for (unsigned i = 0; i < righe; i++)
			{
				for (unsigned j = 0; j < colonne; j++)
				{
					al_draw_bitmap(nemico[i][j]->getEnemyImage(), nemico[i][j]->x, nemico[i][j]->y, 1);
				}
			}*/

			if (motion)
			{
				for (unsigned i = 0; i < righe; i++)
				{
					for (unsigned j = 0; j < colonne; j++)
					{
						if (nemico[i][j]->getDraw())
						{
							nemico[i][j]->x += nemico[i][j]->getEnemySpeed();
							al_draw_bitmap(nemico[i][j]->getEnemyImage(), nemico[i][j]->x, nemico[i][j]->y, 1);
						}
						/*if (arma != nullptr)
						{
				            if (arma->x >= nemico[i][j]->x && arma->x <= nemico[i][j]->x + al_get_bitmap_width(nemico[i][j]->getEnemyImage()))
							{
								cout << "COLPITO " << nemico[i][j]->x<<" "<<nemico[i][j]->y << endl;
								//nemico[i][j]->setDraw(false);
								//delete arma;
								//arma = nullptr;
							}
						}*/
					}
				}
				if (nemico[l][colonne - 1]->x >= LARGHEZZA-100 && nemico[0][colonne-1]->getDraw()) motion = false;
				else if(l<righe && !nemico[l][colonne-1]->getDraw())
				{
					l++;
				}
			}
			else
			{
				for (unsigned i = 0; i < righe; i++)
				{
					for (unsigned j = 0; j < colonne; j++)
					{
						if (nemico[i][j]->getDraw())
						{
							nemico[i][j]->x -= nemico[i][j]->getEnemySpeed();
							al_draw_bitmap(nemico[i][j]->getEnemyImage(), nemico[i][j]->x, nemico[i][j]->y, 1);
						}
					}
				}
				if (nemico[0][0]->x == 0 && nemico[0][0]->getDraw()) motion = true;
			}

			al_draw_bitmap(giocatore.getPlayerImage(direction), giocatore.x, giocatore.getY(), 0);
			al_flip_display();
		}
	}

	
	//distrugge i nemici
	for (unsigned i = 0; i < righe; i++)
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			delete nemico[i][j];
		}
	}
	//if (arma != nullptr) delete arma;

	//al_destroy_sample(song);
	//al_destroy_sample_instance(canzone);
	al_destroy_bitmap(sfondo);
	al_destroy_bitmap(esc);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	al_destroy_display(display);
	return 0;
}