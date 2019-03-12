#include "GameManager.h"
#define FPS 120 
#define ALTEZZA 1080 //height
#define LARGHEZZA 1920 //width

GameManager::GameManager()
{

	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERRORE", "ERRORE", "NON INIZIALIZZATO", "OK", ALLEGRO_MESSAGEBOX_ERROR);
	}
	if (!al_init_primitives_addon())
	{
		al_show_native_message_box(NULL, "ERRORE", "ERRORE", "NON INIZIALIZZATO", "OK", ALLEGRO_MESSAGEBOX_ERROR);
	}

	//addon's initialization
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf 
	
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(LARGHEZZA, ALTEZZA);
	timer = al_create_timer(1.0 / FPS);
	queue = al_create_event_queue();
	queue2 = al_create_event_queue();
	menuBackground = al_load_bitmap("MenuBackground.png");
	gameBackground = al_load_bitmap("Background.png"); //background
	menuText = al_load_bitmap("spaceInvadersMenu.png");
	startButton = al_load_bitmap("startButton.png");
	startButtonPressed = al_load_bitmap("startButtonPressed.png");
	escButton = al_load_bitmap("exitButton.png");
	escButtonPressed = al_load_bitmap("exitButtonPressed.png");
	optionButton = al_load_bitmap("optionButton.png");
	optionButtonPressed = al_load_bitmap("optionButtonPressed.png");
	font = al_load_ttf_font("alien.ttf", 72, 0);
	cout << "game manager creato" << endl;
	
}

GameManager::~GameManager()
{
	for (unsigned i = 0; i < 3; i++)
	{
		delete barriere[i];
	}
	al_destroy_event_queue(queue);
	al_destroy_event_queue(queue2);
	al_destroy_bitmap(menuBackground);
	al_destroy_bitmap(gameBackground);
	al_destroy_bitmap(optionButton);
	al_destroy_bitmap(optionButtonPressed);
	al_destroy_bitmap(escButton);
	al_destroy_bitmap(escButtonPressed);
	al_destroy_bitmap(startButtonPressed);
	al_destroy_bitmap(startButton);
	al_destroy_bitmap(menuText);
	al_destroy_font(font);
	al_destroy_timer(timer);
	cout << "game manager distrutto" << endl;
}

bool GameManager::enemies_initialize(Nemico* nemico[][9], int righe, int colonne) //private
{
	//initialize enemies coordinates
	for (unsigned j = 1; j < colonne; j++)
	{
		nemico[0][j]->x = nemico[0][j - 1]->x + al_get_bitmap_width(nemico[0][j]->getEnemyImage()) + 70;
	}

	for (unsigned i = 1; i < righe; i++)
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			if (j == 0)
			{
				nemico[i][j]->y = nemico[i - 1][j]->y + al_get_bitmap_width(nemico[i][j]->getEnemyImage());
			}
			else
			{
				nemico[i][j]->x = nemico[i][j - 1]->x + al_get_bitmap_width(nemico[i][j]->getEnemyImage()) + 70;
				nemico[i][j]->y = nemico[i - 1][j]->y + al_get_bitmap_width(nemico[i][j]->getEnemyImage());
			}
		}
	}
	cout << endl << endl;
	return true;
} 

bool GameManager::menu()
{
	al_register_event_source(queue2, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_get_keyboard_state(&keyState);
	al_get_mouse_state(&mouseState);
	
	/*Nemico* nemico[3];
	nemico[0] = new Nemico1;
	nemico[1] = new Nemico2;
	nemico[2] = new Nemico3;*/
	
	//bool close = false;
	/*for (unsigned i = 0; i < 3; i++)
	{
		nemico[i]->y = rand() % ALTEZZA;
	}*/

	//while (!close)
	//{
		al_draw_bitmap(menuBackground, 0, 0, 1);

		
		/*for (unsigned i = 0; i < 3; i++)
		{
			if (nemico[i]->getDraw())
			{
				nemico[i]->x += nemico[i]->getEnemySpeed();
				al_draw_bitmap(nemico[i]->getEnemyImage(), nemico[i]->x, nemico[i]->y, 1);
			}
		}*/

		al_draw_bitmap(menuText, (LARGHEZZA / 2) - (al_get_bitmap_width(menuText) / 2), 50, 0);

		//start button
		if (mouseState.x >= (LARGHEZZA / 2) - (al_get_bitmap_width(startButtonPressed) / 2) &&
			mouseState.x <= (LARGHEZZA / 2) - (al_get_bitmap_width(startButtonPressed) / 2) + al_get_bitmap_width(startButtonPressed) &&
			mouseState.y >= (ALTEZZA / 2) - (al_get_bitmap_height(startButtonPressed) / 2) - 50 &&
			mouseState.y <= (ALTEZZA / 2) - (al_get_bitmap_height(startButtonPressed) / 2) - 50 + al_get_bitmap_height(startButtonPressed))

		{
			al_draw_bitmap(startButtonPressed, (LARGHEZZA / 2) - (al_get_bitmap_width(startButton) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(startButton) / 2) - 50, 0);
			if (al_mouse_button_down(&mouseState, 1)) return true;
		}
		else
		{
			al_draw_bitmap(startButton, (LARGHEZZA / 2) - (al_get_bitmap_width(startButton) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(startButton) / 2) - 50, 0);
		}

		//option button
		if (mouseState.x >= (LARGHEZZA / 2) - (al_get_bitmap_width(optionButtonPressed) / 2) &&
			mouseState.x <= (LARGHEZZA / 2) - (al_get_bitmap_width(optionButtonPressed) / 2) + al_get_bitmap_width(optionButtonPressed) &&
			mouseState.y >= (ALTEZZA / 2) - (al_get_bitmap_height(optionButtonPressed) / 2) + 175 &&
			mouseState.y <= (ALTEZZA / 2) - (al_get_bitmap_height(optionButtonPressed) / 2) + 175 + al_get_bitmap_height(optionButtonPressed))

		{
			al_draw_bitmap(optionButtonPressed, (LARGHEZZA / 2) - (al_get_bitmap_width(optionButtonPressed) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(optionButtonPressed) / 2) + 175, 0);
		}
		else
		{
			al_draw_bitmap(optionButton, (LARGHEZZA / 2) - (al_get_bitmap_width(optionButton) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(optionButton) / 2) + 175, 0);
		}

		//exit button
		if (mouseState.x >= (LARGHEZZA / 2) - (al_get_bitmap_width(escButton) / 2) &&
			mouseState.x <= (LARGHEZZA / 2) - (al_get_bitmap_width(escButton) / 2) + al_get_bitmap_width(escButton) &&
			mouseState.y >= (ALTEZZA / 2) - (al_get_bitmap_height(escButton) / 2) + 400 &&
			mouseState.y <= (ALTEZZA / 2) - (al_get_bitmap_height(escButton) / 2) + 400 + al_get_bitmap_height(escButton))

		{
			al_draw_bitmap(escButtonPressed, (LARGHEZZA / 2) - (al_get_bitmap_width(escButton) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(escButton) / 2) + 400, 0);
		}
		else
		{
			al_draw_bitmap(escButton, (LARGHEZZA / 2) - (al_get_bitmap_width(escButton) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(escButton) / 2) + 400, 0);
		}

		al_flip_display();
		return false;
	//}

	//for (unsigned i = 0; i < 3; i++)
	//{
	//	delete nemico[i];
	//}
}


void GameManager::level1()
{
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	Player giocatore;

	/*//gestione barriere
	for (int i = 0; i < 3; i++) 
	{
		barriere[i] = new Barrier;
	}

	for (int i = 1; i < 3; i++) 
	{
		//stabilire posizione barriere
		barriere[i]->x = barriere[i - 1]->x + al_get_bitmap_width(barriere[i]->getBarrierImage()) + 100;
	}*/

	//gestione traslate nemico
	int xToStart = 200;
	int yToStart = 400;
	//fine gestione translate

	const unsigned righe = 5; //matrix's lines
	const unsigned colonne = 9; //matrix's columns
	Nemico* nemico[righe][colonne]; //I've created a pointer to enemy for polimorphism
	//create enemies
	for (unsigned i = 0; i < righe; i++)
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			if (i == 0) nemico[i][j] = new Nemico3; //the strongest enemy on the first line
			else if (i == 1) nemico[i][j] = new Nemico2; //the medium enemy on the second line
			else if (i > 1) nemico[i][j] = new Nemico1; //the poorest enemy on other lines
		}
	}

	for (unsigned i = 0; i < righe; i++) //check if enemies are created in the right way
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			cout << " " << nemico[i][j]->getTipo() << " ";
		}
		cout << endl;
	}

	cout << enemies_initialize(nemico, righe, colonne) << endl;
	srand(time(NULL));

	short unsigned allEnemiesKilled = 0;
	
	while (!close)
	{
		DIRECTION direction = OTHER; //direction that I pass to the getPlayerImage()
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);

		/*if (easter[0] && easter[1] && easter[2]) //trigger the easter egg event
		{
			close = true;
			easter_egg(display);
		}*/

		//gestione menu e scelta livelli
		//	l1	->	normal
		//	l2	->	advanced (con barriere)
		//	l3	->	time


		//->gestione mouse
		/*if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1) {
			if (evento.mouse.x >= 821 && evento.mouse.x <= 1098 && evento.mouse.y >= 526 && evento.mouse.y <= 724) {
				cout << "clicked" << endl;
				choose = true;
			}
		}*/

		al_draw_bitmap(gameBackground, 0, 0, 0);

		if (evento.type == ALLEGRO_EVENT_TIMER)
		{
			//test stampa barriere
			/*for (int i = 0; i < 3; i++) {
				al_draw_bitmap(barriere[i]->getBarrierImage(), barriere[i]->x, barriere[i]->y, 1);
			}*/
			//fine test stampa barriere
			if (giocatore.getLife() == 0) //gestione vite
			{
				close = true; //implementare la schermata di game over
			}

			stringstream strs;
			strs << giocatore.getLife();
			string temp_str = strs.str();
			char * char_type = (char *)temp_str.c_str();
			al_draw_text(font, al_map_rgb(255, 0, 0), 100, 0, ALLEGRO_ALIGN_CENTRE, char_type);//life print test

			al_get_keyboard_state(&keyState);
			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) close = true; //when esc is pressed game will end
			if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) { giocatore.x -= giocatore.getPlayerSpeed(); direction = LEFT; }
			if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) { giocatore.x += giocatore.getPlayerSpeed(); direction = RIGHT; }

			//random choose enemy shoot
			if (enemyshoot == false)
			{
				row_enemy = rand() % 5 + 0;
				column_enemy = rand() % 9 + 0;
				if (nemico[row_enemy][column_enemy]->getDraw()) 
				{
					if (row_enemy == righe - 1) //if i'm cecking the last row
					{ 
						armanemico = new Weapon;
						armanemico->x = nemico[row_enemy][column_enemy]->x + 50;//50 = dim/2
						armanemico->y = nemico[row_enemy][column_enemy]->y;
						enemyshoot = true;
					}
					else 
					{
						if (nemico[row_enemy + 1][column_enemy]->getDraw() == false) //if under that enemy there's no one that shoot
						{ 
							armanemico = new Weapon;
							armanemico->x = nemico[row_enemy][column_enemy]->x + 50;//50 = dim/2
							armanemico->y = nemico[row_enemy][column_enemy]->y;
							enemyshoot = true;
						}
					}
				}
			}

			if (al_key_down(&keyState, ALLEGRO_KEY_SPACE) && !shoot) //shooting pressinf space key
			{

				shoot = true;
				arma = new Weapon;
				arma->x = giocatore.x + 72;
				arma->y = giocatore.getY();

			}
			if (armanemico != nullptr && enemyshoot == true) //shoot del nemico verso il giocatore
			{ 
				bool playerShooted = false;
				armanemico->y += armanemico->getSpeed();
				al_draw_bitmap(armanemico->getWeaponImage(), armanemico->x, armanemico->y, 1);
				if (armanemico->x >= giocatore.x && armanemico->x <= giocatore.x + 150 && armanemico->y == giocatore.getY() + 150) 
				{
					//player shooted
					playerShooted = true;
				}
				if (playerShooted == true) --giocatore; //nemico colpito
				if (armanemico->y >= 1080 && armanemico != nullptr && playerShooted == false) 
				{ 
					delete armanemico; 
					armanemico = nullptr; 
				}
				//gestire qui collisioni con barriera con un if(advancedMode)


			}
			if (armanemico == nullptr) //gestione random shoot nemico 
			{
				numero = rand() % 100 + 1;
				if (numero == 3) enemyshoot = false; //3 numero casuale, quando il numero è uguale a 3 attiva lo shoot dei nemici casuali
			}
			//fine gestione arma nemici



			if (shoot) //shoot by player
			{
				arma->y -= arma->getSpeed();
				al_draw_bitmap(arma->getWeaponImage(), arma->x, arma->y, 1);

				//**DA CONTROLLARE**//

				//collision
				for (int i = righe - 1; i >= 0; i--)  //collisone weapon player con nemici
				{
					bool shooted = false;
					int vx;
					int vy;
					for (int j = 0; j < colonne; j++) 
					{
						if (arma->x >= nemico[i][j]->x && arma->x <= nemico[i][j]->x + 100 && arma->y <= nemico[i][j]->y + 100 && nemico[i][j]->getDraw() == true) 
						{
							allEnemiesKilled++;
							shooted = true;
							vx = i;
							vy = j;
							break;
						}
					}
					if (shooted == true) 
					{ 
						nemico[vx][vy]->setDraw(false); 
						shoot = false;  
						break;
					}

				}
				//**FINE CONTROLLI COLLISIONI***//
				//cout <<"Y "<< arma->y << endl;
				if ((arma->y <= 0) && arma != nullptr) //when the top of the screen is reached delete the weapon
				{
					shoot = false;
					delete arma;
					arma = nullptr;
				}
			}//end of shoot
			if (al_key_down(&keyState, ALLEGRO_KEY_C)) easter[0] = true;
			if (al_key_down(&keyState, ALLEGRO_KEY_A)) easter[1] = true;
			if (al_key_down(&keyState, ALLEGRO_KEY_O)) easter[2] = true;

			if (motion)
			{
				for (unsigned i = 0; i < righe; i++)
				{
					for (unsigned j = 0; j < colonne; j++)
					{
						if (nemico[i][j] != nullptr) {
							if (nemico[i][j]->getDraw())
							{
								nemico[i][j]->x += nemico[i][j]->getEnemySpeed();
								al_draw_bitmap(nemico[i][j]->getEnemyImage(), nemico[i][j]->x, nemico[i][j]->y, 1);
							}
						}

					}
				}
				//check translate to dx
				int yToControl = -1;
				for (int j = colonne - 1; j >= 0; j--) 
				{
					if (nemico[0][j]->getDraw()) 
					{
						yToControl = j;
						break;
					}
				}
				if (yToControl != -1 && nemico[0][yToControl]->getDraw()) //when the bound is reached enemies change direction
				{
					if (nemico[0][yToControl]->x >= LARGHEZZA - 100) 
					{
						motion = false;
					}
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
				//check translate to sx...
				int xToControl = -1;
				for (int j = 0; j < colonne; j++) {
					if (nemico[0][j]->getDraw()) {
						xToControl = j;
						break;
					}
				}
				if (xToControl != -1 && nemico[0][xToControl]->getDraw()) {
					//when the bound is reached enemies change direction
					if (nemico[0][xToControl]->x == 0) {
						motion = true;
					}
				}
				//if (nemico[0][0]->x == 0 && nemico[0][0]->getDraw()) motion = true;
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
			//allEnemiesKilled = 45;
			if (allEnemiesKilled == 45)
			{
				close = true;
				winScreen();
			}
			

		}//fine event timer
	//}//fine choose
	}


	//destroy enemies pointers
	for (unsigned i = 0; i < righe; i++)
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			delete nemico[i][j];
		}
	}
}

void GameManager::winScreen()
{
	al_clear_to_color(al_map_rgb(0, 2, 45));
	//al_draw_bitmap(al_load_bitmap("rullo.jpg"), 300, 300, 0);
	stringstream strs;
	strs << "YOU WIN";
	string temp_str = strs.str();
	char * char_type = (char *)temp_str.c_str();
	al_draw_text(font, al_map_rgb(255, 0, 0), 200, 0, ALLEGRO_ALIGN_CENTRE, char_type);//life print test
	al_flip_display();
	al_rest(4);
}