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
	LOG("Debug Start");
	return ret;
}

bool Debug::PreUpdate()
{
	bool ret = true;
	return ret;
}

bool Debug::Update(float dt)
{
	
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
	{ 
		app->RequestSave();
		LOG("SAVE REQUESTED");

	}
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
	{
		if (app->player->lvl2 == true)
		{

		}
		else
		{
			app->RequestLoad();
		}
		LOG("LOAD REQUESTED");
		

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

	if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		if (capFrameRate)
		{
			storeFrameRateCap = app->cappedMs;
			app->cappedMs = 1000.0f / 30.0f;
			capFrameRate = false;
		}
		else
		{
			app->cappedMs = storeFrameRateCap;
			capFrameRate = true;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		app->render->camera.x += 100;
	}
	if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
	{
		app->player->position.x = 443;
		app->player->position.y = 1333;
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
