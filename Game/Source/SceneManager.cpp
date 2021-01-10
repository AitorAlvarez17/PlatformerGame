#include "SceneManager.h"

#include "SceneLogo.h"
#include "SceneTitle.h"
#include "SceneGameplay.h"
#include "SceneEnding.h"
#include "ModuleUI.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Window.h"
#include "EntityManager.h"

#include "GuiButton.h"

#include "Defs.h"
#include "Log.h"
#include "SString.h"

#include "SDL/include/SDL.h"

#define FADEOUT_TRANSITION_SPEED	2.0f
#define FADEIN_TRANSITION_SPEED		2.0f


SceneManager::SceneManager(Input* input, Render* render, Textures* tex, AudioManager* manager, Window* window, EntityManager* entityManager, App* app, ModuleUI* ui, Collisions* coll, CheckPoints* check, Debug* debug) : Module()
{
	name.Create("scenemanager");

	onTransition = false;
	fadeOutCompleted = false;
	transitionAlpha = 0.0f;;

	this->input = input;
	this->render = render;
	this->tex = tex;
	this->aud = manager;
	this->win = window;
	this->app = app;
	this->entityManager = entityManager;
	this->ui = ui;
	this->collisions = coll;
	this->check = check;
	this->debug = debug;
}

// Destructor
SceneManager::~SceneManager()
{}

// Called before render is available
bool SceneManager::Awake()
{
	LOG("Loading Scene manager");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneManager::Start()
{
	exitDemand = false;
	current = new SceneLogo();
	current->Load(tex);
	next = nullptr;
	aud->PlayMusic(PATH("Assets/Audio/music/", "music.ogg"));
	return true;
}

// Called each loop iteration
bool SceneManager::PreUpdate()
{
	/*
	// L12b: Debug pathfing
	static iPoint origin;
	static bool originSelected = false;

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);

	if(app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(originSelected == true)
		{
			app->pathFinding->CreatePath(origin, p);
			originSelected = false;
		}
		else
		{
			origin = p;
			originSelected = true;
		}
	}
	*/
	if (!onTransition)
	{
		current->PreUpdate();
	}
	return true;
}

// Called each loop iteration
bool SceneManager::Update(float dt)
{
	if (!onTransition)
	{
		
		//if (input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) render->camera.y -= 1;
		//if (input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) render->camera.y += 1;
		//if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) render->camera.x -= 1;
		//if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) render->camera.x += 1;

		current->Update(input, dt);
	}
	else
	{
		if (!fadeOutCompleted)
		{
			transitionAlpha += (FADEOUT_TRANSITION_SPEED * dt);

			// NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
			// For that reason we compare against 1.01f, to avoid last frame loading stop
			if (transitionAlpha > 1.01f)
			{
				transitionAlpha = 1.0f;

				current->Unload();	// Unload current screen
				next->Load(tex);	// Load next screen

				RELEASE(current);	// Free current pointer
				current = next;		// Assign next pointer
				next = nullptr;

				// Activate fade out effect to next loaded screen
				fadeOutCompleted = true;
			}
		}
		else  // Transition fade out logic
		{
			transitionAlpha -= (FADEIN_TRANSITION_SPEED * dt);

			if (transitionAlpha < -0.01f)
			{
				transitionAlpha = 0.0f;
				fadeOutCompleted = false;
				onTransition = false;
			}
		}
	}

	// Draw current scene
	current->Draw(render);
	
	
	// Draw full screen rectangle in front of everything
	if (onTransition)
	{
		render->DrawRectangle({ 0, 0, 1280, 720 }, { 0, 0, 0, (unsigned char)(255.0f * transitionAlpha) });
	}

	// L12b: Debug pathfinding
	/*
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);
	p = app->map->MapToWorld(p.x, p.y);

	const DynArray<iPoint>* path = app->pathFinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		app->render->DrawTexture(debugTex, pos.x, pos.y);
	}
	*/

	if (current->transitionRequired)
	{
		onTransition = true;
		fadeOutCompleted = false;
		transitionAlpha = 0.0f;

		switch (current->nextScene)
		{
			case SceneType::LOGO: next = new SceneLogo(); break;
			case SceneType::TITLE: next = new SceneTitle(aud, win, app, input, entityManager); break;
			case SceneType::GAMEPLAY: next = new SceneGameplay(aud, win, entityManager, input, ui,collisions, app, check, debug); break;
			case SceneType::ENDING: next = new SceneEnding(); break;
			default: break;
		}

		current->transitionRequired = false;
	}

	
	//if (input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && exitDemand == true) return false;
	
	
	return true;
}

// Called each loop iteration
bool SceneManager::PostUpdate(float dt)
{
	bool ret = true;

	if (!onTransition)
	{
		current->PostUpdate(input, dt);
	}

	return ret;
}

// Called before quitting
bool SceneManager::CleanUp()
{
	LOG("Freeing scene");

	if (current != nullptr) current->Unload();

	return true;
}

bool SceneManager::LoadState(pugi::xml_node& data)
{
	LOG("Scenes loaded");
	int lvl = data.child("currentScene").attribute("sceneNumber").as_int();
	Scene* scene = current;
	
	if (lvl == 2)
	{
		
	}

	//Scene * scene;
	//scene->TransitionToScene();
	return true;
}

// L02: DONE 8: Create a method to save the state of the renderer
// Save Game State
bool SceneManager::SaveState(pugi::xml_node& data) const
{
	LOG("Scenes saved");
	pugi::xml_node currentScene = data.append_child("currentScene");
	
	if (current->name == "GAMEPLAY")
	{
		int level = 2;
		currentScene.append_attribute("sceneNumber") = level;
	}
	

	return true;
}