#include "Enemy.h"
#include "Player.h"
#include "Debug.h"
#include "App.h"
#include "Input.h"
#include "Animation.h"
#include "Textures.h"
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
	LOG("Loading Enemy");
	bool ret = true;

	texturePath = config.child("texture").child_value();

	pugi::xml_node move = config.child("move");

	speed = move.attribute("speed").as_int();

	pugi::xml_node audio = config.child("audio");

	//jumpFxPath = audio.attribute("jump").as_string();

	return ret;
}

bool Enemy::Start()
{
	bool ret = true;
	int pixels = 32;


	position.x = 700;
	position.y = 2816;

	winWidth = app->win->GetWidth();
	winHeigh = app->win->GetHeight();


	LOG("Loading Enemy textures");

	texture = app->tex->Load("Assets/textures/FinnSprite.png");

	if (texture == nullptr)
		LOG("Couldn't load player texture");

	coll = { position.x, position.y, pixels - 4,pixels + 2 };

	//cambiar això
	collider = app->collisions->AddCollider(coll, Collider::Type::ENEMY, this);

	idleAnimR.loop = idleAnimL.loop = runRightAnim.loop = runLeftAnim.loop = true;
	idleAnimR.speed = idleAnimL.speed = 0.2f;
	runRightAnim.speed = runLeftAnim.speed = 0.3f;

	if (push == false)
	{
		for (int i = 0; i < 27; i++)// 0 to 9
		{
			if (i >= 0 && i < 9)//RIGHT ANIM IDLE
			{
				idleAnimR.PushBack({ i * pixels,0,32,32 });

			}
			if (i >= 0 && i < 9)//LEFT ANIM IDLE
			{
				idleAnimL.PushBack({ (27 - i) * pixels + 5,32,32,32 });

			}
			if (i >= 9 && i < 15)// RIGHT
			{
				runRightAnim.PushBack({ i * pixels,0,32,32 });

			}
			if (i >= 9 && i < 15)// LEFT
			{
				runLeftAnim.PushBack({ (27 - i) * pixels + 5,32,32,32 });

			}
			if (i == 15) // JUMP R & L
			{
				jumpRightAnim.PushBack({ i * pixels,0,32,32 });
				jumpLeftAnim.PushBack({ (27 - i) * pixels + 5,32,32,32 });

			}
			if (i >= 20 && i < 23) // DEAD RIGHT
			{
				deadAnimR.PushBack({ i * pixels,0,32,32 });

			}
			if (i >= 20 && i < 23) // DEAD RIGHT
			{
				deadAnimL.PushBack({ (27 - i) * pixels,32,32,32 });

			}
			push = true;

		}

	}

	//left
	if (currentAnim == nullptr)
	{
		currentAnim = &idleAnimR;
	}

	return ret;
}

bool Enemy::PreUpdate()
{
	if (app->debug->godMode == false)
	{
	//	position.y -= vy;
		//vy -= gravityForce * 0.5;
		//app->player->UpdateState();
	}

	return true;
}

bool Enemy::Update(float dt)
{
	if (app->debug->godMode == false)
	{

	}

	if (isMovingRight)
	{
		position.x += speed;
	}
	else
	{
		position.x -= speed;
	}

return true;
}

bool Enemy::PostUpdate()
{
	SDL_Rect rect = currentAnim->GetCurrentFrame();

	// Recordatorio para optimizar codigo - No eliminar(Telmo)
	if (isMovingRight == true)
	{
		if (currentAnim == &runLeftAnim) { currentAnim = &runRightAnim; }
		app->render->DrawTexturePlayer(texture, position.x - 12, position.y - 30, &rect);
	}
	else
	{
		if (currentAnim == &runRightAnim) { currentAnim = &runLeftAnim; }
		app->render->DrawTexturePlayer(texture, position.x - 24, position.y - 30, &rect);
	}


	return true;
}