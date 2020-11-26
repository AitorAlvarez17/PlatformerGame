#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Collisions.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"

Scene::Scene(bool startEnabled) : Module(startEnabled)
{
	name.create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// L03: DONE: Load map
	fullScreenRect = SDL_Rect({ 0, 0, app->render->camera.w, app->render->camera.h });
	
	//pushbacks for anims

	app->map->Load("GAME.tmx");
	bgTexture = app->tex->Load("Assets/maps/MenuF.png");
	bgTexture2 = app->tex->Load("Assets/maps/Gameover.png");
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");


	

	return true;
}


// Called each loop iteration
bool Scene::PreUpdate()
{
	
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	// L02: TODO 3: Request Load / Save when pressing L/S

	/*if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();*/

	
	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

	//Draw Map
	
	
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && gameplayState == TITLE_SCREEN)
	{
		FadeToNewState(PLAYING);
	}
	if (gameplayState != targetState)
	{
		currentFade += 0.02f;
		if (currentFade >= 1.0f)
		{
			currentFade = 1.0f;
			ChangeGameplayState(targetState);
		}
	}
	else if (currentFade > 0.0f)
	{
		currentFade -= 0.02f;
	}
	else if (currentFade <= 0.0f)
	{
		currentFade = 0.0f;
		fading = false;
	}

	//screenDisplayAnim->Update();
	if (app->player->lvl1 == false)
	{
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			
		}
	}
	if (app->player->isDead == true) 
	{
		FadeToNewState(GAME_OVER_SCREEN);
		app->player->position.x = 961;
		app->player->position.y = 80;
		if(app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			app->player->isDead = false;
			app->player->position.x = 600;
			app->player->position.y = 2816;
			app->player->vy = 0;
			app->player->jumps = 0;
		/*	app->render->camera.x = app->player->position.x;
			app->render->camera.y = app->player->position.y;*/
			app->player->lvl1 = true;
		}

	}
	if (app->player->lvl1 == true)
	{
		
	}
	
	app->map->LoadColliders();

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d", app->map->data.width, app->map->data.height, app->map->data.tileWidth, app->map->data.tileHeight, app->map->data.tilesets.count());

	app->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;
	
	

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	app->map->Draw();
	if (gameplayState == TITLE_SCREEN)
	{
		app->render->DrawTexture(bgTexture, 0, 0);
	}
	app->render->DrawTexture(bgTexture2, 641, 0);

	//FADE TO BLACK
	//SDL_Rect rect = screenDisplayAnim->GetCurrentFrame();

	float adjustedFade = currentFade;
	if (adjustedFade < 0.0f) adjustedFade = 0.0f;
	if (adjustedFade > 1.0f) adjustedFade = 1.0f;

	int alpha = adjustedFade * 255.0f;
	
	app->render->DrawRectangle(fullScreenRect, 0, 0, 0, alpha, true, false);

	
	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void Scene::FadeToNewState(GameplayState newState)
{
	if (gameplayState == newState) return;
	if (fading) return;
	targetState = newState;
	currentFade = 0.0f;
	fading = true;
}

void Scene::ChangeGameplayState(GameplayState newState)
{
	if (gameplayState == newState) return;

	switch (newState)
	{
	case PLAYING:
		//screenDisplayAnim = &turnOffAnim;
		app->player->Init();
		app->map->Init();
		gameplayState = PLAYING;
		//currentLevel.Create("level1.tmx");
		app->map->Load("GAME.tmx");
		app->tex->UnLoad(bgTexture);
		//PLAYER
		app->player->position.x = 600;
		app->player->position.y = 2816;
		app->player->vy = 0;
		app->player->jumps = 0;
		app->player->lvl1 = true;
		//app->player->Reload();
		break;
	case TITLE_SCREEN:
		//screenDisplayAnim = &titleScreenAnim;
		gameplayState = TITLE_SCREEN;
		app->player->Disable();
		app->map->Disable();
		app->render->camera.x = 0;
		app->render->camera.y = 0;
		break;
	case GAME_OVER_SCREEN:
		//screenDisplayAnim = &gameOverAnim;
		gameplayState = GAME_OVER_SCREEN;
		app->map->CleanUp();
		app->render->camera.x = 0;
		app->render->camera.y = 0;
		break;
	}
}
