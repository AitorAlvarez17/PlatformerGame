#include "Player.h"
#include "Textures.h"

#include "Log.h"

#define PIXELS 32
Player::Player(iPoint origin, AudioManager* manager) : Entity(EntityType::PLAYER)
{
	aud = manager;
	delayUi = 2.0f;
	position = origin;
	vy = 200.0f;

	width = 64;
	height = 64;

	lifes = 3;
	godMode = -1;

	coins = 0;


	// Define Player animations
	idleAnimL.GenerateAnimation({ 0,192,32,32 }, 0, 3, 0, 0);
	idleAnimL.loop = true;
	idleAnimL.speed = 0.1f;

	idleAnimR.GenerateAnimation({ 320,192,32,32 }, 0, 3, 0, 0);
	idleAnimR.loop = true;
	idleAnimR.speed = 0.1f;

	runLeftAnim.GenerateAnimation({ 128,192,32,32 }, 0, 3, 0, 0);
	runLeftAnim.loop = true;
	runLeftAnim.speed = 0.3f;

	runRightAnim.GenerateAnimation({ 448,192,32,32 }, 0, 3, 0, 0);
	runRightAnim.loop = true;
	runRightAnim.speed = 0.3f;

	jumpLeftAnim.GenerateAnimation({ 0,224,32,32 }, 0, 2, 0, 0);
	jumpLeftAnim.loop = false;
	jumpLeftAnim.speed = 0.1f;

	jumpRightAnim.GenerateAnimation({ 320,224,32,32 }, 0, 2, 0, 0);
	jumpRightAnim.loop = false;
	jumpRightAnim.speed = 0.1f;

	fallRightAnim.GenerateAnimation({ 384,224,32,32 }, 0, 0, 0, 0);
	fallRightAnim.loop = false;

	fallLeftAnim.GenerateAnimation({ 64,224,32,32 }, 0, 0, 0, 0);
	fallLeftAnim.loop = false;

	damageAnimL.GenerateAnimation({ 256,192,32,32 }, 0, 1, 0, 0);
	damageAnimL.loop = true;
	damageAnimL.speed = 0.1f;

	damageAnimR.GenerateAnimation({ 576,192,32,32 }, 0, 1, 0, 0);
	damageAnimR.loop = true;
	damageAnimR.speed = 0.1f;

	deadAnimL.GenerateAnimation({ 256,224,32,32 }, 0, 0, 0, 0);
	deadAnimL.loop = false;

	deadAnimR.GenerateAnimation({ 576,224,32,32 }, 0, 0, 0, 0);
	deadAnimR.loop = false;

	actualAnimation = &jumpLeftAnim;

	int tpCounter = 1;
}


bool Player::Update(Input* input, float dt)
{
	prevPos = position;
	FixedUpdate(input, dt);

	cooldown += dt;
	delayUi += dt;
	fireCooldown += dt;


	if (lifes == 0)
	{
		isDead = true;
		aud->PlayFx(2, 0);
	}

	if (hitted)
		hitCooldown += dt;

	if (hitCooldown >= 1.0f)
	{
		hitted = false;
		hitCooldown = 0;
	}

	if (cooldown > 3.0f)
		cooldown = 3.0f;

	if (fireCooldown > 2.0f)
		fireCooldown = 2.0f;

	if (delayUi > 1.0f)
		delayUi = 1.0f;


	return true;
}

void Player::Draw(Render* render)
{
	// animation state and animation frame
	actualAnimation->Update();

	SDL_Rect rec = actualAnimation->GetCurrentFrame();


	if (isGoingRight == true)
	{
		if (actualAnimation == &runLeftAnim) { actualAnimation = &runRightAnim; }
		render->DrawTextureScaled(2, texture, (int)position.x, (int)position.y, &rec);
	}
	else
	{
		if (actualAnimation == &runRightAnim) { actualAnimation = &runLeftAnim; }
		render->DrawTextureScaled(2, texture, (int)position.x, (int)position.y, &rec);
	}



	if (position.x > 3761)
	{
	}
	else if (position.x < 320)
	{
	}
	else if (position.y > 2256)
	{
	}
	else
	{
		render->camera.x = -(int)position.x + render->camera.w / 4;
		render->camera.y = -(int)position.y + render->camera.h / 2 + 64;
	}

}

void Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c2 == hitbox)
	{
		Collider* c3 = c1;
		c1 = c2;
		c2 = c3;
	}

	//aqui se meter�n las comparaciones entre colliders. C1 siempre sera el collider del cpp en el que estas.

}

void Player::OnCollision(Collider* c1)
{
	//aqui se compara con otro collider, siendo c1 el collider del otro objeto.
	if (godMode == -1)
	{
		if (c1->type == Collider::Type::HEART)
		{
			aud->PlayFx(5, 0);
			lifes++;
		}
		if (c1->type == Collider::Type::COIN)
		{
			aud->PlayFx(7, 0);
			coins++;

		}
		if (c1->type == Collider::Type::ENEMY)
		{

			if (hitted == false)
				lifes--;

			hitted = true;

		}
		if (c1->type == Collider::Type::DEATH)
		{
			lifes = 0;
			isDead = true;

		}
		if (c1->type == Collider::TP)
		{
			onColl = true;
		}
	}

}

void Player::HealAbility()
{
	if (lifes < maxLifes)
	{
		lifes++;
		cooldown = 0;
	}
	else
	{
		delayUi = 0;
	}
}

void Player::FireballAbility()
{
	fireCooldown = 0;
}

void Player::SetTexture(SDL_Texture* tex)
{
	texture = tex;
}

void Player::FixedUpdate(Input* input, float dt)
{
#define GRAVITY 18
#define PLAYER_MOVE_SPEED 256
#define PLAYER_JUMP_SPEED 550

	//Start Idle
	UpdateAnim(currentAnim, IDLE);
	if (godMode < 0)
	{
		//Calculate gravity acceleration
		position.y += (vy * dt);

		if (floor == false) vy = vy + GRAVITY;
		if (vy > 200) vy = 200;

		//Get left / right input
		if (input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
		{
			position.x -= PLAYER_MOVE_SPEED * dt;
			isGoingRight = false;
			UpdateAnim(currentAnim, WALK);

		}
		if (input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
		{
			position.x += PLAYER_MOVE_SPEED * dt;
			isGoingRight = true;
			UpdateAnim(currentAnim, WALK);

		}
		if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			if (jumps > 0)
			{
				jumps--;
				vy = vy - (PLAYER_JUMP_SPEED);
				floor = false;
				UpdateAnim(currentAnim, JUMP);
				aud->PlayFx(6, 0);

			}

		}

	}
	else
	{
		if (input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) position.x -= (PLAYER_MOVE_SPEED * dt);
		if (input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) position.x += (PLAYER_MOVE_SPEED * dt);
		if (input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) position.y -= (PLAYER_JUMP_SPEED * dt);
		if (input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) position.y += (PLAYER_JUMP_SPEED * dt);
	}

	hitbox->rect = { position.x,position.y,width,height };

}

void Player::UpdateAnim(PlayerAnim previousState, PlayerAnim newState)
{
	switch (newState)
	{
	case(IDLE):
	{
		if (isGoingRight == true)
		{
			actualAnimation = &idleAnimR;
		}
		else
		{
			actualAnimation = &idleAnimL;
		}

		break;
	}
	case(WALK):
	{
		if (isGoingRight == true)
		{
			actualAnimation = &runRightAnim;

		}
		else
		{
			actualAnimation = &runLeftAnim;

		}

		break;
	}
	case(JUMP):
	{
		if (isGoingRight == true)
		{
			actualAnimation = &jumpRightAnim;
		}
		else
		{
			actualAnimation = &jumpLeftAnim;
		}

		break;
	}
	case(FALLING):
	{
		if (isGoingRight == true)
		{
			actualAnimation = &fallRightAnim;
		}
		else
		{
			actualAnimation = &fallLeftAnim;
		}

	}

	}

	currentAnim = newState;

}

SDL_Rect Player::GetBounds()
{
	return { (int)position.x, (int)position.y, (int)width , (int)height };
}

SDL_Rect Player::GetBoundsScaled()
{
	return { (int)position.x , (int)position.y , (int)width , (int)height };
}


