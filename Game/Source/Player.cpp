#include "Player.h"
#include "Debug.h"
#include "Map.h"
#include "App.h"
#include "Input.h"
#include "Animation.h"
#include "Textures.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Window.h"
#include "Render.h"
#include "CheckPoints.h"
#include "Collisions.h"
#include "SDL/include/SDL_scancode.h"
#include "Audio.h"
#include "../Defs.h"
#include "../Log.h"
#include <math.h>


Player::Player(bool startEnabled) : Module(startEnabled)
{
	name.create("player");
}

bool Player::Awake(pugi::xml_node& config)
{
	LOG("Loading player config");
	bool ret = true;

	texturePath = config.child("texture").child_value();


	pugi::xml_node move = config.child("move");


	jumpForceValue = move.attribute("jumpForceValue").as_int();
	speed = move.attribute("speed").as_int();
	jumps = move.attribute("maxJumps").as_int();


	pugi::xml_node audio = config.child("audio");

	jumpFxPath = audio.attribute("jump").as_string();

	return ret;
}

bool Player::Start()
{
	bool ret = true;
	int pixels = 32;


	spawnLevel1.x = 600;
	spawnLevel1.y = 2816;

	position.x = spawnLevel1.x;
	position.y = spawnLevel1.y;

	spawnLevel2.x = 3427;
	spawnLevel2.y = 508;

	winWidth = app->win->GetWidth();
	winHeigh = app->win->GetHeight();


	LOG("Loading Player textures");

	texture = app->tex->Load("Assets/textures/FinnSprite.png");

	if (texture == nullptr)
		LOG("Couldn't load player texture");

	coll = { (int)position.x, (int)position.y, pixels - 4,pixels + 2 };

	//cambiar aix�
	collider = app->collisions->AddCollider(coll, Collider::Type::PLAYER, this);

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

bool Player::PreUpdate()
{
	if (app->debug->godMode == false)
	{
		position.y = (int)(position.y - vy);
		vy -= gravityForce * 0.5;
		app->player->UpdateState();
	}

	return true;
}

bool Player::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
	{
		HealHability();
	}
	if (app->debug->godMode == false)
	{

		app->player->UpdateLogic(dt);

	}
	else
	{

		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			position.x -= speed * dt;
		}
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.x += speed * dt;
		}
		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			position.y += speed * dt;
		}
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			position.y -= speed * dt;
		}

	}
	if (app->input->GetKey(SDL_SCANCODE_C) == KEY_REPEAT)
	{
		LOG("%d", position.x);
		LOG("%d", position.y);

	}
	return true;
}

bool Player::PostUpdate()
{

	SDL_Rect rect = currentAnim->GetCurrentFrame();


	if (isGoingRight == true)
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

void Player::OnCollision(Collider* a, Collider* b) {

	if (app->debug->godMode == false)
	{

		if (b == collider)
		{
			Collider* c = a;
			a = b;
			b = c;
		}

		int compY = a->rect.y - b->rect.y;
		int compX = a->rect.x - b->rect.x;
		switch (b->type)
		{
		case(Collider::Type::ENDLEVEL):

			lvl2 = true;
			app->oManager->CleanUp();
			app->map->CleanUp();
			app->player->Reload();
			app->scene->LoadLevel("level2.tmx");
			collider = app->collisions->AddCollider(coll, Collider::Type::PLAYER, this);
			return;
			break;

		case(Collider::Type::FLOOR):


			if (std::abs(compY) < std::abs(compX))
			{
				if (compX > 0) {
					position.x += b->rect.x + b->rect.w - a->rect.x;
				}
				else
				{
					position.x -= a->rect.x + a->rect.w - b->rect.x;
				}
			}
			else
			{
				if (compY > 0)
				{
					position.y += b->rect.y + b->rect.h - a->rect.y;

				}
				else
				{
					position.y -= a->rect.y + a->rect.h - b->rect.y;
					vy = 0;
					jumps = 3;
				}

			}

			collider->SetPos(position.x, position.y);


			break;

		case(Collider::Type::DEATH):

			if (lifes > 0)
			{
				//if level 1 or 2
				position.x = spawnLevel1.x;
				position.y = spawnLevel1.y;
				this->lifes--;
			}
			if (lifes <= 0)
			{
				isDead = true;
			}

			break;

		case(Collider::Type::HEART):


			lifes++;

			break;
		}
		
	}

}

void Player::UpdateState()
{

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		isGoingRight = false;
	}

	else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		isGoingRight = true;
	}

	switch (playerState)
	{
	case IDLE:
	{

		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT ||
			app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) {
			ChangeState(playerState, RUNNING);

		}

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			jumps--;
			app->audio->PlayFx(1, 0);
			ChangeState(playerState, JUMPING);

		}

		if (isDead == true)
		{
			ChangeState(playerState, DYING);


		}

		break;
	}

	case RUNNING:
	{
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				jumps--;

				if (jumps > 0)
					app->audio->PlayFx(1, 0);

				ChangeState(playerState, JUMPING);


			}

		}
		else
			ChangeState(playerState, IDLE);

		break;
	}

	case JUMPING:
	{
		//once animation is done change to falling
		// or simply add the falling sprite on jumping animations
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{


		}

		break;
	}

	case FALLING:
	{
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{

		}
		break;
	}

	case DYING:
	{
		if (isDead == false)
		{
			ChangeState(DYING, IDLE);
		}

		break;
	}

	}

}

void Player::UpdateLogic(float dt)
{
	cooldown += dt;
	
	if (cooldown > maxCooldown)
		cooldown = maxCooldown;

	switch (playerState)
	{
	case(IDLE):
	{

		break;
	}
	case(RUNNING):
	{
		if (app->checkpoints->mapOpen == 0)
		{
			if (isGoingRight == true)
			{

				position.x += speed * dt;

			}
			else
			{

				position.x -= speed * dt;

			}
		}

		break;
	}
	case(JUMPING):
	{
		if (jumps > 0)
		{
			vy = jumpForceValue;
		}
		if (jumps == 2) {
			//jump fix. Do not delete this before asking 
			position.y -= 2;
		}
		ChangeState(JUMPING, FALLING);

		break;
	}

	case(FALLING):
	{

		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.x += speed * dt;

		}
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			position.x -= speed * dt;

		}

		ChangeState(FALLING, IDLE);
	}
	case(DYING):
	{
		break;
	}

	}

	collider->SetPos(position.x, position.y);

	currentAnim->Update();
}

void Player::ChangeState(PlayerState previousState, PlayerState newState)
{

	switch (newState)
	{
	case(IDLE):
	{
		if (isGoingRight == true)
		{
			currentAnim = &idleAnimR;
		}
		else
		{
			currentAnim = &idleAnimL;
		}

		break;
	}
	case(RUNNING):
	{
		if (isGoingRight == true)
		{
			currentAnim = &runRightAnim;

		}
		else
		{
			currentAnim = &runLeftAnim;

		}


		break;
	}
	case(JUMPING):
	{
		if (isGoingRight == true)
		{
			currentAnim = &jumpRightAnim;
			isJumping = true;
		}
		else
		{
			currentAnim = &jumpLeftAnim;
			isJumping = true;
		}


		break;
	}
	case(DOUBLE_JUMPING):
	{
		if (isGoingRight == true)
		{
			currentAnim = &jumpRightAnim;
		}
		else
		{
			currentAnim = &jumpLeftAnim;
		}


		break;
	}
	case(DYING):
	{
		if (isGoingRight == true)
		{
			currentAnim = &deadAnimR;

		}
		else
		{
			currentAnim = &deadAnimL;
		}


		break;
	}
	}

	playerState = newState;
}

bool Player::Save(pugi::xml_node& savedGame)
{

	savedGame.append_attribute("x") = position.x;
	savedGame.append_attribute("y") = position.y;
	savedGame.append_attribute("jumpsRemaining") = jumps;
	savedGame.append_attribute("verticalVelocity") = vy;


	return true;
}

bool Player::Load(pugi::xml_node& savedPlayer)
{
	position.x = savedPlayer.attribute("x").as_int();
	position.y = savedPlayer.attribute("y").as_int();
	jumps = savedPlayer.attribute("jumpsRemaining").as_int();
	vy = savedPlayer.attribute("verticalVelocity").as_int();

	return true;
}

void Player::Reload()
{
	playerState = PlayerState::IDLE;
	if (lvl2 == false)
	{
		app->player->position.x = app->player->spawnLevel1.x;
		app->player->position.y = app->player->spawnLevel1.y;
	}
	else
	{
		app->player->position.x = app->player->spawnLevel2.x;
		app->player->position.y = app->player->spawnLevel2.y;
	}
	//verticalVelocity = 0.0f;
	/*if (health == 0)
	{
		health = 3;
		app->ui->score = 0;
	}*/
	//initialPosition = position;
	//respawnPosition = initialPosition;
	//gravityOn = false;
	//initialWaitCount = 0.0f;*/
}

void Player::HealHability()
{
	if (cooldown == maxCooldown)
	{
		if(app->player->lifes <= 3)app->player->lifes++;
		LOG("%d", app->player->lifes);
		cooldown = 0;
	}
	else
	{

	}
	
	LOG("%f", maxCooldown);

}




