#include "App.h"
#include "Debug.h"

#include "Input.h"
#include "Collisions.h"

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

bool Debug::Update()
{
	bool ret = true;
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_F1) == KEY_REPEAT)
	{


	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_F2) == KEY_REPEAT)
	{


	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_F3) == KEY_REPEAT)
	{


	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_F5) == KEY_REPEAT)
	{


	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_F6) == KEY_REPEAT)
	{


	}
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		app->collisions->DebugRequest();
		LOG("Debug Mode");
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_F10) == KEY_REPEAT)
	{


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
