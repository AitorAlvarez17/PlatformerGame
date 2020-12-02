#include "CheckPoints.h"
#include "Debug.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Window.h"
#include "Render.h"
#include "Player.h"
#include "Log.h"
#include "Animation.h"
#include "Collisions.h"
#include "SDL/include/SDL_scancode.h"
#include "Audio.h"
#include "../Defs.h"
#include "../Log.h"
#include <math.h>



CheckPoints::CheckPoints(bool startEnabled) : Module(startEnabled)
{
	name.create("checkpoints");
}

bool CheckPoints::Awake(pugi::xml_node& config)
{
	//texturePath = config.child("texture").child_value();

	return true;
}

bool CheckPoints::Start()
{
	bool ret = true;
	int pixels = 24;


	position.x = 2040;
	position.y = 2654-200;

	tp1.x = 480;
	tp1.y = 2846;

	tp2.x = 3582;
	tp2.y = 2366;

	tp3.x = 2502;
	tp3.y = 2046;

	LOG("Loading Coin textures");


	coll = { position.x, position.y, pixels ,pixels*10 };
	tpColl = { tp1.x, tp1.y, pixels ,pixels };
	tpColl2 = { tp2.x, tp2.y, pixels ,pixels };
	tpColl3 = { tp3.x, tp3.y, pixels ,pixels };

	collider = app->collisions->AddCollider(coll, Collider::Type::SAVEPOINT, this);
	collidertp1 = app->collisions->AddCollider(tpColl, Collider::Type::TP, this);
	collidertp2 = app->collisions->AddCollider(tpColl2, Collider::Type::TP, this);
	collidertp3 = app->collisions->AddCollider(tpColl3, Collider::Type::TP, this);


	return ret;
}

bool CheckPoints::PreUpdate()
{

	return true;
}

bool CheckPoints::Update(float dt)
{
	/*if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		if (tpcounter == 1)
		{
			app->player->position.x = tp1.x;
			app->player->position.y = tp1.y;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		if (tpcounter == 2)
		{
			app->player->position.x = tp2.x;
			app->player->position.y = tp2.y;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		if (tpcounter == 3)
		{
			app->player->position.x = tp3.x;
			app->player->position.y = tp3.y;
		}
	}*/
	return true;
}

bool CheckPoints::PostUpdate()
{

	if (active == true)
	{
		
	}
	if (active == false)
	{
		app->RequestSave();
		active = true;
		collider->pendingToDelete = true;
	}


	return true;
}



void CheckPoints::OnCollision(Collider* a, Collider* b) {


	if (a->type == Collider::SAVEPOINT && b->type == Collider::PLAYER)
	{
		active = false;
	}
	if (a->type == Collider::TP && b->type == Collider::PLAYER)
	{
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			app->player->position.x = tp2.x;
			app->player->position.y = tp2.y;
		}
	}
	



}

bool CheckPoints::Save(pugi::xml_node& savedGame)
{




	return true;
}

bool CheckPoints::Load(pugi::xml_node& savedPlayer)
{

	return true;
}


