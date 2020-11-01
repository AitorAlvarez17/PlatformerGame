#include "Player.h"
#include "Debug.h"
#include "App.h"
#include "Input.h"
#include "Animation.h"
#include "Textures.h"
#include "Window.h"
#include "Render.h"
#include "Collisions.h"
#include "SDL/include/SDL_scancode.h"
#include "Audio.h"
#include "../Defs.h"
#include "../Log.h"
#include <math.h>


Player::Player(bool startEnabled) : Module(startEnabled)
{

}

bool Player::Start()
{
	bool ret = true;
	int pixels = 32;

	
	position.x = 600;
	position.y = 2816;


	winWidth = app->win->GetWidth();
	winHeigh = app->win->GetHeight();
	

	LOG("Loading Player textures");

	texture = app->tex->Load("Assets/textures/FinnSprite.png");
	
	
	//texture = app->tex->Load("Assets/textures/Main Characters/Virtual Guy/Idle (32x32).png");
	/*texture = app->tex->Load("Assets/textures/Main Characters/Virtual Guy/SpriteSheet.png");*/

	if (texture == nullptr)
		LOG("Couldn't load player texture");
	coll = { position.x, position.y, pixels-4,pixels+2 };

	//cambiar això
	collider = app->collisions->AddCollider(coll, Collider::Type::PLAYER, this);

	idleAnimR.loop = idleAnimL.loop = runRightAnim.loop = runLeftAnim.loop = true;
	idleAnimR.speed = idleAnimL.speed = 0.2f;
	runRightAnim.speed = runLeftAnim.speed = 0.3f;

	//
	if (push == false)
	{
		for (int i = 0; i < 27; i++)// 0 to 9
		{
			if (i >= 0 && i < 9)//FIRST ANIM IDLE
			{
				idleAnimR.PushBack({ i * pixels,0,32,32 });
				/*if (i == 8)
				{
					break;
				}*/
			}
			if (i >= 0 && i < 9)//FIRST ANIM IDLE
			{
				idleAnimL.PushBack({ (27 - i) * pixels,32,32,32 });
				/*if (i == 8)
				{
					break;
				}*/
			}
			if (i >= 9 && i < 15)// RUN
			{
				runRightAnim.PushBack({ i * pixels,0,32,32 });
				/*if (i == 14)
				{
					break;
				}*/
			}
			if (i >= 9 && i < 15)// RUN
			{
				runLeftAnim.PushBack({ (27 - i) * pixels,32,32,32 });
				/*if (i == 14)
				{
					break;
				}*/
			}
			if (i == 15) // JUMP R 
			{
				jumpRightAnim.PushBack({ i * pixels,0,32,32 });
				jumpLeftAnim.PushBack({ (27 - i) * pixels,32,32,32 });
				/*if (i == 15)
				{
					break;
				}*/
			}
			if (i >= 20 && i < 23) // DEAD RIGHT
			{
				deadAnimR.PushBack({ i * pixels,0,32,32 });
				/*if (i == 22)
				{
					break;
				}*/
			}
			if (i >= 20 && i < 23) // DEAD RIGHT
			{
				deadAnimL.PushBack({ (27 - i) * pixels,32,32,32 });
				/*if (i == 22)
				{
					break;
				}*/
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
		position.y -= vy;
		vy -= gravityForce * 0.5;
	}
	
	

	return true;
}

bool Player::Update(float dt)
{
	if (app->debug->godMode == false)
	{
		app->player->UpdateState();
		app->player->UpdateLogic();

	}
	else
	{
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT )
		{
			position.x -= speed;
		}
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			position.y -= speed;
		}
		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			position.y += speed;
		}
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.x += speed;
		}
	}

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	if (lvl1 == true)
	{
		app->render->camera.x = (-position.x + (winWidth / 4)) * 2;
		app->render->camera.y = -(position.y * 1.95);
		if (app->render->camera.x >= -704)
		{
			app->render->camera.x = -704;
		}
		if (app->render->camera.x < -6018)
		{
			app->render->camera.x = -6018;
		}
		if (app->render->camera.y < -5400)
		{
			app->render->camera.y = -5400;
		}
		
	}
	

	//LOG("x: %d y: %d", app->render->camera.x, app->render->camera.y);

	return true;
}

bool Player::PostUpdate()
{
	SDL_Rect rect = currentAnim->GetCurrentFrame();


	if (isGoingRight = true)
	{
		app->render->DrawTexturePlayer(texture, position.x - 12, position.y - 30, &rect);
	}
	else
	{
		app->render->DrawTexturePlayer(texture, position.x - 100 ,position.y - 30, &rect);
		
	
	}
	
	

	return true;
}



void Player::OnCollision(Collider* a, Collider* b) {

	if (app->debug->godMode == false)
	{
		if (a->type == Collider::PLAYER && b->type == Collider::FLOOR)
		{
			int compY = a->rect.y - b->rect.y;
			int compX = a->rect.x - b->rect.x;


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
					position.y -= a->rect.y + a->rect.h - b->rect.y ;
					vy = 0;
				}
			}

			collider->SetPos(position.x, position.y);
			jumps = 1;

		}
		if (a->type == Collider::PLAYER && b->type == Collider::DEATH)
		{
			isDead = true;
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
		{
			ChangeState(playerState, RUNNING);
			LOG("RUNNIG");
		}
			

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			if (jumps > 0) {
				
				app->audio->PlayFx(1, 0);
				ChangeState(playerState, JUMPING);
				LOG("JUMPING");
				jumps--;
			}

		}
		


		if (isDead == true) 
		{
			ChangeState(playerState, DYING);
			LOG("DYING");
		}

		break;
	}

	case RUNNING:
	{
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{

			
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) 
			{
				if (jumps > 0) 
				{
						
					app->audio->PlayFx(1, 0);
					ChangeState(playerState, JUMPING);
					LOG("JUMPING");
					jumps--;
				}
			}

			
			


		}
		else
			ChangeState(playerState, IDLE);

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
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
			if (jumps == 2)
				ChangeState(FALLING, JUMPING);
			else if (jumps == 1)
				ChangeState(FALLING, DOUBLE_JUMPING);
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

void Player::UpdateLogic()
{

	switch (playerState)
	{
		case(IDLE):
		{
		

			break;
		}
		case(RUNNING):
		{

			if (isGoingRight == true)
			{
	
				position.x += speed;
			
			}
			else
			{
			
				position.x -= speed;
	
			}



			break;
	}
	case(JUMPING):
	{
		if (jumps > 0)
		{
			vy = jumpForceValue;
		}
		
		
		



		/*if (isGoingRight == true)
			currentAnim = &jumpRightAnim;
		else
			currentAnim = &jumpLeftAnim;*/

		ChangeState(JUMPING, FALLING);

		break;
	}

	case(FALLING):
	{

		/*if (isGoingRight == true)
			currentAnim = &fallRightAnim;
		else
			currentAnim = &fallLeftAnim;*/

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
		if(isGoingRight == true)
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
			LOG("CHANGE to RUN");
		}
		else
		{
			currentAnim = &runLeftAnim;
		}




		/*if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			isGoingRight = false;
		else
			isGoingRight = true;
		currentAnim= &(canMoveRight == false ? runLeftAnim : runRightAnim);*/
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

		/*if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			isGoingRight = false;
		else
			isGoingRight = true;
		currentAnim = &(canMoveRight == false ? jumpLeftAnim : jumpRightAnim);*/
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
		/*if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)

			isGoingRight = false;
		else
			isGoingRight = true;
		currentAnim = &(canMoveRight == false ? jumpLeftAnim : jumpRightAnim);*/

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

