#include "Player.h"
#include "Textures.h"

#include "Log.h"

#define PIXELS 16
Player::Player(fPoint origin) : Entity(EntityType::PLAYER)
{

	position = origin;
	vy = 200.0f;

	width = 16;
	height = 16;

	/*SDL_Rect size = { origin.x, origin.y,width,height };*/

	/*hitbox = Collisions::AddCollider(size, Collider::Type::PLAYER,this);*/
	


	// Define Player animations
	idleAnimL.GenerateAnimation({ 0,96,16,16 }, 0, 3, 0, 0);
	idleAnimL.loop = true;
	idleAnimL.speed = 0.1f;

	idleAnimR.GenerateAnimation({ 160,96,16,16 }, 0, 3, 0, 0);
	idleAnimR.loop = true;
	idleAnimR.speed = 0.1f;

	runLeftAnim.GenerateAnimation({ 64,96,16,16 }, 0, 3, 0, 0);
	runLeftAnim.loop = true;
	runLeftAnim.speed = 0.3f;

	runRightAnim.GenerateAnimation({ 224,96,16,16 }, 0, 3, 0, 0);
	runRightAnim.loop = true;
	runRightAnim.speed = 0.3f;

	jumpLeftAnim.GenerateAnimation({ 0,112,16,16 }, 0, 2, 0, 0);
	jumpLeftAnim.loop = false;
	jumpLeftAnim.speed = 0.1f;

	jumpRightAnim.GenerateAnimation({ 160,112,16,16 }, 0, 2, 0, 0);
	jumpRightAnim.loop = false;
	jumpRightAnim.speed = 0.1f;

	fallRightAnim.GenerateAnimation({ 192,112,16,16 }, 0, 0, 0, 0);
	fallRightAnim.loop = false;

	fallLeftAnim.GenerateAnimation({ 32,112,16,16 }, 0, 0, 0, 0);
	fallLeftAnim.loop = false;

	damageAnimL.GenerateAnimation({ 128,96,16,16 }, 0, 1, 0, 0);
	damageAnimL.loop = true;
	damageAnimL.speed = 0.1f;

	damageAnimR.GenerateAnimation({ 288,96,16,16 }, 0, 1, 0, 0);
	damageAnimR.loop = true;
	damageAnimR.speed = 0.1f;

	deadAnimL.GenerateAnimation({ 128,112,16,16 }, 0, 0, 0, 0);
	deadAnimL.loop = false;

	deadAnimR.GenerateAnimation({ 288,112,16,16 }, 0, 0, 0, 0);
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
	render->scale = 4;

	SDL_Rect rec = actualAnimation->GetCurrentFrame();

	render->DrawTexture(texture, 0, 0, &rec);

	//if (isGoingRight == true)
	//{
	//	if (actualAnimation == &runLeftAnim) { actualAnimation = &runRightAnim; }
	//	render->DrawTexture(texture, 0, 0, &rec);
	//}
	//else
	//{
	//	if (actualAnimation == &runRightAnim) { actualAnimation = &runLeftAnim; }
	//	render->DrawTexture(texture, position.x, position.y, &rec);
	//}
	//render->DrawRectangle({ (int)position.x,(int)position.y,width,height }, { 255, 0, 0, 255 });
	//render->DrawRectangle({ 0,0,16,16 }, { 255,255,255,255 }, true);
	render->scale = 1;
	render->camera.x = -(int)position.x * 4 + render->camera.w / 2;
	render->camera.y = -(int)position.y * 4 + render->camera.h / 2;
	


	return false;
}

void Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c2 == hitbox)
	{
		Collider* c3 = c1;
		c1 = c2;
		c2 = c3;
	}

	//aqui se meterán las comparaciones entre colliders. C1 siempre sera el collider del cpp en el que estas.


}

void Player::OnCollision(Collider* c1)
{

	//aqui se compara con otro collider, siendo c1 el collider del otro objeto.


}

void Player::SetTexture(SDL_Texture* tex)
{
	texture = tex;
}

void Player::FixedUpdate(Input* input, float dt)
{
#define GRAVITY 64.0f
#define PLAYER_MOVE_SPEED 64.0f
#define PLAYER_JUMP_SPEED 90.0f



	//Start Idle
	UpdateAnim(currentAnim, IDLE);
	if (godMode < 0)
	{
		//Calculate gravity acceleration
		
		position.y += (vy * dt);
		preCalc = (vy * dt);
		vy += GRAVITY * dt;

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
	else
	{
		if (input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) position.x -= (PLAYER_MOVE_SPEED * dt);
		if (input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) position.x += (PLAYER_MOVE_SPEED * dt);
		if (input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) position.y -= (PLAYER_JUMP_SPEED * dt);
		if (input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) position.y += (PLAYER_JUMP_SPEED * dt);
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

SDL_Rect Player::GetBounds(Map* map)
{
	iPoint offset = map->GetCameraOffset();
	return { (int)position.x, (int)position.y, (int)width , (int)height  };
}


