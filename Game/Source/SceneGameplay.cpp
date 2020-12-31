#include "SceneGameplay.h"

#include "EntityManager.h"
#include "Log.h"

SceneGameplay::SceneGameplay()
{
	btnResume = new GuiButton(6, { 1280 / 2 - 300 / 2, 155, 300, 80 }, "RESUME");
	btnResume->SetObserver(this);

	btnSettings = new GuiButton(7, { 1280 / 2 - 300 / 2, 275, 300, 80 }, "SETTINGS");
	btnSettings->SetObserver(this);

	btnBackToTitle = new GuiButton(8, { 1280 / 2 - 300 / 2, 395, 300, 80 }, "BACKTOTITLE");
	btnBackToTitle->SetObserver(this);

	btnExit = new GuiButton(9, { 1280 / 2 - 300 / 2, 515, 300, 80 }, "EXIT");
	btnExit->SetObserver(this);

	btnBack = new GuiButton(10, { 1280 / 2 - 300 / 2, 515, 300, 80 }, "EXIT");
	btnBack->SetObserver(this);
	
}

SceneGameplay::~SceneGameplay()
{}

bool SceneGameplay::Load(Textures* tex) /*EntityManager entityManager)*/
{
	map = new Map(tex);

	// L12b: Create walkability map on map loading
	if (map->Load("main_level.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		//if (map->CreateWalkabilityMap(w, h, &data)) pathFinding->SetMap(w, h, data);

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

	background = tex->Load(PATH("Assets/Textures/Maps/", "bg.png"));
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
	healthNameUi = tex->Load(PATH("Assets/Textures/UI/", "hearth_ui.png"));
	healthBackground = tex->Load(PATH("Assets/Textures/UI/", "health_background.png"));
	moneyBackgroundUi = tex->Load(PATH("Assets/Textures/UI/", "money_background_ui.png"));


	// Initialize player
	player = new Player();
	player->position = iPoint(200, 400);
	player->SetTexture(playerText);

    return false;
}

inline bool CheckCollision(SDL_Rect rec1, SDL_Rect rec2)
{
	if ((rec1.x < (rec2.x + rec2.w) && (rec1.x + rec1.w) > rec2.x) &&
		(rec1.y < (rec2.y + rec2.h) && (rec1.y + rec1.h) > rec2.y)) return true;
	else return false;
}

bool SceneGameplay::Update(Input *input, float dt)
{
	// Collision detection: map vs player
	iPoint tempPlayerPosition = player->position;

	// Check if updated player position collides with next tile
	// IMPROVEMENT: Just check adyacent tiles to player
	for (int y = 0; y < map->data.height; y++)
	{
		for (int x = 0; x < map->data.width; x++)
		{
			if ((map->data.layers[2]->Get(x, y) >= 65) && 
				CheckCollision(map->GetTilemapRec(x, y), player->GetBounds()))
			{

				player->position = tempPlayerPosition;
				//player->ChangeState(WALK);
				//create a function that changes the player's state to a new one from the one before.
				player->vy = 0.0f;
				break;
			}
		}
	}

	if (input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_UP) map->drawColliders = !map->drawColliders;
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
	btnResume->Update(input, dt);
	btnSettings->Update(input, dt);
	btnBackToTitle->Update(input, dt);
	btnExit->Update(input, dt);
	btnBack->Update(input, dt);

	return true;
}

bool SceneGameplay::Draw(Render* render)
{
	//Draw BG
	render->DrawTexture(background, player->position.x, player->position.y + 200);
	render->DrawTexture(olympus, 0, 720);
	render->DrawTexture(clouds, render->camera.x, 720);

	// Draw map
	map->Draw(render);

	player->Draw(render);

	//MONEY UI
	render->DrawTexture(moneyBackgroundUi, 1150, 0, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	//HEALTH BACKGROUND
	render->DrawTexture(healthBackground, 0, 15, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	//HEARTHS
	render->DrawTexture(healthNameUi, 15 + 4, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(healthNameUi, 55 + 4, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(healthNameUi, 95 + 4, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(healthNameUi, 135 + 4, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	//ABILITY UI
	render->DrawTexture(backgroundUi, 490, 625, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(habUi, 500, 630, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(habUi, 600, 630, 0, 0, 0, 0, 0, SDL_FLIP_NONE);

	if (menu)
	{
		if (settings)
		{
			render->DrawRectangle({ 100, 50, 1080, 620 }, { 100, 200, 200, 255 });
			btnBack->Draw(render);
			render->DrawTexture(backText, 490, 515, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
			//music volume
			//fx volume
			//fullscreen mode
			//Vsync
		}
		else
		{
			render->DrawRectangle({ 100, 50, 1080, 620 }, { 100, 200, 200, 255 });
			btnResume->Draw(render);
			render->DrawTexture(playText, 490, 155, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
			btnSettings->Draw(render);
			render->DrawTexture(settingsText, 490, 275, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
			btnBackToTitle->Draw(render);
			render->DrawTexture(title, 490, 395, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
			btnExit->Draw(render);
			render->DrawTexture(exitText, 490, 515, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
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
		if (control->id == 6) menu = 0;
		else if (control->id == 7) settings = 1;
		else if (control->id == 8) TransitionToScene(SceneType::TITLE);
		else if (control->id == 9) SDL_Quit();
		else if (control->id == 10) settings = 0;
		
	}
	default: break;
	}

	return true;
}
