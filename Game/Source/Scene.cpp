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
#include "ObjectManager.h"
#include "ModuleUI.h"

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

	//app->map->Load("level1.tmx");
	bgTexture = app->tex->Load("Assets/maps/MenuF.png");//por esto ramon descuenta !!!!!
	bgTexture2 = app->tex->Load("Assets/maps/Gameover.png");
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
	app->oManager->AddObject(ObjType::HEART, 2151, 2654,0);
	app->oManager->AddObject(ObjType::COIN, 1053, 2800, 0);
	app->oManager->AddObject(ObjType::COIN, 1315, 2740, 0);
	app->oManager->AddObject(ObjType::COIN, 1572, 2677, 0);
	app->oManager->AddObject(ObjType::COIN, 3269, 2526, 0);
	app->oManager->AddObject(ObjType::COIN, 3014, 2590, 0);
	app->oManager->AddObject(ObjType::COIN, 1667, 1850, 0);
	app->oManager->AddObject(ObjType::COIN, 1537, 1854, 0);
	app->oManager->AddEnemy(600, 2200);


	

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

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		/*app->map->CleanUp();
		
		currentLevel.create("level1.tmx");
		LoadLevel("level1.tmx");


		app->player->collider = app->collisions->AddCollider(app->player->coll, Collider::Type::PLAYER, app->player);


		app->player->lvl2 = false;

		app->player->position.x = app->player->spawnLevel1.x;
		app->player->position.y = app->player->spawnLevel1.y;

		app->player->vy = 0;
		app->player->jumps = 0;

		app->render->camera.x = app->player->position.x;
		app->render->camera.y = app->player->position.y;
		//app->ui->currentLevel = 1;
		app->map->CleanUpLoad();
		app->player->Reload();*/
		
	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		/*app->player->lvl2 = true;
		app->map->CleanUp();
		//app->scene->LoadLevel("level2.tmx");
		app->player->collider = app->collisions->AddCollider(app->player->coll, Collider::Type::PLAYER, app->player);
		app->player->position.x = app->player->spawnLevel2.x;
		app->player->position.y = app->player->spawnLevel2.y;
		//app->ui->currentLevel = 2;
		app->map->CleanUpLoad();
		app->player->Reload();
		LoadLevel("level2.tmx");*/
	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		//LoadLevel(currentLevel);
	}

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
		if(app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && gameplayState == GAME_OVER_SCREEN)
		{
			app->player->lifes = 3;
			app->player->isDead = false;
			app->player->position.x = 600;
			app->player->position.y = 2816;
			app->player->vy = 0;
			app->player->jumps = 0;
			app->render->camera.x = app->player->position.x;
			app->render->camera.y = app->player->position.y;
			app->player->lvl1 = true;
			//gameplayState = PLAYING;
			playing = true;
		}

	}
	if (app->player->lvl1 == true)
	{
		
	}
	
	app->map->LoadColliders();

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d", app->map->data.width, app->map->data.height, app->map->data.tileWidth, app->map->data.tileHeight, app->map->data.tilesets.count());

	//app->win->SetTitle(title.GetString());

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
		//app->player->Init();
		app->map->Init();
		gameplayState = PLAYING;
		currentLevel.create("level1.tmx");
		app->map->Load("level1.tmx");
		app->tex->UnLoad(bgTexture);
		//PLAYER
		app->player->position.x = app->player->spawnLevel1.x;
		app->player->position.y = app->player->spawnLevel1.y;
		app->player->vy = 0;
		app->player->jumps = 0;
		app->player->lvl1 = true;
		playing = true;
		//app->player->Reload();
		break;
	case TITLE_SCREEN:
		//screenDisplayAnim = &titleScreenAnim;
		gameplayState = TITLE_SCREEN;
		app->player->Disable();
		app->map->Disable();
		app->render->camera.x = 0;
		app->render->camera.y = 0;
		playing = false;
		break;
	case GAME_OVER_SCREEN:
		//screenDisplayAnim = &gameOverAnim;
		gameplayState = GAME_OVER_SCREEN;
		app->render->camera.x = 0;
		app->render->camera.y = 0;
		playing = false;
		break;
	}


}

bool Scene::Load(pugi::xml_node& savedGame)
{
	app->map->CleanUpLoad();
	app->player->Reload();
	FadeToNewState(PLAYING);
	LoadLevel(savedGame.attribute("currentLevel").as_string("level1.tmx"));

	return true;
}

bool Scene::Save(pugi::xml_node& savedGame)
{

	pugi::xml_attribute lvl = savedGame.append_attribute("currentLevel");
	lvl.set_value(currentLevel.GetString());

	return true;
}

void Scene::LoadLevel(SString name)
{

	//app->player->unlockedChekpoint1 = false;
	//app->player->unlockedChekpoint2 = false;
	app->player->isDead = false;
	currentLevel = name;
	app->map->Load(name.GetString());
	app->player->Reload();


}
