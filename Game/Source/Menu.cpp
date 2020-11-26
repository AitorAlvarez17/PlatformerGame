#include "Menu.h"
#include "Window.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Player.h"
#include "Textures.h"
#include "Render.h"
#include "ModuleFadeToBlack.h"
//#include "Audio.h"
#include "Input.h"
//#include "ModuleFadeToBlack.h"

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
	screenRect.y = app->win->GetHeight();
	screenRect.x = app->win->GetWidth();
	bool ret = true;

	bgTexture = app->tex->Load("Assets/maps/MenuF.png");
	

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	return ret;
}

bool Menu::Update(float dt)
{

	if (app->player->lvl1 == false)
	{
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			app->player->position.x = 600;
			app->player->position.y = 2816;
			app->player->vy = 0;
			app->player->jumps = 0;
			/*		app->render->camera.x = app->player->position.x;
					app->render->camera.y = app->player->position.y;*/
			app->player->lvl1 = true;
		}
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