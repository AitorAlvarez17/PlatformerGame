#include "Player.h"
#include "Textures.h"

#include "Log.h"

#define PIXELS 32
Player::Player(fPoint origin) : Entity(EntityType::PLAYER)
{

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

}

bool Player::Update(Input* input, float dt)
{
	prevPos = position;
	FixedUpdate(input, dt);

	// if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) position.x -= (PLAYER_MOVE_SPEED * dt);
	// if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) position.x += (PLAYER_MOVE_SPEED * dt);
	//if (input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) position.y -= (PLAYER_JUMP_SPEED * dt);

	return true;
}

bool Player::Draw(Render* render)
{

	// animation state and animation frame
	actualAnimation->Update();
	render->DrawRectangle(GetBounds(), { 255, 0, 0, 255 });

	SDL_Rect rec = actualAnimation->GetCurrentFrame();
	if (isGoingRight == true)
	{
		if (actualAnimation == &runLeftAnim) { actualAnimation = &runRightAnim; }
		render->DrawTexturePlayer(texture, position.x, position.y, &rec, 0, 0, 0, 0);
	}
	else
	{
		if (actualAnimation == &runRightAnim) { actualAnimation = &runLeftAnim; }
		render->DrawTexturePlayer(texture, position.x, position.y, &rec, 0, 0, 0, 0);
	}

	render->camera.x = -(int)position.x * 4 + render->camera.w / 2;
	render->camera.y = -(int)position.y * 4 + render->camera.h / 2;

	return false;
}

void Player::SetTexture(SDL_Texture* tex)
{
	texture = tex;
}

void Player::FixedUpdate(Input* input, float dt)
{
#define GRAVITY 128.0f
#define PLAYER_MOVE_SPEED 64.0f
#define PLAYER_JUMP_SPEED 90.0f

	//Calculate gravity acceleration
	position.y += (vy * dt);
	vy += GRAVITY * dt;

	//Start Idle
	UpdateAnim(currentAnim, IDLE);

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
	if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT || input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		position.y += -PLAYER_JUMP_SPEED * dt;
		UpdateAnim(currentAnim, JUMP);

	}



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

	return { (int)position.x , (int)position.y, (int)width + PIXELS , (int)height + PIXELS };
}


