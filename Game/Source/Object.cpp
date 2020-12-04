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
	if (type == ObjType::COIN) {
		objText = app->tex->Load("Assets/textures/coinAnim.png");

		collider = app->collisions->AddCollider(coll, Collider::Type::COIN, this);

		objMov.loop = true;
		objMov.speed = 0.4f;


		objMov.PushBack({ 0,0,24,24 });
		objMov.PushBack({ 24,0,24,24 });
		objMov.PushBack({ 48,0,24,24 });
		objMov.PushBack({ 72,0,24,24 });
		objMov.PushBack({ 96,0,24,24 });
		objMov.PushBack({ 120,0,24,24 });


	}

	if (type == ObjType::HEART)
	{
		objText = app->tex->Load("Assets/textures/heartAnim.png");

		collider = app->collisions->AddCollider(coll, Collider::Type::HEART, this);

		if (objText == nullptr || objText == nullptr)
			LOG("Couldn't load player texture");

		objMov.loop = true;
		objMov.speed = 0.4f;

		objMov.PushBack({ 0,0,24,24 });
		objMov.PushBack({ 24,0,24,24 });
		objMov.PushBack({ 48,0,24,24 });
		objMov.PushBack({ 72,0,24,24 });
		objMov.PushBack({ 96,0,24,24 });
		objMov.PushBack({ 120,0,24,24 });
	}

	if (currAnim == nullptr)
	{
		currAnim = &objMov;
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
	currAnim->Update();
	return true;
}

bool Object::PostUpdate()
{
	
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


