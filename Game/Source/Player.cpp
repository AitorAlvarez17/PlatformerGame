#include "Player.h"

#include "App.h"
#include "Input.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"
#include "Collisions.h"
#include "SDL/include/SDL_scancode.h"

#include "../Defs.h"
#include "../Log.h"
#include <math.h>

bool Player::Start()
{
	bool ret = true;
	int pixels = 32;
	position.x = 0;
	position.y = 0;

	LOG("Loading Player textures");

	texture = app->tex->Load("Assets\textures\FinnSprite");
	
	//texture = app->tex->Load("Assets/textures/Main Characters/Virtual Guy/Idle (32x32).png");
	/*texture = app->tex->Load("Assets/textures/Main Characters/Virtual Guy/SpriteSheet.png");*/

	if (texture == nullptr)
		LOG("Couldn't load player texture");

	currentAnim;
	//cambiar això
	//collider = app->collisions->AddCollider(SDL_Rect({ position.x, position.y, 22, 26 }), Collider::Type::DYNAMIC, this);

	idleAnimR.loop = idleAnimL.loop = runRightAnim.loop = runLeftAnim.loop = true;
	idleAnimR.speed = idleAnimL.speed = 0.6f;
	runRightAnim.speed = runLeftAnim.speed = 0.7f;

	//right
	for (int i = 0; i < 27; i ++)// 0 to 9
	{
		if (0 <= i < 9)//FIRST ANIM IDLE
		{
			idleAnimR.PushBack({ i*32,0,32,32 });
		}
		if (27 > i >= 18)// FIRST ANIM IDLE
		{
			idleAnimL.PushBack({ i * 32, 32,32,32 });
		}
		if(9 <= i < 15)// RUN
		{
			runRightAnim.PushBack({ i*32,0,32,32 });
		}
		if (13 > i >= 18)// RUN LEFT
		{
			runLeftAnim.PushBack({ i*32, 32,32,32 });
		}
		if (i == 15 ) // JUMP R 
		{
			jumpRightAnim.PushBack({ i*32,0,32,32 });
		}
		if (i == 12) // JUMP L
		{
			jumpLeftAnim.PushBack({ i*32,32,32,32 });
		}
		if (20 <= i < 23) // DEAD RIGHT
		{
			deadAnim.PushBack({ i*32,0,32,32 });
		}
		if (7 > i >= 5) //DEAD LEFT
		{
			deadAnim.PushBack({ i*32,32,32,32 });
		}
	}
	//left
	

	//appearAnim.loop = disappearLeftAnim.loop = disappearRightAnim.loop = false;


	
	return ret;
}

bool Player::Update(float dt)
{
	app->player->UpdateState();
	app->player->UpdateLogic();

	return true;
}

bool Player::PostUpdate()
{
	SDL_Rect rect = {0,0,100,55};

	app->render->DrawTexture(texture, position.x, position.y, &rect);

	return true;
}

void Player::OnCollision(Collider* a, Collider* b) {

	int diffPosX = a->rect.x + a->rect.w - b->rect.x;
	int diffNegX = a->rect.x - (b->rect.x + b->rect.w);
	int diffPosY = b->rect.y + b->rect.h - a->rect.y;
	int diffNegY = b->rect.y - (a->rect.y + a->rect.h);

	if (std::min(std::abs(diffPosX), std::abs(diffNegX)) < std::min(std::abs(diffPosY), std::abs(diffNegY)))
	{
		if (std::abs(diffPosX) < std::abs(diffNegX))
		{
			position.x -= diffPosX;
		}
		else
		{
			position.x -= diffNegX;
		}
	}
	else
	{
		if (std::abs(diffPosY) < std::abs(diffNegY))
		{
			position.y -= diffPosY;
		}
		else
		{
			position.y -= diffNegY;
		}
	}
}


void Player::UpdateState()
{
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
		isGoingRight = false;
	else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
		isGoingRight = true;

	switch (playerState)
	{
	case IDLE:
	{


		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT ||
			app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			ChangeState(playerState, RUNNING);

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			ChangeState(playerState, JUMPING);

		}

		if (isDead == true) ChangeState(playerState, DYING);

		break;
	}

	case RUNNING:
	{
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)

		{


		}
		else
			ChangeState(playerState, IDLE);

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			ChangeState(playerState, JUMPING);
		}



		break;
	}

	case JUMPING:
	{
		//once animation is done change to falling
		// or simply add the falling sprite on jumping animations
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			ChangeState(playerState, DOUBLE_JUMPING);

		}



		break;
	}

	case DOUBLE_JUMPING:
	{




		break;
	}

	case FALLING:
	{
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			if (jumpsLeft == 2)
				ChangeState(FALLING, JUMPING);
			else if (jumpsLeft == 1)
				ChangeState(FALLING, DOUBLE_JUMPING);
		}



		break;
	}
	case DYING:
	{


		break;
	}

	}

}

void Player::UpdateLogic()
{
	//change to collider
	if (position.y < 130)
	{
		position.y += gravityForce;
		//jumpForce = 0;

	}
	position.y -= jumpForce;
}
	/*switch (playerState)
	{
	case(IDLE):
	{
		if (isGoingRight == true)
			currentAnim = &idleRightAnim;
		else
			currentAnim = &idleLeftAnim;

		break;
	}
	case(RUNNING):
	{
		if (isGoingRight == true)
		{
			currentAnim = &runRightAnim;
			position.x += speed;
		}

		else
		{
			currentAnim = &runLeftAnim;
			position.x -= speed;
		}



		break;
	}
	case(JUMPING):
	{

		jumpForce = jumpForceValue;
		jumpsLeft--;

		if (isGoingRight == true)
			currentAnim = &jumpRightAnim;
		else
			currentAnim = &jumpLeftAnim;

		ChangeState(JUMPING, FALLING);

		break;
	}

	case(FALLING):
	{
		jumpForce = 0;

		if (isGoingRight == true)
			currentAnim = &fallRightAnim;
		else
			currentAnim = &fallLeftAnim;

		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.x += speed;

		}
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			position.x -= speed;

		}



		ChangeState(FALLING, IDLE);
	}

	case(DOUBLE_JUMPING):
	{
		jumpForce = jumpForceValue;

		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.x += speed;

		}
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			position.x -= speed;

		}


		break;
	}
	case(DYING):
	{
		if (isGoingRight == true)
			currentAnim = &disappearRightAnim;
		else
			currentAnim = &disappearLeftAnim;

		break;

	}

	}

	collider->SetPos(position.x, position.y);

	//currentAnim->Update();
}
*/
void Player::ChangeState(PlayerState previousState, PlayerState newState)
{

	switch (newState)
	{
	case(IDLE):
	{
		//currentAnimation = &(goingRight == false ? idleLeftAnim : idleRightAnim);
		break;
	}
	case(RUNNING):
	{

		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT
			)
			isGoingRight = false;
		else
			isGoingRight = true;
		//currentAnimation = &(goingRight == false ? leftAnim : rightAnim);
		break;
	}
	case(JUMPING):
	{
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			isGoingRight = false;
		else
			isGoingRight = true;
		//currentAnimation = &climbAnim;
		break;
	}
	case(DOUBLE_JUMPING):
	{
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)

			isGoingRight = false;
		else
			isGoingRight = true;

		break;
	}
	case(DYING):
	{
		break;
	}
	}

	playerState = newState;
}

