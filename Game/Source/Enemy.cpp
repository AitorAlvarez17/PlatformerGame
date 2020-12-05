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

	return true;
}

bool Enemy::Start()
{
	int pixels = 32;

	position.x = 700;
	position.y = 2816;

	//load texture
	texture = app->tex->Load("Assets/textures/Warrior.png");
	if (texture == nullptr)LOG("Invalid enemy Texture");

	leftAnim.loop = true;
	leftAnim.speed = rightAnim.speed = 0.5f;
	//SDL_Rect animRect = { 0,0,32,32 };

	idleAnim.PushBack(SDL_Rect({ 32, 0, 32, 32 }));

	leftAnim.PushBack({ 0,32,32,32 });
	leftAnim.PushBack({ 32,32,32,32 });
	leftAnim.PushBack({ 64,32,32,32 });
	leftAnim.PushBack({ 96,32,32,32 });
	leftAnim.PushBack({ 128,32,32,32 });
	leftAnim.PushBack({ 160,32,32,32 });

	rightAnim.PushBack({ 0,0,32,32 });
	rightAnim.PushBack({ 32,0,32,32 });
	rightAnim.PushBack({ 64,0,32,32 });
	rightAnim.PushBack({ 96,0,32,32 });
	rightAnim.PushBack({ 128,0,32,32 });
	rightAnim.PushBack({ 160,0,32,32 });

	//currentAnim = &leftAnim;

	//Colliders
	enemyCollider = app->collisions->AddCollider(SDL_Rect({ position.x,position.y,pixels,pixels }), Collider::Type::ENEMY, this);

	leftWall = app->collisions->AddCollider(SDL_Rect({ position.x - 100,position.y,pixels,pixels }), Collider::Type::ENEMYWALL, this);
	rightWall = app->collisions->AddCollider(SDL_Rect({ position.x + 100,position.y,pixels,pixels }), Collider::Type::ENEMYWALL, this);
	

	return true;
}


bool Enemy::PreUpdate()
{


	return true;
}

bool Enemy::Update(float dt)
{
	//if (!isMoving && ((position.x - app->player->position.x) < 30))
	//{
	//	isMoving = true;
	//}
	//
	if ((position.x - app->player->position.x) < 50) { isMoving = true; }
	if (isMoving)
	{
		if (isMovingRight) {
		
			position.x += speed;
			currentAnim = &rightAnim;

		}
		else
		{
			position.x -= speed;
			currentAnim = &leftAnim;

		}

		enemyCollider->SetPos(position.x, position.y);
	}
	else { currentAnim = &idleAnim; }

	currentAnim->Update();
	return true;
}

bool Enemy::PostUpdate()
{
	//SDL_Rect enemyRect = currentanim;
	//app->render->DrawTexture(texture, position.x, position.y, &enemyRect);
	SDL_Rect rect = currentAnim->GetCurrentFrame();
	app->render->DrawTexturePlayer(texture, position.x, position.y, &rect);



	return true;
}
void Enemy::OnCollision(Collider* a, Collider* b) {

	if (app->debug->godMode == false)
	{
		if (a->type == Collider::ENEMY && b->type == Collider::ENEMYWALL)
		{
			
			if (isMovingRight)
			{
				isMovingRight = false;
			}
			else
			{
				isMovingRight = true;
			}
		}
	}

}

//bool Enemy::Save(pugi::xml_node& savedGame)
//{
//
//	savedGame.append_attribute("x") = position.x;
//	savedGame.append_attribute("y") = position.y;
//
//
//
//	return true;
//}
//
//bool Enemy::Load(pugi::xml_node& savedPlayer)
//{
//	position.x = savedPlayer.attribute("x").as_int();
//	position.y = savedPlayer.attribute("y").as_int();
//	jumps = savedPlayer.attribute("jumpsRemaining").as_int();
//	vy = savedPlayer.attribute("verticalVelocity").as_int();
//
//	return true;
//}