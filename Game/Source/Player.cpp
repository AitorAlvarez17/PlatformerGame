#include "Player.h"
#include "Textures.h"

Player::Player(fPoint origin) : Entity(EntityType::PLAYER)
{
	int pixels = 32;

	position = origin;
	vy = 200.0f;

	width = 32;
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

	//Calculate gravity acceleration
	vy += GRAVITY * dt;
	position.y += (vy * dt);

	UpdateState(input);
	UpdateLogic(dt, input);

	// if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) position.x -= (PLAYER_MOVE_SPEED * dt);
	// if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) position.x += (PLAYER_MOVE_SPEED * dt);
	//if (input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) position.y -= (PLAYER_JUMP_SPEED * dt);

	return true;
}

bool Player::Draw(Render* render)
{
	int pixels = 32;
	// animation state and animation frame
	actualAnimation->Update();
	render->DrawRectangle(GetBounds(), { 255, 0, 0, 255 });

	SDL_Rect rec = actualAnimation->GetCurrentFrame();
	if (isGoingRight == true)
	{
		if (actualAnimation == &runLeftAnim) { actualAnimation = &runRightAnim; }
		render->DrawTexture(texture, position.x, position.y, &rec, 0, 0, 0, 0, SDL_FLIP_NONE);
	}
	else
	{
		if (actualAnimation == &runRightAnim) { actualAnimation = &runLeftAnim; }
		render->DrawTexture(texture, position.x, position.y, &rec, 0, 0, 0, 0, SDL_FLIP_NONE);
	}

	render->camera.x = -position.x;
	render->camera.y = -position.y - 200;

	return false;
}

void Player::SetTexture(SDL_Texture* tex)
{
	texture = tex;
}

SDL_Rect Player::GetBounds()
{
	int pixels = 32;
	return {(int)position.x, (int)position.y, (int)width, (int)height };
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

