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

	tp1IDLE = app->tex->Load("Assets/maps/TP1/tp1_to0");
	tp1To2 = app->tex->Load("Assets/maps/TP1/tp1_to2");
	tp1To3 = app->tex->Load("Assets/maps/TP1/tp1_to3");

	tp2IDLE = app->tex->Load("Assets/maps/TP2/tp2_to_0");
	tp2To1 = app->tex->Load("Assets/maps/TP2/tp2_to_1");
	tp2To3 = app->tex->Load("Assets/maps/TP2/tp2_to3");

	tp3IDLE = app->tex->Load("Assets/maps/TP3/tp3_to_0");
	tp3To1 = app->tex->Load("Assets/maps/TP3/tp3_to_1");
	tp3To2 = app->tex->Load("Assets/maps/TP3/tp3_to2");

	coll = { position.x, position.y, pixels ,pixels*10 };
	tpColl = { tp1.x, tp1.y, pixels ,pixels };
	tpColl2 = { tp2.x, tp2.y, pixels ,pixels };
	tpColl3 = { tp3.x, tp3.y, pixels ,pixels };

	collider = app->collisions->AddCollider(coll, Collider::Type::SAVEPOINT, this);
	collidertp1 = app->collisions->AddCollider(tpColl, Collider::Type::TP, this);
	collidertp2 = app->collisions->AddCollider(tpColl2, Collider::Type::TP, this);
	collidertp3 = app->collisions->AddCollider(tpColl3, Collider::Type::TP, this);

	texRect = { 0, 0, 640, 480};


	return ret;
}

bool CheckPoints::PreUpdate()
{

	return true;
}

bool CheckPoints::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
	{
		if (mapOpen == true)
		{
			mapOpen = false;
			LOG("%d", mapOpen);
		}
		else 
		{
			mapOpen = true;
			LOG("%d", mapOpen);
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		tpCounter--;
		if (tpCounter == 0)
		{
			tpCounter = 2;
		}
		LOG("%d", tpCounter);
	}
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		tpCounter++;
		if (tpCounter == 3)
		{
			tpCounter = 1;
		}
		LOG("%d", tpCounter);
	}
	
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
		if (a->rect.x == tp1.x && mapOpen == true)
		{
			switch (tpCounter)
			{
				case 1:
					app->render->DrawTexture(tp1To2, 640, 480, &texRect);
					break;
				case 2:
					app->render->DrawTexture(tp1To3, 640, 480, &texRect);
					break;
			}

		}
		if (a->rect.x == tp2.x && mapOpen == true)
		{
			switch (tpCounter)
			{
			case 1:


				break;
			case 2:


				break;
			}

		}
		if (a->rect.x == tp3.x && mapOpen == true)
		{
			switch (tpCounter)
			{
			case 1:


				break;
			case 2:


				break;
			}

		}
		//app->player->position.x = tp1.x;
		//app->player->position.y = tp1.y;
			
		
		
			
		//app->player->position.x = tp2.x;
		//app->player->position.y = tp2.y;
			
		
		
		//app->player->position.x = tp3.x;
		//app->player->position.y = tp3.y;
		
		
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


