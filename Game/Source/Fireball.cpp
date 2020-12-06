#include "Fireball.h"
#include "Player.h"
#include "Debug.h"
#include "App.h"
#include "Input.h"
#include "Animation.h"
#include "Textures.h"
#include "PathFinding.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"

#include "Window.h"
#include "Render.h"
#include "Collisions.h"
#include "Audio.h"

#include "SDL/include/SDL_scancode.h"
#include "../Defs.h"
#include "../Log.h"
#include <math.h>

Fireball::Fireball(bool startEnabled) : Module(startEnabled)
{
	name.create("fireball");
}

bool Fireball::Awake(pugi::xml_node& config)
{
	LOG("Loading Fireball config");
	bool ret = true;

	texturePath = config.child("texture").child_value();


	pugi::xml_node move = config.child("move");


	//health = move.attribute("health").as_float();
	//speed = move.attribute("speed").as_float();

	//StunTime
	//Cooldown
	//Cuantinty
	//Speed
	//Range


	return ret;
}

bool Fireball::Start()
{
	int pixels = 32;
	//Spawns at player position
	position.x = app->player->position.x - 200;
	position.y = app->player->position.y;

	//Load Textures
	texture = app->tex->Load("Assets/textures/fireball2.png");
	if (texture == nullptr)LOG("Invalid Fireball Texture");

	//Animations

	rightFireball.GenerateAnimation({ 0,0,32,32 }, 5);
	rightFireball.loop = true;
	rightFireball.speed = 0.7f;

	leftFireball.GenerateAnimation({ 0,0,32,32 }, 5);
	leftFireball.loop = true;
	leftFireball.speed = 0.5f;

	//Colliders
	fireballCollider = app->collisions->AddCollider(SDL_Rect({ (int)position.x ,(int)position.y + pixels,pixels,pixels }), Collider::Type::FIREBALL, this);

	return true;
}

bool Fireball::PreUpdate()
{
	return true;
}

bool Fireball::Update(float dt)
{
	if (app->player->isGoingRight)
	{
		position.x += speed;

	}
	else
	{
		position.x -= speed;

	}
	return true;
}

bool Fireball::PostUpdate()
{
	currentAnim = &leftFireball;
	currentAnim->Update();
	//Draw 
	SDL_Rect fireballRect = currentAnim->GetCurrentFrame();
	app->render->DrawTexture(texture, (int)position.x, (int)position.y, &fireballRect);

	//Update Colliders Position
	fireballCollider->SetPos((int)position.x + 16, (int)position.y + 32);
	return true;
}

void Fireball::OnCollision(Collider* a, Collider* b)
{
	if (a->type == Collider::FIREBALL && b->type == Collider::ENEMY)
		{

		int compX = a->rect.x - b->rect.x;


		if (compX > 0)
		{
			app->enemy->isDead = true;
			//DESTROY BALL
			LOG("ISDEAD TRUE");
		}

		}
	
}


void Fireball::UpdateAnim()
{
}

void Fireball::ChangeState()
{
}

bool Fireball::Load(pugi::xml_node&)
{
	return true;
}

bool Fireball::Save(pugi::xml_node&)
{
	return true;
}
