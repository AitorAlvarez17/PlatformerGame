#include "Hearts.h"
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


Hearts::Hearts(/*int x, int y,*/bool startEnabled) : Module(startEnabled)
{
	int pixels = 24;

	position.x = 750;
	position.y = 2825;

	coll = { position.x, position.y, pixels ,pixels };


}

bool Hearts::Awake(pugi::xml_node& config)
{
	texturePath = config.child("texture").child_value();

	return true;
}

bool Hearts::Start()
{
	bool ret = true;
	int pixels = 24;



	LOG("Loading Coin textures");

	texture = app->tex->Load("Assets/textures/heartAnim.png");

	if (texture == nullptr)
		LOG("Couldn't load player texture");


	collider = app->collisions->AddCollider(coll, Collider::Type::COIN, this);

	heartMovement.loop = true;
	heartMovement.speed = 0.4f;


	heartMovement.PushBack({ 0,0,24,24 });
	heartMovement.PushBack({ 24,0,24,24 });
	heartMovement.PushBack({ 48,0,24,24 });
	heartMovement.PushBack({ 72,0,24,24 });
	heartMovement.PushBack({ 96,0,24,24 });
	heartMovement.PushBack({ 120,0,24,24 });


	if (currentAnim == nullptr)
	{
		currentAnim = &heartMovement;
	}


	return ret;
}


bool Hearts::PreUpdate()
{
	if (active == false)
	{
		SetToDelete();
	}
	return true;
}

bool Hearts::Update(float dt)
{
	currentAnim->Update();
	return true;
}

bool Hearts::PostUpdate()
{
	rect = currentAnim->GetCurrentFrame();

	if (active == true)
	{
		app->render->DrawTexture(texture, position.x, position.y, &rect);
	}
	return true;
}



void Hearts::OnCollision(Collider* a, Collider* b) {


	if (a->type == Collider::COIN && b->type == Collider::PLAYER)
	{
		active = false;
	}



}

void Hearts::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool Hearts::Save(pugi::xml_node& savedGame)
{




	return true;
}

bool Hearts::Load(pugi::xml_node& savedPlayer)
{

	return true;
}


