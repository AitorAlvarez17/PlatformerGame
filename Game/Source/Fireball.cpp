#include "Fireball.h"

Fireball::Fireball(iPoint origin, bool isRight) : Entity(EntityType::FIREBALL)
{
	position = origin;

	isGoingRight = isRight;

}

bool Fireball::Update(float dt, Input* input)
{
#define ATTACK_MAX_COOLDOWN 3
#define ABILITY_MAX_COOLDOWN 5

	//Oncrease Cooldown
	attackCool += dt;
	abilityCool += dt;

	if (attackCool > ABILITY_MAX_COOLDOWN)
		attackCool = ABILITY_MAX_COOLDOWN;
	if (attackCool > ATTACK_MAX_COOLDOWN)
		attackCool = ATTACK_MAX_COOLDOWN;

	//Check Input
	if (input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
	{
		Ability();
	}
	if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		Attack();
	}

	return true;
}

void Fireball::Ability()
{
	if (abilityCool == ABILITY_MAX_COOLDOWN)
	{
		//if (/*wandPlayer.lifes == 5*/)
		//{
		//	//wandPlayer.maxLifes = false;
		//}
		//else
		//{
		//	//ui->cantSumon = 0;
		//	maxLifes = true;
		//}
		abilityCool = 0;
	}
	else
	{


	}
}

void Fireball::Attack()
{
	if (attackCool == ATTACK_MAX_COOLDOWN)
	{
		////CREATE FIREBALL
		//if (wandPlayer->isGoingRight)
		//{
		//	//app->oManager->AddObject(ObjType::FIREBALL, position.x, position.y, 1);
		//}
		//else
		//{
		//	//app->audio->PlayFx(4, 0);
		//	//app->oManager->AddObject(ObjType::FIREBALL, position.x, position.y, -1);

		//}
		//attackCool = 0;
	}
	else
	{

	}


}

