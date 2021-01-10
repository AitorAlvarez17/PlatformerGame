#include "SceneGameplay.h"
#include "ModuleUI.h"

#include "Log.h"

SceneGameplay::SceneGameplay(AudioManager* manager, Window* window, EntityManager* eManager, Input* input, ModuleUI* ui, Collisions* coll, App* app, CheckPoints* check)
{
	name = "GAMEPLAY";
	btnResume = new GuiButton(6, { 1280 / 2 - 300 / 2, 155, 300, 80 }, "RESUME");
	btnResume->SetObserver(this);

	btnSettings = new GuiButton(7, { 1280 / 2 - 300 / 2, 275, 300, 80 }, "SETTINGS");
	btnSettings->SetObserver(this);

	btnBackToTitle = new GuiButton(8, { 1280 / 2 - 300 / 2, 395, 300, 80 }, "BACKTOTITLE");
	btnBackToTitle->SetObserver(this);

	btnExit = new GuiButton(9, { 1280 / 2 - 300 / 2, 515, 300, 80 }, "EXIT");
	btnExit->SetObserver(this);

	btnBack = new GuiButton(10, { 1280 / 2 - 300 / 2, 520, 300, 80 }, "EXIT");
	btnBack->SetObserver(this);

	fullscreen = new GuiCheckBox(11, { 320, 400, 80, 80 }, "fullscreen");
	fullscreen->SetObserver(this);

	Vsync = new GuiCheckBox(12, { 880, 400, 80, 80 }, "Vsync");
	Vsync->SetObserver(this);

	music = new GuiSlider(13, { 1280 / 2 - 600 / 2, 170, 600, 30 }, "music");
	music->SetObserver(this);

	fxVolume = new GuiSlider(14, { 1280 / 2 - 600 / 2, 270, 600, 30 }, "other");
	fxVolume->SetObserver(this);



	buffer = true;

	this->aud = manager;
	this->win = window;
	this->eManager = eManager;
	this->input = input;
	this->ui = ui;
	this->collisions = coll;
	this->app = app;
}

SceneGameplay::~SceneGameplay()
{}

bool SceneGameplay::Load(Textures* tex) /*EntityManager entityManager)*/
{
	map = new Map(tex);

	// Create walkability map on map loading
	if (map->Load("main_level.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		if (map->CreateWalkabilityMap(w, h, &data))
		{
			path->GetInstance()->SetMap(w, h, data);
		}

		RELEASE_ARRAY(data);
	}

	// Load music
	//AudioManager::PlayMusic("Assets/Audio/Music/music_spy.ogg");

	// Load game entities
	//Player* player = (Player*)entityManager->CreateEntity(EntityType::PLAYER);
	//player->SetTexture(tex->Load("Assets/Textures/player.png"));
	//entityManager->CreateEntity(EntityType::ENEMY);
	//entityManager->CreateEntity(EntityType::ENEMY);
	//entityManager->CreateEntity(EntityType::ITEM);
	//entityManager->CreateEntity(EntityType::ITEM);
	//entityManager->CreateEntity(EntityType::ITEM);
	coinUi = tex->Load(PATH("Assets/Textures/Items/", "coin.png"));
	olympus = tex->Load(PATH("Assets/Textures/Maps/", "olympus.png"));
	clouds = tex->Load(PATH("Assets/Textures/Maps/", "clouds.png"));
	playerText = tex->Load(PATH("Assets/Textures/Character/", "players.png"));
	enemyText = tex->Load(PATH("Assets/Textures/Character/", "bat.png"));
	fireballTex = tex->Load(PATH("Assets/Textures/Items/", "fireball.png"));
	playText = tex->Load(PATH("Assets/Textures/Ui/", "play.png"));
	continueText = tex->Load(PATH("Assets/Textures/UI/", "continue.png"));
	settingsText = tex->Load(PATH("Assets/Textures/UI/", "settings.png"));
	title = tex->Load(PATH("Assets/Textures/UI/", "title.png"));
	exitText = tex->Load(PATH("Assets/Textures/UI/", "exit.png"));
	backText = tex->Load(PATH("Assets/Textures/UI/", "back.png"));
	backgroundUi = tex->Load(PATH("Assets/Textures/UI/", "background_ui.png"));
	habUi = tex->Load(PATH("Assets/Textures/UI/", "hab_ui.png"));
	moneyBackgroundUi = tex->Load(PATH("Assets/Textures/UI/", "money_background_ui.png"));
	marginsUi = tex->Load(PATH("Assets/Textures/UI/", "margins_ui.png"));
	marginsButtonUi = tex->Load(PATH("Assets/Textures/UI/", "margins_ui_button.png"));
	marginsSlidersUi = tex->Load(PATH("Assets/Textures/UI/", "margins_ui_music_and_fx.png"));
	hearth = tex->Load(PATH("Assets/Textures/UI/", "hearth_ui.png"));
	healthBackground = tex->Load(PATH("Assets/Textures/UI/", "health_background.png"));
	cantSummonUi = tex->Load(PATH("Assets/Textures/UI/", "cant.png"));
	saveFeedback = tex->Load(PATH("Assets/Textures/UI/", "autosave_feedback.png"));
	x = tex->Load(PATH("Assets/Textures/UI/Details/", "money_x.png"));
	wint = tex->Load(PATH("Assets/Textures/UI/", "win.png"));
	lose = tex->Load(PATH("Assets/Textures/UI/", "lose.png"));


	tp1To2 = tex->Load(PATH("Assets/Textures/Maps/Tp/", "1_to_2.png"));
	tp1To3 = tex->Load(PATH("Assets/Textures/Maps/Tp/", "1_to_3.png"));

	tp2To1 = tex->Load(PATH("Assets/Textures/Maps/Tp/", "2_to_1.png"));
	tp2To3 = tex->Load(PATH("Assets/Textures/Maps/Tp/", "2_to_3.png"));

	tp3To1 = tex->Load(PATH("Assets/Textures/Maps/Tp/", "3_to_1.png"));
	tp3To2 = tex->Load(PATH("Assets/Textures/Maps/Tp/", "3_to_2.png"));
	
	openPhrase = tex->Load(PATH("Assets/Textures/Dialogue/", "open_menu.png"));
	teleportPhrase = tex->Load(PATH("Assets/Textures/Dialogue/", "teleport_menu.png"));
	
	//NUMBERS

	cd1 = tex->Load(PATH("Assets/Textures/UI/", "cooldown_1.png"));
	cd2 = tex->Load(PATH("Assets/Textures/UI/", "cooldown_2.png"));
	cd3 = tex->Load(PATH("Assets/Textures/UI/", "cooldown_3.png"));

	x = tex->Load(PATH("Assets/Textures/UI/Details/", "money_x.png"));

	healHab = tex->Load(PATH("Assets/Textures/UI/", "heal_gui.png"));
	fireHab = tex->Load(PATH("Assets/Textures/UI/", "fireball_gui.png"));

	font1Tex = tex->Load(PATH("Assets/Textures/Fonts/", "font.png"));


	// Initialize player
	player = eManager->CreatePlayer(iPoint(5 * 16, 17 * 16));
	player->position = iPoint(384, 2176);
	player->SetTexture(playerText);

	enemy = eManager->CreateEnemy(iPoint(1407, 1920), EnemyType::FLYING, 2, 0, map, player); // ONLY ANIM = 0 for now.
	enemy->SetTexture(enemyText);

	enemy2 = eManager->CreateEnemy(iPoint(1407, 2176), EnemyType::WALKING, 2, 0, map, player); // Enemy 1: 0, Enemy 2: 2, Enemy 3: 4... + 2
	enemy2->SetTexture(playerText);

	eManager->CreateItem(iPoint(768, 2124), ItemType::HEART);
	eManager->CreateItem(iPoint(820, 2124), ItemType::COIN);

	tp = eManager->CreateTp(iPoint(456, 2176), 0);
	tp2 = eManager->CreateTp(iPoint(3697, 31 * 64), 0);
	tp3 = eManager->CreateTp(iPoint(960, 9 * 64), 0);
	save = eManager->CreateSavePoint(iPoint(500, 2176));

	for (int i = 0; i <= 10; i++)
	{
		eManager->CreateDeath(iPoint(-64 - 64 * i, 39 * 64));
	}

	for (int i = 0; i <= 7; i++)
	{
		eManager->CreateDeath(iPoint(40*64 + 64 * i, 39 * 64));
	}

	for (int i = 0; i <= 10; i++)
	{
		eManager->CreateDeath(iPoint(60 * 64 + 64 * i, 39 * 64));
	}

	for (int i = 0; i <= 3; i++)
	{
		eManager->CreateDeath(iPoint(25 * 64 + 64 * i, 13 * 64 - 3));
	}

	font1 = new Font(font1Tex, 45, 3, 16, { 144,24 }, "0123456789.,'!´-@ABCDEFGHIJKLMNOPQRSTUVWXYZ. ");

	if (app->newGame != true)
	{
		if (app->firstSaved == true)
		{
			app->LoadGameRequest();
		}
	}
	end = eManager->CreateWin({ 1 * 64,8 * 68 });

	app->newGame = false;

	return false;
}

inline bool CheckCollision(SDL_Rect rec1, SDL_Rect rec2)
{
	if ((rec1.x < (rec2.x + rec2.w) && (rec1.x + rec1.w) > rec2.x) &&
		(rec1.y < (rec2.y + rec2.h) && (rec1.y + rec1.h) > rec2.y)) return true;
	else return false;
}

bool SceneGameplay::PreUpdate()
{
	player->onColl = false;

	return true;
}

bool SceneGameplay::Update(Input* input, float dt)
{
	if (player->godMode == -1)
		collisions->godMode = false;
	if (player->godMode != -1)
		collisions->godMode = true;

	if (player->isDead == false && end->active == false)
	{
		if (player->position.x > tp->position.x && player->position.x < tp->position.x + tp->width)
		{
			player->onArea1 = true;
			player->outArea = false;
		}
		else
		{
			player->onArea1 = false;
		}
		if (player->position.x > tp2->position.x && player->position.x < tp2->position.x + tp2->width)
		{
			player->onArea2 = true;
			player->outArea = false;
		}
		else
		{
			player->onArea2 = false;
		}
		if (player->position.x > tp3->position.x && player->position.x < tp3->position.x + tp3->width)
		{
			player->onArea3 = true;
			player->outArea = false;
		}
		else
		{
			player->onArea3 = false;
		}

		//SET THE SETTINGS TO THE SAME ONES AS MENU
		if (settings && buffer)
		{
			music->slider.x = ((aud->volumeMusic * music->bounds.w / 100) + music->bounds.x) - music->bounds.w / 100;
			fxVolume->slider.x = ((aud->volumeFx * music->bounds.w / 100) + music->bounds.x) - music->bounds.w / 100;
			if (aud->fullscreenCheck)
			{
				fullscreen->checked = true;
			}
			else if (aud->fullscreenCheck == 0)
			{
				fullscreen->checked = false;
			}
			if (aud->vsyncCheck)
			{
				Vsync->checked = true;
			}
			else if (aud->fullscreenCheck == 0)
			{
				Vsync->checked = false;
			}
			buffer = 0;
		}
		//-----------
		if (menu)
		{
			if (settings == 0 && credits == 0)
			{
				btnResume->Update(input, dt);
				btnSettings->Update(input, dt);
				btnBackToTitle->Update(input, dt);
				btnExit->Update(input, dt);
				btnBack->Update(input, dt);
			}
			else
			{
				btnBack->Update(input, dt);
				fullscreen->Update(input, dt);
				Vsync->Update(input, dt);
				music->Update(input, dt);
				fxVolume->Update(input, dt);
			}
		}


		// Check if updated player position collides with next tile
		// IMPROVEMENT: Just check adyacent tiles to player
		if (input->GetKey(SDL_SCANCODE_G) == KEY_DOWN) player->godMode *= -1;

		iPoint tempPlayerPosition = player->position;

		if (player->godMode < 0)
		{
			for (int y = 0; y < map->data.height; y++)
			{
				for (int x = 0; x < map->data.width; x++)
				{
					if ((map->data.layers[2]->Get(x, y) >= 65) &&
						CheckCollision(map->GetTilemapRecScaled(x, y), player->GetBounds()))
					{
						SDL_Rect tile = map->GetTilemapRecScaled(x, y);

						/*player->position = tempPlayerPosition;
						player->vy = 0.0f;*/
						int compY = player->position.y - tile.y;
						int compX = player->position.x - tile.x;
						bool floor = false;

						if (std::abs(compY) < std::abs(compX))
						{
							if (compX > 0) {
								player->position.x = player->prevPos.x;

							}
							else
							{
								player->position.x = player->prevPos.x;
							}
						}
						else
						{
							if (compY > 0)
							{
								player->position.y = player->prevPos.y;
								//LOG("UP");
							}
							else
							{
								// Comparativa con jumping en player. nueva variable.

								player->position.y = player->prevPos.y;
								player->vy = 0;
								player->jumps = 2;
								//LOG("DOWN");
							}
						}
						break;
					}
				}
			}

		}

		if (input->GetKey(SDL_SCANCODE_F9) == KeyState::KEY_UP)
		{
			map->drawColliders = !map->drawColliders;
			enemy->hasPath *= -1;
			enemy2->hasPath *= -1;
		}

		if (input->GetKey(SDL_SCANCODE_ESCAPE) == KeyState::KEY_DOWN)
		{
			if (menu == true)
			{
				menu = false;

			}
			else
			{
				menu = true;
			}
		}
		// L02: DONE 3: Request Load / Save when pressing L/S
		//if (input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) app->LoadGameRequest();
		//if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) app->SaveGameRequest();

		if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
		{
			if (player->cooldown == 3)
			{
				player->HealAbility();
			}
		}
		if (input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_DOWN)
		{
			if (player->firecooldown == 2)
			{
				player->FireballAbility();
				fireball = eManager->CreateFireball(player->position, 5, player->isGoingRight);
				fireball->SetTexture(fireballTex);

			}
		}
		player->Update(input, dt);
	}
	else if(player->isDead == true)
	{

		if (input->GetKey(SDL_SCANCODE_RETURN) == KeyState::KEY_DOWN)
		{
			TransitionToScene(SceneType::TITLE);
		}

	}

	else if (end->active == true)
	{

	if (input->GetKey(SDL_SCANCODE_RETURN) == KeyState::KEY_DOWN)
	{
		TransitionToScene(SceneType::TITLE);
	}

	}


	return true;
}

bool SceneGameplay::PostUpdate(Input* input, float dt)
{
	if (save->saveActive == true)
	{

	}
	if (save->saveActive == false)
	{
		app->SaveGameRequest();
		save->pendingToDelete = true;
	}
	return true;

}

bool SceneGameplay::Draw(Render* render)
{

	//Draw BG
	if (player->isDead == false && end->active == false)
	{
		render->SetBackgroundColor({ 83,217,217, 1 });
		render->DrawTexture(olympus, 0, 1900);
		render->DrawTexture(clouds, render->camera.x, 1900);

		// Draw map
		map->Draw(render);

		collisions->Draw(render);

		eManager->Draw(render);

		player->Draw(render);



		DrawMenu(render);
		DrawHealth(render);
		DrawMoney(render);
		DrawWand(render);
		DrawTp(render);

		render->DrawText(font1, "WELCOME TO TEMPLARIA!", 620, 2150, 2, false);
		
	}
	else if ( player->isDead == true)
	{
		SDL_Rect rec = { 0,0,1280,720 };
		render->DrawTextTexture(1,lose, 0, 0, &rec);
		//render->DrawText(font1, "GAME OVER!", 325, 300, 5, true);
	}
	else if (end->active == true)
	{
		SDL_Rect rec = { 0,0,1280,720 };
		render->DrawTextTexture(1, wint, 0, 0, &rec);		
		//render->DrawText(font1, "YOU WIN!", 375, 320, 5, true);
	}
	


	return false;
}

bool SceneGameplay::Unload()
{
	// TODO: Unload all resources

		eManager->CleanUp();

	return false;
}

bool SceneGameplay::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		aud->PlayFx(8, 0);
		if (control->id == 6) menu = 0;
		else if (control->id == 7)
		{
			settings = 1;
			music->Start();//music value stored in config ----- read volume value and set slider.x to it
			fxVolume->Start();//fx value stored in config ----- read volume value and set slider.x to it
			Vsync->Start();//set vsync value ---- read it from file and set it to the current state
			fullscreen->Start();//set fullscreen value ---- read it from file and set it to the current state
		}
		else if (control->id == 8)
		{
			TransitionToScene(SceneType::TITLE);
		}
		else if (control->id == 9) input->windowEvents[WE_QUIT] = 1;
		else if (control->id == 10) settings = 0;

	}
	case GuiControlType::CHECKBOX:
	{
		aud->PlayFx(8, 0);
		if (control->id == 11)
		{
			//FULLSCREEN
			if (fullscreen->checked)
			{
				win->ChangeFullscreen(fullscreen->checked);
				aud->fullscreenCheck = 1;

			}
			else
			{
				win->ChangeFullscreen(fullscreen->checked);
				aud->fullscreenCheck = 0;
				//fullscreen changed to aud->fullscreenCheck);

			}

		}
		else if (control->id == 12)
		{
			//VSYNC
			if (Vsync->checked)
			{
				SDL_GL_SetSwapInterval(1);
				aud->vsyncCheck = 1;
				//LOG("ON");
			}
			else
			{
				SDL_GL_SetSwapInterval(0);
				aud->vsyncCheck = 0;
				//LOG("OFF");
			}
		};
	}
	case GuiControlType::SLIDER:
	{
		aud->PlayFx(8, 0);
		if (control->id == 13)
		{
			//mixmusic = music->value;
			aud->VolumeMusic(music->value);
			aud->volumeMusic = music->value;
		}
		else if (control->id == 14)
		{
			//fxmusic = music->value
			aud->VolumeFx(fxVolume->value);
			aud->volumeFx = fxVolume->value;
		}
	}
	default: break;
	}

	return true;
}

bool SceneGameplay::DrawWand(Render* render)
{
	render->DrawTexture(backgroundUi, 490, 625, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(habUi, 500, 630, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(habUi, 600, 630, 0, 0, 0, 0, 0, SDL_FLIP_NONE);

	render->DrawTexture(healHab, 510, 640, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(fireHab, 610, 640, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	if (player->lifes == player->maxLifes)
	{
		if (player->delayUi < 1.0f)
		{
			render->DrawTexture(cantSummonUi, 510, 640, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}
	}
	if (player->cooldown < 3) // HEAL
	{
		if (player->cooldown < 1)
		{
			render->DrawTexture(cd3, 511, 638, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}
		else if (player->cooldown < 2 && player->cooldown > 1)
		{
			render->DrawTexture(cd2, 511, 638, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}
		else if (player->cooldown < 3 && player->cooldown > 2)
		{
			render->DrawTexture(cd1, 511, 638, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}
	}
	if (player->firecooldown < 2) // HEAL
	{
		if (player->firecooldown < 1)
		{
			render->DrawTexture(cd2, 610, 638, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}
		else if (player->firecooldown < 2 && player->firecooldown > 1)
		{
			render->DrawTexture(cd1, 610, 638, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}
	}

	return false;
}

bool SceneGameplay::DrawMoney(Render* render)
{

	render->DrawTexture(moneyBackgroundUi, 1150, 0, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTextTexture(3,coinUi, 1170, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(x, 1150, 0, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	switch (player->coins)
	{
	case 0:
		render->DrawText(font1, "0", 1185, 98, 4, true);

		break;
	case 1:
		render->DrawText(font1, "1", 1185, 98, 4, true);
		
		break;
	case 2:
		render->DrawText(font1, "2", 1185, 98, 3, true);
		
		break;
	case 3:
		render->DrawText(font1, "3", 1185, 98, 3, true);
		
		break;
	case 4:
		render->DrawText(font1, "4", 1185, 98, 3, true);
		
		break;
	case 5:
		render->DrawText(font1, "5", 1185, 98, 3, true);
		
		break;
	case 6:
		render->DrawText(font1, "6", 1185, 98, 3, true);
		
		break;
	case 7:
		render->DrawText(font1, "7", 1185, 98, 3, true);
		
		break;
	case 8:
		render->DrawText(font1, "8", 1185, 98, 3, true);
		break;
	case 9:
		render->DrawText(font1, "9", 1185, 98, 3, true);
		
		break;
	default:
		render->DrawText(font1, "10", 1185, 98, 3, true);
		
		break;
	}


	return false;
}

bool SceneGameplay::DrawHealth(Render* render)
{
	int margin = 4;

	render->DrawTexture(healthBackground, 0, 15, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	if (player->lifes != 0)
	{
		int maxLifes = player->lifes;
		for (int i = 0; i < maxLifes; i++)
		{
			//LOG("lifes loading: %d", i);
			render->DrawTexture(hearth, (5 + (64 * i)) + margin, 18, 0, 0, 0, 0, 0, SDL_FLIP_NONE);


		}
	}


	return false;
}

bool SceneGameplay::DrawMenu(Render* render)
{
	if (menu)
	{
		if (settings)
		{
			//BG
			render->DrawRectangle({ 100, 50, 1080, 620 }, { 100, 200, 200, 255 });
			render->DrawTexture(marginsUi, 100, 50, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
			//BACK BUTTON
			btnBack->Draw(render);
			render->DrawTexture(backText, btnBack->bounds.x, btnBack->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
			render->DrawTexture(marginsButtonUi, btnBack->bounds.x, btnBack->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
			//SLIDERS AND CHECKBOX
			render->DrawRectangle({ fullscreen->bounds.x - 2, fullscreen->bounds.y - 2, fullscreen->bounds.w + 4, fullscreen->bounds.h + 4 }, { 0, 0, 0, 255 });//PURE UI
			fullscreen->Draw(render);
			render->DrawRectangle({ Vsync->bounds.x - 2, Vsync->bounds.y - 2, Vsync->bounds.w + 4, Vsync->bounds.h + 4 }, { 0, 0, 0, 255 });//PURE UI
			Vsync->Draw(render);
			music->Draw(render);
			render->DrawTexture(marginsSlidersUi, music->bounds.x - 20, music->bounds.y - 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
			fxVolume->Draw(render);
			render->DrawTexture(marginsSlidersUi, fxVolume->bounds.x - 20, fxVolume->bounds.y - 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
		}
		else
		{
			//BG
			render->DrawRectangle({ 100, 50, 1080, 620 }, { 100, 200, 200, 255 });
			render->DrawTexture(marginsUi, 100, 50, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
			//RESUME BUTTON
			btnResume->Draw(render);
			render->DrawTexture(playText, 490, 155, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
			render->DrawTexture(marginsButtonUi, btnResume->bounds.x, btnResume->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
			//SETTINGS BUTTON
			btnSettings->Draw(render);
			render->DrawTexture(settingsText, 490, 275, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
			render->DrawTexture(marginsButtonUi, btnSettings->bounds.x, btnSettings->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
			//BACK TO TITLE BUTTON
			btnBackToTitle->Draw(render);
			render->DrawTexture(title, 490, 395, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
			render->DrawTexture(marginsButtonUi, btnBackToTitle->bounds.x, btnBackToTitle->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
			//EXIT BUTTON
			btnExit->Draw(render);
			render->DrawTexture(exitText, 490, 515, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
			render->DrawTexture(marginsButtonUi, btnExit->bounds.x, btnExit->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
		}

	}

	return false;
}

bool SceneGameplay::DrawTp(Render* render)
{
	if (save->saveCoroutine < 2.0f)
	{
		//render->DrawTexture(save_feedback, player->position.x, player->position.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	}
	if (player->onColl == true)
	{
		if (input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
		{
			if (player->mapOpen == true)
			{
				aud->PlayFx(8, 0);
				player->mapOpen = false;

			}
			else
			{
				aud->PlayFx(8, 0);
				player->mapOpen = true;

			}
		}
		if (player->onArea1 && player->mapOpen == true)
		{
			switch (player->tpCounter)
			{
			case 1:
				renderedOption = tp1To2;
				if (input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					aud->PlayFx(8, 0);
					player->position.x = tp2->position.x;
					player->position.y = tp2->position.y;

					player->mapOpen = false;
				}
				break;
			case 2:
				renderedOption = tp1To3;
				if (input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					aud->PlayFx(8, 0);
					player->position.x = tp3->position.x;
					player->position.y = tp3->position.y;

					player->mapOpen = false;
				}
				break;
			}

		}
		if (player->onArea2 && player->mapOpen == true)
		{
			switch (player->tpCounter)
			{
			case 1:
				renderedOption = tp2To1;
				if (input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					aud->PlayFx(8, 0);
					player->position.x = tp->position.x;
					player->position.y = tp->position.y;

					player->mapOpen = false;
				}

				break;
			case 2:
				renderedOption = tp2To3;
				if (input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					aud->PlayFx(8, 0);
					player->position.x = tp3->position.x;
					player->position.y = tp3->position.y;

					player->mapOpen = false;
				}
				break;
			}

		}
		if (player->onArea3 && player->mapOpen == true)
		{
			switch (player->tpCounter)
			{
			case 1:
				renderedOption = tp3To1;
				if (input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					aud->PlayFx(8, 0);
					player->position.x = tp->position.x;
					player->position.y = tp->position.y;

					player->mapOpen = false;
				}
				break;
			case 2:
				renderedOption = tp3To2;
				if (input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					aud->PlayFx(8, 0);
					player->position.x = tp2->position.x;
					player->position.y = tp2->position.y;

					player->mapOpen = false;
				}
				break;
			}

		}
		if (player->onArea1 || player->onArea2 || player->onArea3)
		{
			render->DrawTexture(openPhrase, player->position.x, (player->position.y) - 35);
			if (player->mapOpen)
			{
				render->DrawRectangle({ 0,0,1800, 720 }, { 0,0,0,200 }, true);
				render->DrawTexture(renderedOption, 200, 50, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
				render->DrawTexture(teleportPhrase, 577, 75, 0, 0, 0, 0, SDL_FLIP_NONE);
			}

		}
		if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
		{
			player->tpCounter--;
			aud->PlayFx(8, 0);
			if (player->tpCounter == 0)
			{
				player->tpCounter = 2;
			}

		}
		if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		{
			player->tpCounter++;
			aud->PlayFx(8, 0);
			if (player->tpCounter == 3)
			{
				player->tpCounter = 1;
			}

		}

	}

	return false;
}

bool SceneGameplay::CleanUp()
{

	eManager->CleanUp();
	return true;
}

