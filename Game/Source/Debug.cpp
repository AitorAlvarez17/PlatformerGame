#include "App.h"
#include "Debug.h"
#include "Input.h"
#include "Collisions.h"
#include "Player.h"
#include "Render.h"
#include "Log.h"
#include "SDL/include/SDL_scancode.h"

Debug::Debug(bool startEnabled) : Module(startEnabled)
{
}

Debug::~Debug()
{
}

bool Debug::Start()
{
	bool ret = true;
	LOG("TONTO");
	return ret;
}

bool Debug::PreUpdate()
{
	bool ret = true;
	return ret;
}

bool Debug::Update(float dt)
{
	LOG("A");
	bool ret = true;
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		app->player->position.x = 600;
		app->player->position.y = 2816;
		app->player->vy = 0;
		app->player->jumps = 0;
		app->render->camera.x = app->player->position.x;
		app->render->camera.y = app->player->position.y;

	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{


	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{


	}

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
	{


	}
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
	{


	}
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		app->collisions->DebugRequest();
	}
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if (godMode == true)
		{
			app->player->jumps = 0;
			godMode = false;
			
		}
		else
		{
			app->player->jumps = 0;
			godMode = true;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= 100;

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 100;

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 100;


	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		app->render->camera.x += 100;
		LOG("RIGHT");
	}



	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) {
		app->RequestLoad();
		LOG("LOAD REQUESTED");
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		app->RequestSave();
		LOG("SAVE REQUESTED");
	}

	
	return ret;
}

bool Debug::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool Debug::CleanUp()
{
	bool ret = true;
	return ret;
}

void Debug::Enable()
{
}
