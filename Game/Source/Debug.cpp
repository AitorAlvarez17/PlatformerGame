#include "Debug.h"
#include "App.h"
#include "Input.h"

#include "Defs.h"
#include "Log.h"
#include "Collisions.h"

#include "SDL/include/SDL.h"


Debug::Debug(Input* input, Collisions* coll, App* app) : Module()
{
	name.Create("debug");

	this->input = input;
	this->app = app;
	collisions = coll;
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

	if (input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) collisions->DebugRequest();


	return true;
}

