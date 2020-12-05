#include "Debug.h"
#include "ModuleUI.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Window.h"
#include "Render.h"
#include "Player.h"
#include "Scene.h"
#include "Log.h"
#include "Animation.h"
#include "Collisions.h"
#include "SDL/include/SDL_scancode.h"
#include "Audio.h"
#include "../Defs.h"
#include "../Log.h"
#include <math.h>



ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
{
	name.create("moduleui");
}

bool ModuleUI::Awake(pugi::xml_node& config)
{
	//texturePath = config.child("texture").child_value();

	return true;
}

bool ModuleUI::Start()
{
	bool ret = true;
	int pixels = 24;
	
	camaraPosx = -(app->render->camera.x) / 2;
	camaraPosy = -(app->render->camera.y) / 2;
	LOG("Loading Coin textures");

	
	scoreTitle = app->tex->Load("Assets/UI/GoldText.png");
	healthTitle = app->tex->Load("Assets/UI/HealthText.png");

	
	//texRect = { 0, 0, 640, 480};

	
	return ret;
}

bool ModuleUI::PreUpdate()
{
	
	
	return true;
}

bool ModuleUI::Update(float dt)
{
	
	write = true;
	return true;
	
}

bool ModuleUI::PostUpdate()
{
	
	/*app->render->DrawTexture(healthTitle, camaraPosx + 3, camaraPosy + 3);
	app->render->DrawTexture(scoreTitle, camaraPosx + ((app->render->camera.w) / 2.5), camaraPosy + 5);*/
	if (app->scene->playing == true)
	{
		Draw();
	}

	return true;
}

void ModuleUI::Draw()
{



	app->render->DrawTexture(healthTitle, camaraPosx + 3, camaraPosy + 3, 0, 0, 0, 0, 0, false);
	app->render->DrawTexture(scoreTitle, camaraPosx + ((app->win->GetWidth()) / 2.5), camaraPosy + 5, 0, 0, 0, 0, 0, false);
}


