#include "Enemy.h"
#include "Player.h"
#include "Debug.h"
#include "App.h"
#include "Input.h"
#include "Animation.h"
#include "Textures.h"
#include "PathFinding.h"
#include "Player.h"
#include "Map.h"

#include "Window.h"
#include "Render.h"
#include "Collisions.h"
#include "Audio.h"

#include "SDL/include/SDL_scancode.h"
#include "../Defs.h"
#include "../Log.h"
#include <math.h>


Enemy::Enemy(bool startEnabled) : Module(startEnabled)
{
	name.create("enemy");
}

bool Enemy::Awake(pugi::xml_node& config)
{
	LOG("Loading Enemy config");
	bool ret = true;

	texturePath = config.child("texture").child_value();


	pugi::xml_node move = config.child("move");


	health = move.attribute("health").as_float();
	speed = move.attribute("speed").as_float();
	

	return ret;
}

bool Enemy::Start()
{
	int pixels = 32;

	//Enemy Spawn Position
	position.x = 700;
	position.y = 2816;

	//Load Texture
	texture = app->tex->Load("Assets/textures/warriorcopia.png");
	if (texture == nullptr)LOG("Invalid enemy Texture");

	//Animations

	currentAnim = &rightAnim;

	rightAnim.GenerateAnimation({ 0,0,32,32 }, 5);
	rightAnim.loop = true;
	rightAnim.speed = rightAnim.speed = 0.1f;

	leftAnim.GenerateAnimation({ 0,32,32,32 }, 5);
	leftAnim.loop = true;
	leftAnim.speed = rightAnim.speed = 0.1f;

	deadRightAnim.GenerateAnimation({ 96,128,32,32 }, 3);
	deadRightAnim.loop = true;
	deadRightAnim.speed = rightAnim.speed = 0.1f;

	deadLeftAnim.GenerateAnimation({ 0,128,32,32 }, 3);
	deadLeftAnim.loop = true;
	deadLeftAnim.speed = rightAnim.speed = 0.1f;

	stunRightAnim.GenerateAnimation({ 0,64,32,32 }, 5);
	stunRightAnim.loop = true;
	stunRightAnim.speed = rightAnim.speed = 0.1f;

	stunleftAnim.GenerateAnimation({ 0,96,32,32 }, 5);
	stunleftAnim.loop = true;
	stunleftAnim.speed = rightAnim.speed = 0.1f;


	//Colliders
	enemyCollider = app->collisions->AddCollider(SDL_Rect({ (int)position.x ,(int)position.y + pixels,pixels,pixels }), Collider::Type::ENEMY, this);
	leftWall = app->collisions->AddCollider(SDL_Rect({ (int)position.x - 50,(int)position.y + pixels,pixels,pixels }), Collider::Type::ENEMYWALL, this);
	rightWall = app->collisions->AddCollider(SDL_Rect({ (int)position.x + 120,(int)position.y + pixels,pixels,pixels }), Collider::Type::ENEMYWALL, this);


	return true;
}

bool Enemy::PreUpdate()
{


	return true;
}

bool Enemy::Update(float dt)
{
	//Proccess
	ChangeState();


	return true;
}

bool Enemy::PostUpdate()
{
	UpdateMovement();
	UpdateAnim();
	//Update Animation
	currentAnim->Update();

	//Draw 
	SDL_Rect rect = currentAnim->GetCurrentFrame();
	app->render->DrawTexturePlayer(texture, (int)position.x, (int)position.y, &rect);

	//Update Colliders Position
	enemyCollider->SetPos((int)position.x + 16, (int)position.y + 32);


	return true;
}

void Enemy::OnCollision(Collider* a, Collider* b) {


	if (app->debug->godMode == false)
	{
		if (a->type == Collider::ENEMY && b->type == Collider::ENEMYWALL)
		{

			int compX = a->rect.x - b->rect.x;


			if (compX > 0)
			{
				position.x += b->rect.x + b->rect.w - a->rect.x;
				speed = speed * -1;
			}
			else
			{
				position.x -= a->rect.x + a->rect.w - b->rect.x;
				speed = speed * -1;
			}

			enemyCollider->SetPos((int)b->rect.x - 1, (int)position.y);


		}

	}

}

void Enemy::UpdateMovement()
{
	if (isMoving)
	{

		switch (eState)
		{

		case (ENEMYIDLE):
		{
			return;
		}

		case (ENEMYWALKING):
		{
			position.x += speed;

			return;
		}

		case (ENEMYRUNNING):
		{
			//PATHFINDING
			return;
		}
		}

	}
}

void Enemy::UpdateAnim()
{
	switch (eState)
	{
	case (ENEMYIDLE):
	{
		currentAnim = &idleAnim;
		return;
	}
	case (ENEMYWALKING):
	{
		leftAnim.speed = rightAnim.speed = 0.3f;

		if (speed > 0)
		{
			currentAnim = &rightAnim;


		}
		else
		{
			currentAnim = &leftAnim;

		}
		return;
	}
	case (ENEMYRUNNING):
	{
		leftAnim.speed = rightAnim.speed = 1.0f;

		//PATHFINDING ANIM PART

		return;

	}
	case (ENEMYDYING):
	{

		if (speed > 0)
		{
			currentAnim = &stunRightAnim;


		}
		else
		{
			currentAnim = &stunleftAnim;

		}
	}


	}
}

void Enemy::ChangeState()
{
	if ((position.x - app->player->position.x) < 60.0f)
	{
		eState = EnemyState::ENEMYDYING;

	}
	else
	{
		eState = EnemyState::ENEMYWALKING;

	}
}

bool Enemy::Save(pugi::xml_node& savedGame)
{
	savedGame.append_attribute("x") = position.x;
	savedGame.append_attribute("y") = position.y;
	savedGame.append_attribute("health") = health;

	return true;
}

bool Enemy::Load(pugi::xml_node& savedPlayer)
{
	position.x = savedPlayer.attribute("x").as_float();
	position.y = savedPlayer.attribute("y").as_float();
	health = savedPlayer.attribute("health").as_float();
	

	return true;
}