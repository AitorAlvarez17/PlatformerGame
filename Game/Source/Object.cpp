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


Object::Object(/*int x, int y,*/bool startEnabled) : Module(startEnabled)
{
	int pixels = 24;

	position.x = 700;
	position.y = 2825;

	coll = { position.x, position.y, pixels ,pixels };
	

}

bool Object::Awake(pugi::xml_node& config)
{
	texturePath = config.child("texture").child_value();

	return true;
}

bool Object::Start()
{
	bool ret = true;
	int pixels = 24;



	LOG("Loading Coin textures");

	texture = app->tex->Load("Assets/textures/coinAnim.png");

	if (texture == nullptr)
		LOG("Couldn't load player texture");


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


bool Object::PreUpdate()
{
	if (active == false)
	{
		SetToDelete();
	}
	return true;
}

bool Object::Update(float dt)
{
	currentAnim->Update();
	return true;
}

bool Object::PostUpdate()
{
	
	return true;
}

void Object::Draw()
{
	rect = currentAnim->GetCurrentFrame();

	if (active == true)
	{
		app->render->DrawTexture(texture, position.x, position.y, &rect);
	}

}



void Object::OnCollision(Collider* a, Collider* b) {


	if (a->type == Collider::COIN && b->type == Collider::PLAYER)
	{
		active = false;
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


