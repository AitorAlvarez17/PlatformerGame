#include "Debug.h"
#include "App.h"
#include "Input.h"
#include "ModuleUI.h"
#include "Defs.h"
#include "Log.h"
#include "Collisions.h"
#include "EntityManager.h"

#include "SDL/include/SDL.h"


Debug::Debug(Input* input, Collisions* coll, App* app, ModuleUI* ui, EntityManager* entity) : Module()
{
	name.Create("debug");

	this->input = input;
	this->app = app;
	this->ui = ui;
	this->eManager = entity;
	collisions = coll;
	bufferPlayer = 0;
}

// Destructor
Debug::~Debug()
{}

// Called before render is available
bool Debug::Awake(pugi::xml_node& config)
{
	LOG("Loading Debug Module");
	bool ret = true;

	return ret;
}

bool Debug::Start()
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (eManager->entities[i] != nullptr)
		{
			eManager->entities[i]->type == EntityType::PLAYER;
			bufferPlayer = i;
		}
	}

	return true;
}
// Called before quitting
bool Debug::CleanUp()
{
	if (!active) return true;

	return true;
}

bool Debug::Update(float dt)
{

	if (input->GetKey(SDL_SCANCODE_F5) == KEY_REPEAT) app->SaveGameRequest();

	if (input->GetKey(SDL_SCANCODE_F6) == KEY_REPEAT) app->LoadGameRequest();

	if (input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) 
		collisions->DebugRequest();

	if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		
	}
	if (input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) ui->saveCoroutine = 0;
		
	
	return true;
}

