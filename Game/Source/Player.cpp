#include "Player.h"
#include "Textures.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	int pixels = 32;

	position = iPoint(5 * 16, 17 * 16);
	vy = 200.0f;

	width = 16;
	height = 32;

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

	jumpLeftAnim.GenerateAnimation({ 0,224,32,32 }, 0, 3, 0, 0);
	jumpLeftAnim.loop = false;
	jumpLeftAnim.speed = 0.1f;

	jumpRightAnim.GenerateAnimation({ 320,224,32,32 }, 0, 3, 0, 0);
	jumpRightAnim.loop = false;
	jumpRightAnim.speed = 0.1f;

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

	actualAnimation = &damageAnimR;

}

bool Player::Update(Input* input, float dt)
{
#define GRAVITY 200.0f
#define PLAYER_MOVE_SPEED 100.0f
#define PLAYER_JUMP_SPEED 450.0f

	vy += GRAVITY * dt;
	position.y += (vy * dt);
	UpdateState(input);
	UpdateLogic(dt, input);


	// if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) position.x -= (PLAYER_MOVE_SPEED * dt);
	// if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) position.x += (PLAYER_MOVE_SPEED * dt);
	//if (input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) position.y -= (PLAYER_JUMP_SPEED * dt);

	 //Calculate gravity acceleration
	



	return true;
}

bool Player::Draw(Render* render)
{
	// TODO: Calculate the corresponding rectangle depending on the
	// animation state and animation frame
	actualAnimation->Update();

	SDL_Rect rec = actualAnimation->GetCurrentFrame();
	if (isGoingRight == true)
	{
		if (actualAnimation == &runLeftAnim) { actualAnimation = &runRightAnim; }
		render->DrawTexture(texture, position.x - 12, position.y - 30, &rec, 0, 0, 0, 0, SDL_FLIP_NONE);
	}
	else
	{
		if (actualAnimation == &runRightAnim) { actualAnimation = &runLeftAnim; }
		render->DrawTexture(texture, position.x - 24, position.y - 30, &rec, 0, 0, 0, 0, SDL_FLIP_NONE);
	}

	render->camera.x = -position.x;
	render->camera.y = -position.y - 200;

	//render->DrawRectangle(GetBounds(), { 255, 0, 0, 255 });
	return false;
}

void Player::SetTexture(SDL_Texture* tex)
{
	texture = tex;
}

SDL_Rect Player::GetBounds()
{
	return { position.x, position.y, width, height };
}

void Player::UpdateState(Input* input)
{

	if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		isGoingRight = true;
	}

	else if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		isGoingRight = false;
	}

	switch (currentAnim)//THE ACTUAL STATE THAT WE CHANGE TO ANOTHER
	{
	case IDLE:
	{

		if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT ||
			input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
			ChangeState(currentAnim, WALK);//CHANGTE TO WALK

		}

		if (input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			jumps--;
			ChangeState(currentAnim, JUMP);//CHANGE TO JUMP

		}

		//if (isDead == true)
		//{
		//	ChangeState(currentAnim, DYING);
		//}

		break;
	}

	case WALK:
	{
		if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
			{
				jumps--;
				ChangeState(currentAnim, JUMP);
			}
			ChangeState(currentAnim, WALK);
		}
		else
			ChangeState(currentAnim, IDLE);

		break;
	}

	case JUMP:
	{
		//once animation is done change to falling
		// or simply add the falling sprite on jumping animations
		if (input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{

		}
		break;
	}

	case FALLING:
	{
		if (input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{

		}
		break;
	}

	}

}

void Player::UpdateLogic(float dt, Input* input)
{
	/*cooldown += dt;
	fireCooldown += dt;

	if (cooldown > maxCooldown)
		cooldown = maxCooldown;
	if (fireCooldown > fireMaxCooldown)
		fireCooldown = fireMaxCooldown;*/

	switch (currentAnim)
	{
	case(IDLE):
	{
		break;
	}
	case(WALK):
	{
		if (isGoingRight == true)
		{
			position.x += (PLAYER_MOVE_SPEED * dt);
			
		}
		else
		{
			position.x -= (PLAYER_MOVE_SPEED * dt);

		}

		break;
	}
	case(JUMP):
	{
	
	
		position.y -= (PLAYER_JUMP_SPEED * dt);
			
		if (isGoingRight == true)
		{
			position.x += (PLAYER_MOVE_SPEED * dt);

		}
		else
		{
			position.x -= (PLAYER_MOVE_SPEED * dt);

		}
		
			//jump fix. Do not delete this before asking 
			//position.y -= (PLAYER_JUMP_SPEED * dt);

		ChangeState(currentAnim, FALLING);

		break;
	}

	case(FALLING):
	{

		if (input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.x += (PLAYER_MOVE_SPEED * dt);

		}
		if (input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			position.x -= (PLAYER_MOVE_SPEED * dt);

		}

		ChangeState(currentAnim, IDLE);
	}

	}

}

void Player::ChangeState(PlayerAnim previousState, PlayerAnim newState)
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
			isJumping = true;
		}
		else
		{
			actualAnimation = &jumpLeftAnim;
			isJumping = true;
		}

		break;
	}

	}

	currentAnim = newState;

}

/*void Player::HealHability()
{
	if (cooldown == maxCooldown)
	{
		if (lifes < 5)
		{
			app->player->lifes++;
			app->audio->PlayFx(6, 0);
			maxLifes = false;
		}
		else
		{
			app->ui->cantSumon = 0;
			maxLifes = true;
		}
		LOG("%d", app->player->lifes);
		cooldown = 0;
	}
	else
	{

	}

	LOG("%f", maxCooldown);

}*/

