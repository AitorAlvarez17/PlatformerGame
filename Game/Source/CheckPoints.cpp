#include "CheckPoints.h"
#include "Log.h"
#include <math.h>




CheckPoints::CheckPoints(Input* input, Render* render, Collisions* collisions, AudioManager* audio, App* app, EntityManager* eManager, ModuleUI* ui)
{
	name.Create("checkpoints");
	this->input = input;
	this->rend = render;
	this->col = collisions;
	this->aud = audio;
	this->app = app;
	this->eManager = eManager;
	this->ui = ui;
}

CheckPoints::~CheckPoints()
{}

bool CheckPoints::Awake(pugi::xml_node& config)
{
	return true;
}

bool CheckPoints::Start()
{
	bool ret = true;

	int pixels = 24;

	//Set Positions
	position.x = 579;
	position.y = 229;

	tp1.x = 216;
	tp1.y = 509;

	tp2.x = 870;
	tp2.y = 471;

	tp3.x = 302;
	tp3.y = 108;

	endLevel.x = 384;
	endLevel.y = 1374;

	//Load Textures
	//Set colliders
	coll = { position.x, position.y, pixels ,pixels * 10 };
	tpColl = { tp1.x, tp1.y, pixels ,pixels };//PUT COLLIDERS
	tpColl2 = { tp2.x, tp2.y, pixels ,pixels };//PUT COLLIDERS
	tpColl3 = { tp3.x, tp3.y, pixels ,pixels };//PUT COLLIDERS
	tpEndLevel = { endLevel.x, endLevel.y - 170, pixels ,pixels * 10 };

	collider = col->AddCollider(coll, Collider::Type::SAVEPOINT, this);
	collidertp1 = col->AddCollider(tpColl, Collider::Type::TP, this);
	collidertp2 = col->AddCollider(tpColl2, Collider::Type::TP, this);
	collidertp3 = col->AddCollider(tpColl3, Collider::Type::TP, this);
	//colliderEndLevel = col->AddCollider(tpEndLevel, Collider::Type::ENDLEVEL, this);

	texRect = { 0, 0, 640, 480 };

	return ret;
}

bool CheckPoints::PreUpdate()
{
	onColl = false;
	return true;
}

bool CheckPoints::Load(Textures* tex)
{

	tp1To2 = tex->Load("Assets/Textures/Maps/Tp/1_to_2.png");
	tp1To3 = tex->Load("Assets/Textures/Maps/Tp/1_to_3.png");

	tp2To1 = tex->Load("Assets/Textures/Maps/Tp/2_to_1.png");
	tp2To3 = tex->Load("Assets/Textures/Maps/Tp/2_to_3.png");

	tp3To1 = tex->Load("Assets/Textures/Maps/Tp/3_to_1.png");
	tp3To2 = tex->Load("Assets/Textures/Maps/Tp/3_to_2.png");

	openPhrase = tex->Load("Assets/Textures/Dialogue/open_menu.png");
	teleportPhrase = tex->Load("Assets/Textures/Dialogue/teleport_menu.png");

	return false;

}
bool CheckPoints::Update(float dt)
{
	CheckOut();
	if (input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{

	}
	if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		tpCounter--;
		aud->PlayFx(8, 0);
		if (tpCounter == 0)
		{
			tpCounter = 2;
		}

	}
	if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		tpCounter++;
		aud->PlayFx(8, 0);
		if (tpCounter == 3)
		{
			tpCounter = 1;
		}

	}

	return true;
}

bool CheckPoints::PostUpdate()
{
	if (onColl == true)
	{
		if (onArea1 || onArea2 || onArea3)
		{   
			//rend->DrawTexture(openPhrase, player->position.x - 42, (player->position.y) - 35);
			if (mapOpen)
			{
				int camaraPosx = -(rend->camera.x) / 2;
				int camaraPosy = (-(rend->camera.y) / 2);
				rend->DrawTexture(renderedOption, camaraPosx, camaraPosy - 58);
				rend->DrawTexture(teleportPhrase, camaraPosx + ((rend->camera.w) / 5), camaraPosy);

			}

		}

	}


	if (active == true)
	{

	}
	if (active == false)
	{
		app->SaveGameRequest();
		active = true;
		collider->pendingToDelete = true;
	}


	return true;
}

void CheckPoints::CheckOut()
{
	/*if (player->coll.x != tp1.x)
	{
		//LOG("out");
	}
	else if (player->coll.x == tp1.x)
	{
		//LOG("in");
	}*/

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
		ui->saveCoroutine = 0;
		if (ui->saveCoroutine < 3)
		{
			ui->Draw(rend);
		}
		app->audio->PlayFx(2, 0);
		active = false;
	}
	if (a->type == Collider::TP && b->type == Collider::PLAYER)
	{
		onColl = true;
		//rend->DrawTexture(openPhrase, player->position.x - 42, (player->position.y) - 35);
		if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
		{
			if (mapOpen == true)
			{
				aud->PlayFx(8, 0);
				LOG("%d", mapOpen);
				mapOpen = false;

			}
			else
			{
				aud->PlayFx(8, 0);
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
				if (input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					aud->PlayFx(8, 0);
					player->position.x = tp2.x;
					player->position.y = tp2.y;

					mapOpen = false;
				}
				break;
			case 2:
				renderedOption = tp1To3;
				if (input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					aud->PlayFx(8, 0);
					player->position.x = tp3.x;
					player->position.y = tp3.y;

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
				if (input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					aud->PlayFx(8, 0);
					player->position.x = tp1.x;
					player->position.y = tp1.y;

					mapOpen = false;
				}

				break;
			case 2:
				renderedOption = tp2To3;
				if (input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					aud->PlayFx(8, 0);
					player->position.x = tp3.x;
					player->position.y = tp3.y;

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
				if (input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					aud->PlayFx(8, 0);
					player->position.x = tp1.x;
					player->position.y = tp1.y;

					mapOpen = false;
				}
				break;
			case 2:
				renderedOption = tp3To2;
				if (input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
				{
					aud->PlayFx(8, 0);
					player->position.x = tp2.x;
					player->position.y = tp2.y;

					mapOpen = false;
				}
				break;
			}

		}

	}


}

bool CheckPoints::SaveState(pugi::xml_node& savedGame)
{
	return true;
}

bool CheckPoints::LoadState(pugi::xml_node& savedPlayer)
{
	return true;
}



