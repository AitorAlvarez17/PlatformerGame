#include "Player.h"
#include "Textures.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	int pixels = 32;

    position = iPoint(5 * 16, 17 * 16);
    jumpSpeed = 200.0f;

    width = 16;
    height = 32;


	// Define Player animations
	idleAnimL.GenerateAnimation({ 0,192,32,32 }, 0, 3, 0, 0);
	idleAnimL.loop = true;
	idleAnimL.speed = 1.0f;

	idleAnimR.GenerateAnimation({ 288,192,32,32 }, 0, 3,0,0);
	idleAnimR.loop = true;
	idleAnimR.speed = 1.0f;

	runLeftAnim.GenerateAnimation({ 96,192,32,32 }, 0, 3, 0, 0);
	runLeftAnim.loop = true;
	runLeftAnim.speed = 1.0f;

	runRightAnim.GenerateAnimation({ 384,192,32,32 }, 0, 3, 0, 0);
	runRightAnim.loop = true;
	runRightAnim.speed = 1.0f;

	jumpLeftAnim.GenerateAnimation({ 0,224,32,32 }, 0, 3, 0, 0);
	jumpLeftAnim.loop = true;
	jumpLeftAnim.speed = 1.0f;

	jumpRightAnim.GenerateAnimation({ 288,224,32,32 }, 0, 3, 0, 0);
	jumpRightAnim.loop = true;
	jumpRightAnim.speed = 1.0f;

	actualAnimation = &idleAnimR;


}

bool Player::Start(Textures* tex)
{

	return true;
}

bool Player::PreUpdate(float dt, Input* input, AudioManager* audio)
{
    UpdateState(input, audio);

    return true;
}

bool Player::Update(Input* input, float dt)
{
    //#define GRAVITY 400.0f
    //#define PLAYER_MOVE_SPEED 200.0f
    //#define PLAYER_JUMP_SPEED 350.0f

   // UpdateLogic(dt, input);

    //if (input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) position.y += (PLAYER_MOVE_SPEED * dt);
    //if (input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) position.y -= (PLAYER_MOVE_SPEED * dt);
    //if (input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) position.x -= (PLAYER_MOVE_SPEED * dt);
    //if (input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) position.x += (PLAYER_MOVE_SPEED * dt);

    //if (input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) position.y -= (PLAYER_JUMP_SPEED * dt);

    // Calculate gravity acceleration
    //jumpSpeed += GRAVITY * dt;
    //position.y += (jumpSpeed * dt);

    return true;
}

bool Player::PostUpdate(float dt)
{

   

	return true;
}

bool Player::Draw(Render* render)
{
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
    SDL_Rect rec = actualAnimation->GetCurrentFrame();
    render->DrawTexture(texture, position.x, position.y, &rec);

    render->camera.x = -position.x;
    render->camera.y = -position.y - 200;

    //render->DrawRectangle(GetBounds(), { 255, 0, 0, 255 });


	//if (isGoingRight == true)
	//{
	//	if (actualAnimation == &runLeftAnim) { actualAnimation = &runRightAnim; }
	//	render->DrawTexture(texture, position.x - 12, position.y - 30, &rect, 0, 0, 0, 0, SDL_FLIP_NONE);
	//}
	//else
	//{
	//	if (actualAnimation == &runRightAnim) { actualAnimation = &runLeftAnim; }
	//	render->DrawTexture(texture, position.x - 24, position.y - 30, &rect, 0, 0, 0, 0, SDL_FLIP_NONE);
	//}

    return false;
}

void Player::SetTexture(SDL_Texture *tex, Textures* texture)
{
	tex = texture->Load(PATH("Assets/Textures/", "players.png"));
    //texture = tex;
}

SDL_Rect Player::GetBounds()
{
    return { position.x, position.y, width, height };
}

void Player::UpdateState(Input* input, AudioManager* audio)
{

	if (input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		isGoingRight = false;
	}

	else if (input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		isGoingRight = true;
	}

	switch (currentAnim)//THE ACTUAL STATE THAT WE CHANGE TO ANOTHER
	{
	case IDLE:
	{

		if (input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT ||
			input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) {
			ChangeState(currentAnim, WALK);//CHANGTE TO WALK

		}

		if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			jumps--;
			audio->PlayFx(1, 0);
			ChangeState(currentAnim, JUMP);//CHANGE TO JUMP

		}

		/*if (isDead == true)
		{
			audio->PlayFx(3, 0);
			ChangeState(currentAnim, DYING);
		}*/

		break;
	}

	case WALK:
	{
		if (input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{

			if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				jumps--;

				if (jumps > 0)
					audio->PlayFx(1, 0);

				ChangeState(currentAnim, JUMP);


			}

		}
		else
			ChangeState(currentAnim, IDLE);

		break;
	}

	case JUMP:
	{
		//once animation is done change to falling
		// or simply add the falling sprite on jumping animations
		if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{


		}

		break;
	}

	case FALLING:
	{
		if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
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
		//if (app->checkpoints->mapOpen == 0)
		//{
			if (isGoingRight == true)
			{
				position.x += speed * dt;
				//app->audio->PlayFx(5, 0);
			}
			else
			{
				position.x -= speed * dt;
				//app->audio->PlayFx(5, 0);
			}
		//}*/

		break;
	}
	case(JUMP):
	{
		if (jumps > 0)
		{
			vy = jumpForceValue * dt;
		}
		if (jumps == 2) {
			//jump fix. Do not delete this before asking 
			position.y -= 2;
		}
		ChangeState(currentAnim, FALLING);

		break;
	}

	case(FALLING):
	{

		if (input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.x += speed * dt;

		}
		if (input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			position.x -= speed * dt;

		}

		ChangeState(FALLING, IDLE);
	}

	}

	actualAnimation->Update();
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

