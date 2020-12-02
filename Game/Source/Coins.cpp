#include "Coins.h"
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


Coins::Coins(/*int x, int y,*/bool startEnabled) : Module(startEnabled)
{
	int pixels = 24;

	position.x = 700;
	position.y = 2825;

	coll = { position.x, position.y, pixels ,pixels };
	

}

bool Coins::Awake(pugi::xml_node& config)
{
	texturePath = config.child("texture").child_value();

	return true;
}

bool Coins::Start()
{
	bool ret = true;
	int pixels = 24;



	collider = app->collisions->AddCollider(coll, Collider::Type::COIN, this);
	LOG("Loading Coin textures");

	texture = app->tex->Load("Assets/textures/coinAnim.png");

	if (texture == nullptr)
		LOG("Couldn't load player texture");

	coll = { position.x, position.y, pixels ,pixels };

	collider = app->collisions->AddCollider(coll, Collider::Type::COIN, this);

	coinMovement.loop = true;
	coinMovement.speed = 0.4f;

	
	coinMovement.PushBack({ 0,0,24,24 });
	coinMovement.PushBack({ 24,0,24,24 });
	coinMovement.PushBack({ 48,0,24,24 });
	coinMovement.PushBack({ 72,0,24,24 });
	coinMovement.PushBack({ 96,0,24,24 });
	coinMovement.PushBack({ 120,0,24,24 });
	

	if (currentAnim == nullptr)
	{
		currentAnim = &coinMovement;
	}


	return ret;
}

bool Coins::PreUpdate()
{

	return true;
}

bool Coins::Update(float dt)
{
	currentAnim->Update();

	return true;
}

bool Coins::PostUpdate()
{
	SDL_Rect rect = currentAnim->GetCurrentFrame();
	
	if (active == true)
	{
		app->render->DrawTexture(texture, position.x, position.y, &rect);
	}
	if (active == false)
	{
		collider->pendingToDelete = true;
	}


	return true;
}



void Coins::OnCollision(Collider* a, Collider* b) {


	if (a->type == Collider::COIN && b->type == Collider::PLAYER)
	{
		active = false;
	}

	

}

bool Coins::Save(pugi::xml_node& savedGame)
{




	return true;
}

bool Coins::Load(pugi::xml_node& savedPlayer)
{
	
	return true;
}


