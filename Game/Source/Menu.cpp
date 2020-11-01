#include "Menu.h"

#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Player.h"
#include "Textures.h"
#include "Render.h"
//#include "Audio.h"
#include "Input.h"
#include "ModuleFadeToBlack.h"

Menu::Menu(bool startEnabled) : Module(startEnabled)
{

}

Menu::~Menu()
{

}

// Load assets
bool Menu::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = app->tex->Load("Assets/textures/Menu.png");

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	return ret;
}

bool Menu::Update()
{

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		app->fade->FadeToBlack(this, (Module*)app->render, 90);
	}

	return true;
}

// Update: draw background
bool Menu::PostUpdate()
{
	// Draw everything --------------------------------------
	app->render->DrawTexture(bgTexture, 0, 0, NULL);

	return true;
}

bool Menu::CleanUp()
{
	app->tex->UnLoad(bgTexture);
	return true;
}