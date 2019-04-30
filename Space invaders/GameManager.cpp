#include "GameManager.h"
#include <chrono>
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

	//inizializzazione addon
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();
	al_init_font_addon(); 
	al_init_ttf_addon();
	
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(LARGHEZZA, ALTEZZA);
	timer = al_create_timer(1.0 / FPS);

	queue = al_create_event_queue();
	queue2 = al_create_event_queue();

	menuBackground = al_load_bitmap("MenuBackground.png"); //sfondo del menu
	gameBackground = al_load_bitmap("Background.png"); //sfondo del gioco
	menuText = al_load_bitmap("spaceInvadersMenu.png"); //testo visualizzato nel menu

	//immagini dei bottoni
	startButton = al_load_bitmap("startButton.png");
	startButtonPressed = al_load_bitmap("startButtonPressed.png");
	startButtonPressedLong = al_load_bitmap("startButtonPressedLong.png");

	escButton = al_load_bitmap("exitButton.png");
	escButtonPressed = al_load_bitmap("exitButtonPressed.png");
	escButtonPressedLong = al_load_bitmap("exitButtonPressedLong.png");

	optionButton = al_load_bitmap("optionButton.png");
	optionButtonPressed = al_load_bitmap("optionButtonPressed.png");
	optionButtonPressedLong = al_load_bitmap("optionButtonPressedLong.png");

	font = al_load_ttf_font("alien.ttf", 72, 0);
	cout << "game manager creato" << endl;
}

GameManager::~GameManager()
{
	al_destroy_event_queue(queue);
	al_destroy_event_queue(queue2);

	al_destroy_bitmap(menuBackground);
	al_destroy_bitmap(gameBackground);

	al_destroy_bitmap(optionButton);
	al_destroy_bitmap(optionButtonPressed);
	al_destroy_bitmap(optionButtonPressedLong);

	al_destroy_bitmap(escButton);
	al_destroy_bitmap(escButtonPressed);
	al_destroy_bitmap(escButtonPressedLong);

	al_destroy_bitmap(startButton);
	al_destroy_bitmap(startButtonPressed);
	al_destroy_bitmap(startButtonPressedLong);

	al_destroy_bitmap(menuText);
	al_destroy_font(font);
	al_destroy_timer(timer);
	cout << "game manager distrutto" << endl;
}

bool GameManager::enemies_initialize(Nemico* nemico[][9], unsigned righe, unsigned colonne) //private
{
	//inizializza le coordinate dei nemici
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
	al_pause_event_queue(queue2, false);
	al_register_event_source(queue2, al_get_mouse_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));
	MotoreGrafico::draw(menuBackground, 0, 0);
	MotoreGrafico::draw(menuText, (LARGHEZZA / 2) - (al_get_bitmap_width(menuText) / 2), 50);

	//start button
	if (mouseEvent.mouse.x >= (LARGHEZZA / 2) - (al_get_bitmap_width(startButtonPressed) / 2) &&
		mouseEvent.mouse.x <= (LARGHEZZA / 2) - (al_get_bitmap_width(startButtonPressed) / 2) + al_get_bitmap_width(startButtonPressed) &&
		mouseEvent.mouse.y >= (ALTEZZA / 2) - (al_get_bitmap_height(startButtonPressed) / 2) - 50 &&
		mouseEvent.mouse.y <= (ALTEZZA / 2) - (al_get_bitmap_height(startButtonPressed) / 2) - 50 + al_get_bitmap_height(startButtonPressed))

	{
		MotoreGrafico::draw(startButtonPressed, (LARGHEZZA / 2) - (al_get_bitmap_width(startButtonPressed) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(startButtonPressed) / 2) - 50);
		
		if (mouseEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			MotoreGrafico::draw(startButtonPressedLong, (LARGHEZZA / 2) - (al_get_bitmap_width(startButtonPressedLong) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(startButtonPressedLong) / 2) - 50);
		}
		if (mouseEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) { level1(); return true; }
	}
	else
	{
		MotoreGrafico::draw(startButton, (LARGHEZZA / 2) - (al_get_bitmap_width(startButton) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(startButton) / 2) - 50);
	}

	//option button
	if (mouseEvent.mouse.x >= (LARGHEZZA / 2) - (al_get_bitmap_width(optionButtonPressed) / 2) &&
		mouseEvent.mouse.x <= (LARGHEZZA / 2) - (al_get_bitmap_width(optionButtonPressed) / 2) + al_get_bitmap_width(optionButtonPressed) &&
		mouseEvent.mouse.y >= (ALTEZZA / 2) - (al_get_bitmap_height(optionButtonPressed) / 2) + 175 &&
		mouseEvent.mouse.y <= (ALTEZZA / 2) - (al_get_bitmap_height(optionButtonPressed) / 2) + 175 + al_get_bitmap_height(optionButtonPressed))

	{
		MotoreGrafico::draw(optionButtonPressed, (LARGHEZZA / 2) - (al_get_bitmap_width(optionButtonPressed) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(optionButtonPressed) / 2) + 175);
		if (mouseEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			MotoreGrafico::draw(optionButtonPressedLong, (LARGHEZZA / 2) - (al_get_bitmap_width(optionButtonPressedLong) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(optionButtonPressedLong) / 2) + 175);
		}
	}
	else
	{
		MotoreGrafico::draw(optionButton, (LARGHEZZA / 2) - (al_get_bitmap_width(optionButton) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(optionButton) / 2) + 175);
	}

	//exit button
	if (mouseEvent.mouse.x >= (LARGHEZZA / 2) - (al_get_bitmap_width(escButton) / 2) &&
		mouseEvent.mouse.x <= (LARGHEZZA / 2) - (al_get_bitmap_width(escButton) / 2) + al_get_bitmap_width(escButton) &&
		mouseEvent.mouse.y >= (ALTEZZA / 2) - (al_get_bitmap_height(escButton) / 2) + 400 &&
		mouseEvent.mouse.y <= (ALTEZZA / 2) - (al_get_bitmap_height(escButton) / 2) + 400 + al_get_bitmap_height(escButton))

	{
		MotoreGrafico::draw(escButtonPressed, (LARGHEZZA / 2) - (al_get_bitmap_width(escButton) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(escButton) / 2) + 400);
		if (mouseEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			MotoreGrafico::draw(escButtonPressedLong, (LARGHEZZA / 2) - (al_get_bitmap_width(escButtonPressedLong) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(escButtonPressedLong) / 2) + 400);
		}
		if (mouseEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			return true;
		}
	}
	else
	{
		MotoreGrafico::draw(escButton, (LARGHEZZA / 2) - (al_get_bitmap_width(escButton) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(escButton) / 2) + 400);
	}
	MotoreGrafico::refreshDisplay();
	al_wait_for_event(queue2, &mouseEvent);
	return false;
}

void GameManager::level1()
{
	al_pause_event_queue(queue2, true);
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	Player giocatore;

	//gestione translate nemico
	int xToStart = 200;
	int yToStart = 400;
	//fine gestione translate

	const unsigned righe = 5; //matrix's rows
	const unsigned colonne = 9; //matrix's columns
	Nemico* nemico[righe][colonne]; //puntatori a nemico per polimorfismo
	//crea i nemici
	for (unsigned i = 0; i < righe; i++)
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			if (i == 0) nemico[i][j] = new Nemico3; //il nemico più forte sulla prima riga
			else if (i == 1) nemico[i][j] = new Nemico2; //il nemico medio sulla seconda riga
			else if (i > 1) nemico[i][j] = new Nemico1; //il nemico più scarso sulle altre righe
		}
	}

	for (unsigned i = 0; i < righe; i++) //controlla se i nemici sono creati nel giusto modo e stampa le loro posizioni
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			cout << " " << nemico[i][j]->getTipo() << " ";
		}
		cout << endl;
	}

	cout << enemies_initialize(nemico, righe, colonne) << endl; //funzione che inizializza i nemici
	srand(time(NULL));

	short unsigned allEnemiesKilled = 0;
	auto tempoInizio = chrono::steady_clock::now(); //serve pre spostare i nemici in basso
	al_rest(0.05);
	bool close = false; //per chiudere il gioco
	bool aggiornaNemici = false;
	while (!close)
	{
		DIRECTION direction = OTHER; //direzione che viene passata a getPlayerImage() per restituire la giusta animazione
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);

		MotoreGrafico::draw(gameBackground, 0, 0);

		if (evento.type == ALLEGRO_EVENT_TIMER)
		{
			stringstream vite; //stampa delle vite
			vite << giocatore.getLife();
			string temp_str = vite.str();
			const char* char_type = temp_str.c_str();
			al_draw_text(font, al_map_rgb(255, 0, 0), 60, ALTEZZA - 90, ALLEGRO_ALIGN_CENTRE, char_type);//stampa le vite

			stringstream punteggio; //stampa del punteggio
			punteggio << giocatore.getScore();
			string tempPunteggio = punteggio.str();
			const char* punteggio2 = tempPunteggio.c_str();
			al_draw_text(font, al_map_rgb(255, 0, 0),LARGHEZZA-120 , ALTEZZA-90, ALLEGRO_ALIGN_CENTRE, punteggio2);

			al_get_keyboard_state(&keyState);
			if (al_key_down(&keyState, ALLEGRO_KEY_L)) close = true; //quando premo esc il gioco si chiude
			if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) { giocatore.x -= giocatore.getPlayerSpeed(); direction = LEFT; }
			if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) { giocatore.x += giocatore.getPlayerSpeed(); direction = RIGHT; }

			//scelta random del nemico che deve sparare
			if (enemyshoot == false)
			{
				row_enemy = rand() % 5;
				column_enemy = rand() % 9;
				if (nemico[row_enemy][column_enemy]->getDraw()) 
				{
					if (row_enemy == righe - 1) //se controllo l'ultima riga
					{ 
						armanemico = new Weapon();
						armanemico->x = nemico[row_enemy][column_enemy]->x + 50;//50 = dim/2
						armanemico->y = nemico[row_enemy][column_enemy]->y;
						enemyshoot = true;
					}
					else 
					{
						if (nemico[row_enemy + 1][column_enemy]->getDraw() == false) //se sotto quel nemico non c'è nessuno, spara
						{ 
							armanemico = new Weapon();
							armanemico->x = nemico[row_enemy][column_enemy]->x + 50;//50 = dim/2
							armanemico->y = nemico[row_enemy][column_enemy]->y;
							enemyshoot = true;
						}
					}
				}
			}
			if (armanemico != nullptr && enemyshoot) //sparo del nemico verso il giocatore
			{
				bool playerShooted = false;
				armanemico->y += armanemico->getSpeed();
				al_draw_bitmap(armanemico->getWeaponImage(), armanemico->x, armanemico->y, 1);
				if (armanemico->x >= giocatore.x && armanemico->x <= giocatore.x + 150 && armanemico->y == giocatore.getY() + (float)150.00)
				{
					//giocaore colpito
					playerShooted = true;
				}
				if (playerShooted == true)//giocatore colpito
				{
					--giocatore;
					playerShooted = false;
				}
				if (armanemico->y >= ALTEZZA && armanemico != nullptr && playerShooted == false)
				{
					delete armanemico;
					armanemico = nullptr;
				}
			}
			if (armanemico == nullptr) //gestione random shoot nemico 
			{
				//numero = rand() % 100 + 1;
				//if (numero == 3) 
				enemyshoot = false;
			}
			//fine gestione arma nemici

			if (al_key_down(&keyState, ALLEGRO_KEY_SPACE) && !shoot) //spara premendo space
			{
				shoot = true;
				arma = new Weapon();
				arma->x = giocatore.x + 72;
				arma->y = giocatore.getY();
			}
			if (shoot) //sparo del giocatore
			{
				arma->y -= arma->getSpeed();
				al_draw_bitmap(arma->getWeaponImage(), arma->x, arma->y, 1);

				//**DA CONTROLLARE**//

				//collisioni
				for (int i = righe - 1; i >= 0; i--)  //collisone arma giocatore con i nemici
				{
					bool shooted = false;
					int vx;
					int vy;
					for (int j = 0; j < colonne; j++) 
					{
						if (arma->x >= nemico[i][j]->x && arma->x <= nemico[i][j]->x + 100 && arma->y <= nemico[i][j]->y + 100 && nemico[i][j]->getDraw()) 
						{
							allEnemiesKilled++;
							shooted = true;
							vx = i;
							vy = j;
							break;
						}
					}

					if (shooted)
					{
						giocatore.gestionePunteggio(nemico[vx][vy], shoot);
						//giocatore.setScore(gestionePunteggio( giocatore.getScore()));
						break;
					}
				}
				//**FINE CONTROLLI COLLISIONI***//

				if ((arma->y <= 0) && arma != nullptr) //quando il limite dello schermo è raggiunto elimina l'arma del giocatore
				{
					shoot = false;
					delete arma;
					arma = nullptr;
				}
			}//fine dello sparo

			if (al_key_down(&keyState, ALLEGRO_KEY_C)) easter[0] = true;
			if (al_key_down(&keyState, ALLEGRO_KEY_A)) easter[1] = true;
			if (al_key_down(&keyState, ALLEGRO_KEY_O)) easter[2] = true;

			if (motion)
			{
				for (unsigned i = 0; i < righe; i++)
				{
					for (unsigned j = 0; j < colonne; j++)
					{
						if (nemico[i][j] != nullptr) 
						{
							if (nemico[i][j]->getDraw())
							{
								nemico[i][j]->x += nemico[i][j]->getEnemySpeed();
								MotoreGrafico::draw(*nemico[i][j]);
							}
						}
					}
				}
				//controlla il movimento dei nemici verso destra
				int yToControl = -1;
				for (int j = colonne - 1; j >= 0; j--) 
				{
					if (nemico[0][j]->getDraw()) 
					{
						yToControl = j;
						break;
					}
				}
				if (yToControl != -1 && nemico[0][yToControl]->getDraw()) //quando il limite dello schermo è raggiunto i nemici cambiano direzione
				{
					if (nemico[0][yToControl]->x >= (float)(LARGHEZZA - 100)) 
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
							MotoreGrafico::draw(*nemico[i][j]);
						}
					}
				}
				//controlla il movimento dei nemici verso sinistra
				int xToControl = -1;
				for (int j = 0; j < colonne; j++) 
				{
					if (nemico[0][j]->getDraw()) 
					{
						xToControl = j;
						break;
					}
				}
				if (xToControl != -1 && nemico[0][xToControl]->getDraw()) //quando il limite dello schermo è raggiunto i nemici cambiano direzione
				{
					if (nemico[0][xToControl]->x == 0) 
					{
						motion = true;
					}
				}
			}

			if (giocatore.x < 0) //in questo modo il giocatore non esce fuori dal display
			{
				MotoreGrafico::draw(giocatore, OTHER);
				//al_draw_bitmap(giocatore.getPlayerImage(OTHER), 0, giocatore.getY(), 1);
				giocatore.x = 0;
			}
			else if (giocatore.x > LARGHEZZA - al_get_bitmap_width(giocatore.getPlayerImage(OTHER)))
			{
				MotoreGrafico::draw(giocatore, OTHER);
				//al_draw_bitmap(giocatore.getPlayerImage(OTHER), LARGHEZZA - 150, giocatore.getY(), 1);
				giocatore.x = LARGHEZZA - al_get_bitmap_width(giocatore.getPlayerImage(OTHER));
			}
			else MotoreGrafico::draw(giocatore, direction);

			MotoreGrafico::refreshDisplay();
		}//fine event timer

		if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
		{
			al_pause_event_queue(queue, true);
			pause();
			al_rest(0.25);
			al_pause_event_queue(queue, false);
		}

		if (giocatore.getLife() == 0) //gestione vite
		{
			close = true; //implementare la schermata di game over
		}
		if (allEnemiesKilled == 45)
		{
			close = true;
			winScreen();
		}

		auto tempoFine = chrono::steady_clock::now();
		//cout << "tempo " << chrono::duration_cast<chrono::seconds>(tempoFine - tempoInizio).count() << endl;
		if (chrono::duration_cast<chrono::seconds>(tempoFine - tempoInizio).count() % 4 == 0 && 
			chrono::duration_cast<chrono::seconds>(tempoFine - tempoInizio).count() > 0 && !aggiornaNemici)
		{
			cout << aggiornaCoordinate(nemico, righe, colonne,giocatore.getY(),close);
			aggiornaNemici = true;
			//cout << "tempo "<< chrono::duration_cast<chrono::seconds>(tempoFine - tempoInizio).count()<< endl;
		}
		else 
		{
			aggiornaNemici = false;
		}

		
	}
	
	//dealloca i nemici
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
	stringstream strs;
	strs << "YOU WIN";
	string temp_str = strs.str();
	char * char_type = (char *)temp_str.c_str();
	al_draw_text(font, al_map_rgb(255, 0, 0), 200, 0, ALLEGRO_ALIGN_CENTRE, char_type);
	MotoreGrafico::refreshDisplay();
	al_rest(4);
}

void GameManager::pause()
{
	ALLEGRO_BITMAP* pausa = al_load_bitmap("pauseBackground.png");
	al_pause_event_queue(queue2, false);
	bool close2 = false;
	while (!close2)
	{
		al_get_keyboard_state(&keyState);
		//al_register_event_source(queue2, al_get_mouse_event_source());
		MotoreGrafico::draw(pausa, 0, 0);

		if (mouseEvent.mouse.x >= (LARGHEZZA / 2) - (al_get_bitmap_width(escButton) / 2) &&
			mouseEvent.mouse.x <= (LARGHEZZA / 2) - (al_get_bitmap_width(escButton) / 2) + al_get_bitmap_width(escButton) &&
			mouseEvent.mouse.y >= (ALTEZZA / 2) - (al_get_bitmap_height(escButton) / 2) + 400 &&
			mouseEvent.mouse.y <= (ALTEZZA / 2) - (al_get_bitmap_height(escButton) / 2) + 400 + al_get_bitmap_height(escButton))
		{
			MotoreGrafico::draw(escButtonPressed, (LARGHEZZA / 2) - (al_get_bitmap_width(escButton) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(escButton) / 2) + 400);
			if (mouseEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				MotoreGrafico::draw(escButtonPressedLong, (LARGHEZZA / 2) - (al_get_bitmap_width(escButtonPressedLong) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(escButtonPressedLong) / 2) + 400);
			}
			if (mouseEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				close2 = true;
			}
		}
		else
		{
			MotoreGrafico::draw(escButton, (LARGHEZZA / 2) - (al_get_bitmap_width(escButton) / 2), (ALTEZZA / 2) - (al_get_bitmap_height(escButton) / 2) + 400);
		}
		al_wait_for_event(queue2,&mouseEvent);
		MotoreGrafico::refreshDisplay();
	}
		
	al_destroy_bitmap(pausa);
}

bool GameManager::aggiornaCoordinate(Nemico* nemico[][9], unsigned righe, unsigned colonne, float playerY, bool& close)
{
	for (unsigned i = 0; i < righe; i++)
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			nemico[i][j]->y += 2;
		}
	}

	for (unsigned i = 0; i < righe; i++)
	{
		for (unsigned j = 0; j < colonne; j++)
		{
			if (playerY <= nemico[i][j]->y + al_get_bitmap_height(nemico[i][j]->getEnemyImage()) && nemico[i][j]->getDraw())
			{
				close = true;
			}
		}
	}

	return true;
}