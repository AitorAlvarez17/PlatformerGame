#include "Object.h"
#include "Debug.h"
#include "App.h"
#include "Input.h"
#include "Animation.h"
#include "Textures.h"
#include "Window.h"
#include "Render.h"
#include "Collisions.h"
#include "SDL/include/SDL_scancode.h"
#include "Audio.h"
#include "../Defs.h"
#include "../Log.h"
#include <math.h>


Object::Object(int x, int y,ObjType ptype,bool startEnabled) : Module(startEnabled)
{
	int pixels = 24;

	position.x = x;
	position.y = y;
	type = ptype;
	coll = { position.x, position.y, pixels ,pixels };
	

}

Object::Object(int x, int y,int dir, ObjType ptype, bool startEnabled) : Module(startEnabled)
{
	int pixels = 32;

	position.x = x;
	position.y = y;
	direction = dir;
	type = ptype;

	coll = { position.x, position.y, pixels ,pixels };


}

bool Object::Awake(pugi::xml_node& config)
{
	texturePath = config.child("texture").child_value();
	pugi::xml_node move = config.child("move");


	return true;
}

bool Object::Start()
{
	bool ret = true;
	int pixels = 24;
	int pixelsFire = 32;


	LOG("Loading Coin textures");
	if (type == ObjType::COIN) {
		objText = app->tex->Load("Assets/textures/coin_anim.png");

		collider = app->collisions->AddCollider(coll, Collider::Type::COIN, this);

		objMov.loop = true;
		objMov.speed = 0.4f;

		if (objText == nullptr)
			LOG("Couldn't load coin texture");

		objMov.PushBack({ 0,0,24,24 });
		objMov.PushBack({ 24,0,24,24 });
		objMov.PushBack({ 48,0,24,24 });
		objMov.PushBack({ 72,0,24,24 });
		objMov.PushBack({ 96,0,24,24 });
		objMov.PushBack({ 120,0,24,24 });


	}

	if (type == ObjType::HEART)
	{
		objText = app->tex->Load("Assets/textures/heart_anim.png");

		collider = app->collisions->AddCollider(coll, Collider::Type::HEART, this);

		if (objText == nullptr )
			LOG("Couldn't load heart texture");

		objMov.loop = true;
		objMov.speed = 0.4f;

		objMov.PushBack({ 0,0,24,24 });
		objMov.PushBack({ 24,0,24,24 });
		objMov.PushBack({ 48,0,24,24 });
		objMov.PushBack({ 72,0,24,24 });
		objMov.PushBack({ 96,0,24,24 });
		objMov.PushBack({ 120,0,24,24 });
	}

	if (type == ObjType::FIREBALL)
	{
		objText = app->tex->Load("Assets/textures/fireball_sprite.png");

		speed = 1.0f;
		speed *= direction;

		coll.y += pixelsFire;

		collider = app->collisions->AddCollider(coll, Collider::Type::FIREBALL, this);

		if (objText == nullptr)
			LOG("Couldn't load heart texture");

		
		objMovR.GenerateAnimation({ 0,0,32,32 }, 5);
		objMovR.loop = true;
		objMovR.speed = 0.7f;

		objMovL.GenerateAnimation({ 0,0,32,32 }, 5);
		objMovL.loop = true;
		objMovL.speed = 0.5f;

	}

	if (currAnim == nullptr)
	{

		if(type == ObjType::FIREBALL)
		{

			if (direction == 1)
			{
				currAnim = &objMovR;
			}
			else if (direction == -1)
			{
				currAnim = &objMovL;
			}
			
		}
		else
		{
			currAnim = &objMov;
		}

	}
	return ret;
}


bool Object::PreUpdate()
{
	return true;
}

bool Object::Update(float dt)
{
	if (type == ObjType::FIREBALL)
	{
		position.x += speed;
	}
	currAnim->Update();
	return true;
}

bool Object::PostUpdate()
{
	if (type == ObjType::FIREBALL)
	{
		collider->SetPos((int)position.x + 16, (int)position.y + 32);
	}
	return true;
}

void Object::Draw()
{
	objRect = currAnim->GetCurrentFrame();

	if (active == true)
	{
		app->render->DrawTexture(objText, position.x, position.y, &objRect);
	}

}



void Object::OnCollision(Collider* a, Collider* b) {


	if (a->type == Collider::COIN && b->type == Collider::PLAYER)
	{
		SetToDelete();
	}
	if (a->type == Collider::PLAYER && b->type == Collider::COIN)
	{
		SetToDelete();
	}


	if (a->type == Collider::HEART && b->type == Collider::PLAYER)
	{
		SetToDelete();
	}
	if (a->type == Collider::PLAYER && b->type == Collider::HEART)
	{
		SetToDelete();
	}

	if (a->type == Collider::FIREBALL && b->type == Collider::ENEMY)
	{
		SetToDelete();
	}
	if (a->type == Collider::ENEMY && b->type == Collider::FIREBALL)
	{
		SetToDelete();
	}

}

void Object::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool Object::Save(pugi::xml_node& savedGame)
{




	return true;
}

bool Object::Load(pugi::xml_node& savedPlayer)
{
	
	return true;
}


