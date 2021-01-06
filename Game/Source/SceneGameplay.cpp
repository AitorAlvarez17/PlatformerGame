#include "SceneGameplay.h"
#include "ModuleUI.h"

#include "Log.h"

SceneGameplay::SceneGameplay(AudioManager* manager, Window* window, EntityManager* eManager, Input* input, ModuleUI* ui)
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

	olympus = tex->Load(PATH("Assets/Textures/Maps/", "olympus.png"));
	clouds = tex->Load(PATH("Assets/Textures/Maps/", "clouds.png"));
	playerText = tex->Load(PATH("Assets/Textures/Character/", "players.png"));
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
	//NUMBERS
	zero = tex->Load(PATH("Assets/Textures/UI/Numbers/", "0.png"));
	one = tex->Load(PATH("Assets/Textures/UI/Numbers/", "1.png"));
	two = tex->Load(PATH("Assets/Textures/UI/Numbers/", "2.png"));
	three = tex->Load(PATH("Assets/Textures/UI/Numbers/", "3.png"));
	four = tex->Load(PATH("Assets/Textures/UI/Numbers/", "4.png"));
	five = tex->Load(PATH("Assets/Textures/UI/Numbers/", "5.png"));
	six = tex->Load(PATH("Assets/Textures/UI/Numbers/", "6.png"));
	seven = tex->Load(PATH("Assets/Textures/UI/Numbers/", "7.png"));
	eight = tex->Load(PATH("Assets/Textures/UI/Numbers/", "8.png"));
	nine = tex->Load(PATH("Assets/Textures/UI/Numbers/", "9.png"));

	x = tex->Load(PATH("Assets/Textures/UI/Numbers/", "money_x.png"));



	// Initialize player
	player = eManager->CreatePlayer(fPoint(5 * 16, 17 * 16));
	player->position = fPoint(200, 470);
	player->SetTexture(playerText);
	eManager->CreateItem(fPoint(200, 500), ItemType::COIN);

	return false;
}

inline bool CheckCollision(SDL_Rect rec1, SDL_Rect rec2)
{
	if ((rec1.x < (rec2.x + rec2.w) && (rec1.x + rec1.w) > rec2.x) &&
		(rec1.y < (rec2.y + rec2.h) && (rec1.y + rec1.h) > rec2.y)) return true;
	else return false;
}

bool SceneGameplay::Update(Input* input, float dt)
{
	//Create a Path
	if (pathCreated > 0)
	{

		// Pathfinding Points
		iPoint dst = map->WorldToMap((int)player->position.x, (int)player->position.y + 32);
		iPoint origin = map->WorldToMap(300, 470);
	
		path->GetInstance()->lastPath.Clear();
		path->GetInstance()->CreatePath(origin, dst);
	}
	//SET THE SETTINGS TO THE SAME ONES AS MENU
	if (settings && buffer)
	{
		music->slider.x = ((aud->volumeMusic * music->bounds.w/100) + music->bounds.x) - music->bounds.w / 100;
		fxVolume->slider.x = ((aud->volumeFx * music->bounds.w / 100) + music->bounds.x) - music->bounds.w / 100;
		if (aud->fullscreenCheck)
		{
			fullscreen->checked = true;
		}
		else if(aud->fullscreenCheck == 0)
		{
			fullscreen->checked = false;
		}
		if (aud->vsyncCheck)
		{
			Vsync->checked = true;
		}
		else if(aud->fullscreenCheck == 0)
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

	if (player->godMode < 0)
	{
		for (int y = 0; y < map->data.height; y++)
		{
			for (int x = 0; x < map->data.width; x++)
			{
				if ((map->data.layers[2]->Get(x, y) >= 65) &&
					CheckCollision(map->GetTilemapRec(x, y), player->GetBounds()))
				{

					// parte de ray, comentala hasta el break;

					SDL_Rect tile = map->GetTilemapRec(x, y);
					// player->position = tempPlayerPosition;
					 //player->onGround = true;
					 //player->max = 0;
					 ////player->ChangeState(WALK);
					 ////create a function that changes the player's state to a new one from the one before.
					 //player->vy = 0.0f;
					 //break;



					 // nuestra parte, descomenta la de abajo para probarlo.


					int compY = player->position.y - tile.y - 20;
					int compX = player->position.x - tile.x;
					bool floor = false;

					if (std::abs(compY) < std::abs(compX))
					{
						if (compX > 0) {
							player->position.x = player->prevPos.x;


							//LOG("LEFT");
						}
						else
						{
							player->position.x = player->prevPos.x;

							//LOG("RIGHT");
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
							//player->position.y = player->prevPos.y;
							player->vy = 0;

							//LOG("DOWN");
						}
						player->hitbox->SetPos(player->position.x, player->position.y);

					}

					//collider->SetPos((int)position.x, (int)position.y);


				}

			}
		}
	}

	if (input->GetKey(SDL_SCANCODE_F9) == KeyState::KEY_UP)
	{
		map->drawColliders = !map->drawColliders;
		pathCreated *= -1;
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

	player->Update(input, dt);
	

	return true;
}

bool SceneGameplay::Draw(Render* render)
{
	//COINS
	switch (coins)
	{
		case 1:
			number = one;
			break;
		case 2:
			number = two;
			break;
		case 3:
			number = three;
			break;
		case 4:
			number = four;
			break;
		case 5:
			number = five;
			break;
		case 6:
			number = six;
			break;
		case 7:
			number = seven;
			break;
		case 8:
			number = eight;
			break;
		case 9:
			number = nine;
			break;
	default:
		number = zero;
		break;
	}
	//Draw BG
	render->SetBackgroundColor({ 83,217,217, 1 });
	render->DrawTexture(olympus, 0, 1900);
	render->DrawTexture(clouds, render->camera.x, 1900);

	// Draw map
	map->Draw(render);

	player->Draw(render);


	if (pathCreated > 0)
    	path->GetInstance()->DrawPath(render);



	//MONEY UI
	render->DrawTexture(moneyBackgroundUi, 1150, 0, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(number, 1150, 0, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(x, 1150, 0, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	//HEALTH BACKGROUND
	//ui->DrawHealth(render);
	//ABILITY UI
	render->DrawTexture(backgroundUi, 490, 625, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(habUi, 500, 630, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(habUi, 600, 630, 0, 0, 0, 0, 0, SDL_FLIP_NONE);

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

bool SceneGameplay::Unload()
{
	// TODO: Unload all resources

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
		else if (control->id == 8) TransitionToScene(SceneType::TITLE);
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
