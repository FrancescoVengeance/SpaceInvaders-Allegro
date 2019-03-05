#include "Libraries.h"

#define FPS 120 
#define ALTEZZA 1080 //height
#define LARGHEZZA 1920 //width

void easter_egg(ALLEGRO_DISPLAY* display) //function for an future easter egg
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(al_load_bitmap("easter.png"), (1920/2)-250, (1080/2)-200, 0);
	al_flip_display();
	al_rest(5);
}


//double transformation(double& res_y)
//{
//	//ALLEGRO_TRANSFORM scaling;
//	//ALLEGRO_MONITOR_INFO info;
//	//ALLEGRO_DISPLAY_MODE info;
//	/al_get_display_mode(0 , &info);
//	/*int res_monitor_x; 
//	double res_monitor_y;
//	al_get_monitor_info(0, &info);
//	res_monitor_x = info.x2 - info.x1;
//	res_monitor_y = info.y2 - info.y1;
//	res_x = res_monitor_x / (double)LARGHEZZA;
//	res_y = res_monitor_y / (double)ALTEZZA;*/
//
//	res_y = info.height;
//
//	return info.width;
//}


int main(int argc, char **argv)
{	
	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERRORE", "ERRORE", "NON INIZIALIZZATO", "OK", ALLEGRO_MESSAGEBOX_ERROR);
	}

	//addon's initialization
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();

	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	ALLEGRO_DISPLAY* display = al_create_display(LARGHEZZA, ALTEZZA);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_KEYBOARD_STATE keyState; //o creo un puntatore o passo alle funzioni l'indirizzo di memoria con &
	al_register_event_source(queue, al_get_keyboard_event_source()); 
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	ALLEGRO_BITMAP* sfondo = al_load_bitmap("Background.png"); //background

	Player giocatore;

	const unsigned righe = 5; //matrix's lines
	const unsigned colonne = 9; //matrix's columns
	Nemico* nemico[righe][colonne]; //I've created a pointer to enemy for polimorphism

	//create enemies
	for (unsigned i = 0; i < righe; i++)
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			if (i == 0) nemico[i][j] = new Nemico3; //the strongest enemy on the first line
			else if(i == 1) nemico[i][j] = new Nemico2; //the medium enemy on the second line
			else if (i > 1) nemico[i][j] = new Nemico1; //the poorest enemy on other lines
		}
	}

	for (unsigned i = 0; i < righe; i++) //check if enemyes are created in the right way
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			cout << " " << nemico[i][j]->getTipo() << " ";
		}
		cout << endl;
	}

	//initialize enemies coordinates
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
	///////////////////

	bool easter[3] = { false }; //for the easter egg
	bool close = false; //to close the game
	bool motion = true;
	bool shoot = false; //to shooting

	unsigned l = 0; //serve per cambiare riga quando viene distrutto un nemico
	bool leggi = false;
	Weapon* arma = nullptr;

	while (!close) 
	{
		DIRECTION direction = OTHER; //direction that I pass to the getPlayerImage()
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);
			
		cout << "valore y di nemico -> " << nemico[0][0]->y << " " << "valore di x di nemico -> " << nemico[0][0]->x << " " << endl;
		//al_rest(2.0);

		if (easter[0] && easter[1] && easter[2]) //trigger the easter egg event
		{
			close = true;
			easter_egg(display);
		}

		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			//cout << "x " << evento.mouse.x;
			//cout << " y " << evento.mouse.y << endl;
		}
		
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(sfondo, 0, 0, 0);

		if (evento.type == ALLEGRO_EVENT_TIMER)
		{
			al_get_keyboard_state(&keyState);
			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) close = true; //when esc is pressed game will end
			if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) { giocatore.x -= giocatore.getPlayerSpeed(); direction = LEFT; }
			if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) { giocatore.x += giocatore.getPlayerSpeed(); direction = RIGHT; }
			
			if (al_key_down(&keyState, ALLEGRO_KEY_SPACE) && !shoot) //shooting pressinf space key
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
				
				if (arma->x >= (nemico[4][0]->x) && arma->x <= (nemico[4][0]->x)+100) { //test for first enemy 4th row , zero col 40 
					al_clear_to_color(al_map_rgb(255, 0, 0)); 
					al_flip_display();
					cout << "asd" << endl;

					cout << "asd" << endl;
					//check other controls on y etc...
					
				}


				//cout <<"Y "<< arma->y << endl;
				if ((arma->y <= 0) && arma != nullptr) //when the top of the screen is reached delete the weapon
				{
					shoot = false;
					delete arma;
					arma = nullptr;
				}
			}
			if (al_key_down(&keyState, ALLEGRO_KEY_C)) easter[0] = true;
			if (al_key_down(&keyState, ALLEGRO_KEY_A)) easter[1] = true;
			if (al_key_down(&keyState, ALLEGRO_KEY_O)) easter[2] = true;

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
					}
				}
				//when the bound is reached enemies change direction
				if (nemico[0][colonne - 1]->x >= LARGHEZZA - 100 && nemico[0][colonne - 1]->getDraw()) { motion = false; }
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

			if (giocatore.x < 0)
			{
				al_draw_bitmap(giocatore.getPlayerImage(OTHER), 0, giocatore.getY(), 1);
				giocatore.x = 0;
			}
			else if (giocatore.x > LARGHEZZA - 150)
			{
				al_draw_bitmap(giocatore.getPlayerImage(OTHER), LARGHEZZA - 150, giocatore.getY(), 1);
				giocatore.x = LARGHEZZA - 150;
			}
			else al_draw_bitmap(giocatore.getPlayerImage(direction), giocatore.x, giocatore.getY(), 1);
			
			al_flip_display();
		}
	}

	
	//destroy enemies pointers
	for (unsigned i = 0; i < righe; i++)
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			delete nemico[i][j];
		}
	}
	//if (arma != nullptr) delete arma;

	al_destroy_bitmap(sfondo);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	al_destroy_display(display);
	return 0;
}