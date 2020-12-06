#include "CheckPoints.h"
#include "Debug.h"
#include "Map.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Window.h"
#include "Render.h"
#include "Player.h"
#include "Log.h"
#include "Scene.h"
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

	endLevel.x = 384;
	endLevel.y = 1374;
	LOG("Loading Coin textures");

	tp1IDLE = app->tex->Load("Assets/maps/TP1/tp1_to0.png");
	tp1To2 = app->tex->Load("Assets/maps/TP1/tp1_to2.png");
	tp1To3 = app->tex->Load("Assets/maps/TP1/tp1_to3.png");

	tp2IDLE = app->tex->Load("Assets/maps/TP2/tp2_to0.png");
	tp2To1 = app->tex->Load("Assets/maps/TP2/tp2_to1.png");
	tp2To3 = app->tex->Load("Assets/maps/TP2/tp2_to3.png");

	tp3IDLE = app->tex->Load("Assets/maps/TP3/tp3_to_0.png");
	tp3To1 = app->tex->Load("Assets/maps/TP3/tp3_to_1.png");
	tp3To2 = app->tex->Load("Assets/maps/TP3/tp3_to_2.png");

	OpenPhrase = app->tex->Load("Assets/maps/DialogueArt/OpenMenu.png");
	TeleportPhrase = app->tex->Load("Assets/maps/DialogueArt/TeleportMenu.png");

	coll = { position.x, position.y, pixels ,pixels*10 };
	tpColl = { tp1.x, tp1.y, pixels ,pixels };
	tpColl2 = { tp2.x, tp2.y, pixels ,pixels };
	tpColl3 = { tp3.x, tp3.y, pixels ,pixels };
	tpEndLevel = { endLevel.x, endLevel.y - 170, pixels ,pixels*10 };

	collider = app->collisions->AddCollider(coll, Collider::Type::SAVEPOINT, this);
	collidertp1 = app->collisions->AddCollider(tpColl, Collider::Type::TP, this);
	collidertp2 = app->collisions->AddCollider(tpColl2, Collider::Type::TP, this);
	collidertp3 = app->collisions->AddCollider(tpColl3, Collider::Type::TP, this);
	colliderEndLevel = app->collisions->AddCollider(tpEndLevel, Collider::Type::ENDLEVEL, this);

	texRect = { 0, 0, 640, 480};

	
	return ret;
}

bool CheckPoints::PreUpdate()
{
	onColl = false;
	return true;
}

bool CheckPoints::Update(float dt)
{
	if (app->player->lvl2 == true && createLevel2 == false)
	{
		tp1.x = 3169;
		tp1.y = 510;

		tp2.x = 547;
		tp2.y = 1664;

		tp3.x = 1735;
		tp3.y = 2431;
		createLevel2 = true;
		InitLevel2();
	}
	CheckOut();
	if (app->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		
	}
	/*if (onArea1 == false || onArea2 == false || onArea3 == false)
	{
		renderedOption = NULL;
	}*/
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		tpCounter--;
		if (tpCounter == 0)
		{
			tpCounter = 2;
		}
		//LOG("%d", tpCounter);
	}
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		tpCounter++;
		if (tpCounter == 3)
		{
			tpCounter = 1;
		}
		//LOG("%d", tpCounter);
	}
	
	return true;
}

bool CheckPoints::PostUpdate()
{
	if (onColl == true)
	{
		if (onArea1 || onArea2 || onArea3)
		{
			app->render->DrawTexture(OpenPhrase, app->player->position.x-42, (app->player->position.y) - 35);
			if (mapOpen)
			{
				int camaraPosx = -(app->render->camera.x) / 2;
				int camaraPosy = (-(app->render->camera.y) / 2);
				app->render->DrawTexture(renderedOption, camaraPosx, camaraPosy - 58);
				app->render->DrawTexture(TeleportPhrase, camaraPosx + ((app->render->camera.w)/5), camaraPosy);
			
			}
		}
	}
	
	
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

void CheckPoints::CheckOut()
{
	if (app->player->coll.x != tp1.x)
	{
		//LOG("out");
	}
	else if (app->player->coll.x == tp1.x)
	{
		//LOG("in");
	}

}

void CheckPoints::OnCollision(Collider* a, Collider* b) {

	if (a->rect.x == tp1.x)
	{
		onArea1 = true;
		outArea = false;
	}
	else
	{
		onArea1 = false;
	}
	if (a->rect.x == tp2.x)
	{
		onArea2 = true;
		outArea = false;
	}
	else
	{
		onArea2 = false;
	}
	if (a->rect.x == tp3.x)
	{
		onArea3 = true;
		outArea = false;
	}
	else
	{
		onArea3 = false;
	}

	if (a->type == Collider::SAVEPOINT && b->type == Collider::PLAYER)
	{
		active = false;
	}
	if (a->type == Collider::TP && b->type == Collider::PLAYER)
	{
		onColl = true;
		app->render->DrawTexture(OpenPhrase, app->player->position.x - 42, (app->player->position.y) - 35);
		if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
		{
			if (mapOpen == true)
			{
				LOG("%d", mapOpen);
				mapOpen = false;
				
			}
			else
			{
				LOG("%d", mapOpen);
				mapOpen = true;
				
			}
		}
		if (onArea1 && mapOpen == true)
		{
			switch (tpCounter)
			{
				case 1:
					renderedOption = tp1To2;
					if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
					{
						app->player->position.x = tp2.x;
						app->player->position.y = tp2.y;

						mapOpen = false;
					}
					break;
				case 2:
					renderedOption = tp1To3;
					if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
					{
						app->player->position.x = tp3.x;
						app->player->position.y = tp3.y;

						mapOpen = false;
					}
					break;
			}

		}
		if (onArea2 && mapOpen == true)
		{
			switch (tpCounter)
			{
			case 1:
				renderedOption = tp2To1;
				if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					app->player->position.x = tp1.x;
					app->player->position.y = tp1.y;

					mapOpen = false;
				}

				break;
			case 2:
				renderedOption = tp2To3;
				if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					app->player->position.x = tp3.x;
					app->player->position.y = tp3.y;

					mapOpen = false;
				}
				break;
			}

		}
		if (onArea3 && mapOpen == true)
		{
			switch (tpCounter)
			{
			case 1:
				renderedOption = tp3To1;
				if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					app->player->position.x = tp1.x;
					app->player->position.y = tp1.y;

					mapOpen = false;
				}
				break;
			case 2:
				renderedOption = tp3To2;
				if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					app->player->position.x = tp2.x;
					app->player->position.y = tp2.y;

					mapOpen = false;
				}
				break;
			}

		}
		
		
	}
	



}

void CheckPoints::InitLevel2()
{
	int pixels = 32;
	tp1To2 = app->tex->Load("Assets/maps/TP1/LVL2/1to2.png");
	tp1To3 = app->tex->Load("Assets/maps/TP1/LVL2/1to3.png");

	tp2To1 = app->tex->Load("Assets/maps/TP2/LVL2/2to1.png");
	tp2To3 = app->tex->Load("Assets/maps/TP2/LVL2/2to3.png");

	tp3To1 = app->tex->Load("Assets/maps/TP3/LVL2/3to1.png");
	tp3To2 = app->tex->Load("Assets/maps/TP3/LVL2/3to2.png");

	LOG("helo");
	
	coll = { position.x, position.y - 250, pixels ,pixels * 10 };
	tpColl = { tp1.x, tp1.y, pixels ,pixels };
	tpColl2 = { tp2.x, tp2.y, pixels ,pixels };
	tpColl3 = { tp3.x, tp3.y, pixels ,pixels };
	tpEndLevel = { endLevel.x, endLevel.y - 170, pixels ,pixels * 10 };

	collider = app->collisions->AddCollider(coll, Collider::Type::SAVEPOINT, this);
	collidertp1 = app->collisions->AddCollider(tpColl, Collider::Type::TP, this);
	collidertp2 = app->collisions->AddCollider(tpColl2, Collider::Type::TP, this);
	collidertp3 = app->collisions->AddCollider(tpColl3, Collider::Type::TP, this);


}

bool CheckPoints::Save(pugi::xml_node& savedGame)
{




	return true;
}

bool CheckPoints::Load(pugi::xml_node& savedPlayer)
{

	return true;
}


