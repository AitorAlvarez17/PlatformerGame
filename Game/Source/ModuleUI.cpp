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
	healthUi = app->tex->Load("Assets/UI/healthAnim.png");

	cooldown1 = app->tex->Load("Assets/UI/Cooldown1.png");
	cooldown2 = app->tex->Load("Assets/UI/Cooldown2.png");
	cooldown3 = app->tex->Load("Assets/UI/Cooldown3.png");
	healGUI = app->tex->Load("Assets/UI/HealGUI.png");
	pressH = app->tex->Load("Assets/UI/PressH.png");

	if (healthUi == nullptr)LOG("TEXTURE NOT FOUNDED");

	//Heart Gui Animations

	oneHeart.GenerateAnimation({ 0,0,0,32 }, 5);
	oneHeart.speed = 0.3f;
	oneHeart.loop = true;

	twoHearts.GenerateAnimation({ 0,32,0,32 },5);
	twoHearts.speed = 0.3f;
	twoHearts.loop = true;

	threeHearts.GenerateAnimation({ 0,64,32,32 }, 5);
	threeHearts.speed = 0.3f;
	threeHearts.loop = true;

	fourHearts.GenerateAnimation({ 0,96,32,32 }, 5);
	fourHearts.speed = 0.3f;
	fourHearts.loop = true;

	fiveHearts.GenerateAnimation({ 0,128,32,32 }, 5);
	fiveHearts.speed = 0.3f;
	fiveHearts.loop = true;

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
	int margin = 3;
	app->render->DrawTexture(healGUI, camaraPosx + margin + 5, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
	app->render->DrawTexture(pressH, camaraPosx + margin + 64, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
	if (app->player->cooldown < app->player->maxCooldown)
	{
		float cd = app->player->cooldown;
		if (cd < 1)
		{
			app->render->DrawTexture(cooldown3, camaraPosx + margin + 5, camaraPosy + ((app->render->camera.h)/2.5), 0, 0, 0, 0, 0, false);
		}
		else if (cd < 2 && cd > 1)
		{
			app->render->DrawTexture(cooldown2, camaraPosx + margin + 5, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
		}
		else if (cd < 3 && cd > 2)
		{
			app->render->DrawTexture(cooldown1, camaraPosx + margin + 5, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
		}
	}
	if (app->player->lifes <= 3)
	{
		int life = app->player->lifes;
		if (life == 1)
		{
			LOG("%d", life);
			app->render->DrawTexture(singleHeart, camaraPosx + margin + 90, camaraPosy + camaraPosy + 9, 0, 0, 0, 0, 0, false);
		}
		else if (life == 2)
		{
			LOG("%d", life);
			app->render->DrawTexture(singleHeart, camaraPosx + margin + 90, camaraPosy + camaraPosy + 9, 0, 0, 0, 0, 0, false);
			app->render->DrawTexture(singleHeart, camaraPosx + margin + 90+24, camaraPosy + camaraPosy + 9, 0, 0, 0, 0, 0, false);
		}
		else if (life == 3)
		{
			LOG("%d", life);
			app->render->DrawTexture(singleHeart, camaraPosx + margin + 90, camaraPosy + camaraPosy +9, 0, 0, 0, 0, 0, false);
			app->render->DrawTexture(singleHeart, camaraPosx + margin + 90 + 24, camaraPosy + camaraPosy + 9, 0, 0, 0, 0, 0, false);
			app->render->DrawTexture(singleHeart, camaraPosx + margin + 90 + 24 + 24, camaraPosy + camaraPosy + 9, 0, 0, 0, 0, 0, false);
		}
	}
	app->render->DrawTexture(healthTitle, camaraPosx + margin, camaraPosy + 3, 0, 0, 0, 0, 0, false);
	app->render->DrawTexture(scoreTitle, camaraPosx + ((app->win->GetWidth()) / 2.5), camaraPosy + 5, 0, 0, 0, 0, 0, false);

	//Draw Heart Gui
	//heartRect = currentHealthAnim->GetCurrentFrame();
	//app->render->DrawTexture(healthUi, 600, 2840, &heartRect);

	
}

void ModuleUI::HealthUi(int lifesLeft)
{
	switch (lifesLeft)
	{
	case (1):
	{
		currentHealthAnim = &oneHeart;
		return;
	}
	case (2):
	{
		currentHealthAnim = &twoHearts;
		return;
	}
	case (3):
	{
		currentHealthAnim = &threeHearts;
		return;
	}
	case(4):
	{
		currentHealthAnim = &fourHearts;
		return;
	}
	case (5):
	{
		currentHealthAnim = &fiveHearts;
		return;
	}
	
	}
	currentHealthAnim->Update();
	
}


