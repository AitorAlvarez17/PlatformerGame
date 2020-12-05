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
	singleHeart = app->tex->Load("Assets/UI/heart.png");
	healthUi = app->tex->Load("Assets/UI/heartAnim.png");

	if (healthUi == nullptr)LOG("TEXTURE NOT FOUNDED");

	twoHearts.GenerateAnimation({ 0,0,48,1 }, 1, 2);
	twoHearts.speed = 0.2f;
	twoHearts.loop = true;

	threeHearts.GenerateAnimation({ 0,0,72,24 }, 1, 3);
	threeHearts.speed = 0.2f;
	threeHearts.loop = true;

	fourHearts.GenerateAnimation({ 0,0,96,24 }, 1, 4);
	fourHearts.speed = 0.2f;
	fourHearts.loop = true;

	fiveHearts.GenerateAnimation({ 0,0,144,24 }, 1, 5);
	fiveHearts.speed = 0.2f;
	fiveHearts.loop = true;

	sixHearts.GenerateAnimation({ 0,0,168,24 }, 1, 6);
	sixHearts.speed = 0.2f;
	sixHearts.loop = true;
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
		HealthUi(app->player->lifes);
		Draw();
	}
	
	return true;
}

void ModuleUI::Draw()
{



	app->render->DrawTexture(healthTitle, camaraPosx + 3, camaraPosy + 3, 0, 0, 0, 0, 0, false);
	app->render->DrawTexture(scoreTitle, camaraPosx + ((app->win->GetWidth()) / 2.5), camaraPosy + 5, 0, 0, 0, 0, 0, false);

	currentHealthAnim->Update();
	SDL_Rect heartRect = currentHealthAnim->GetCurrentFrame();
	app->render->DrawTexture(healthUi, camaraPosx + 96, camaraPosy + 10, &heartRect);
	
}

void ModuleUI::HealthUi(int lifesLeft)
{
	switch (lifesLeft)
	{
	case (1):
	{
		currentHealthAnim = &twoHearts;
		return;
	}
	case (2):
	{
		currentHealthAnim = &threeHearts;
		return;
	}
	case (3):
	{
		currentHealthAnim = &fourHearts;
		return;
	}
	case(4):
	{
		currentHealthAnim = &fiveHearts;
		return;
	}
	case (5):
	{
		currentHealthAnim = &sixHearts;
		return;
	}
	
	}
	currentHealthAnim->Update();
	
}


