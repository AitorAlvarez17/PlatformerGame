#include "Enemy.h"

#include "Log.h"

#define DEFAULT_PATH_LENGTH 50
#define PIXELS 32

Enemy::Enemy(fPoint origin, EnemyType type, int life, int anim) : Entity(EntityType::ENEMY)
{
	// path = PathFinding::GetInstance()->CreatePath(iPoint(0, 0), iPoint(0, 0));
	position = origin;
	lifes = life;
	//set the width and the height to the requested value depending on the Enemy etc...

	width = 32;
	height = 32;

	//Set the Animation 0, 2, 4, 6... only pair numbers
	SetAnim(anim);

	//hitbox->rect.x = origin.x;
	//hitbox->rect.y = origin.y;
	//hitbox->rect.w = width;
	//hitbox->rect.h = height;

	this->eType = type;
	ePath = ePath->GetInstance();
}

bool Enemy::Update(float dt)
{


	return true;
}

void Enemy::UpdateLogic(float dt)
{

	//Start Idle
	if (lifes == 0) eState == EnemyState::DEAD;

	switch (eType)
	{
	case EnemyType::WALKING:
	{
		if (eState == EnemyState::IDLE)
		{
			UpdateAnim(EnemyState::IDLE);
		}
		if (eState == EnemyState::WALK)
		{
			if (goingRight) position.x += 60.0f * dt;
			else position.x -= 60.0f * dt;
		}
		if (eState == EnemyState::HIT)
		{
			UpdateAnim(EnemyState::HIT);
			--lifes;
		}
		if (eState == EnemyState::DEAD)
		{
			UpdateAnim(EnemyState::DEAD);
			//DELETE ENEMY
		}
	}
	case EnemyType::FLYING:
	{
		if (eState == EnemyState::IDLE) {}
		if (eState == EnemyState::WALK) {}
		if (eState == EnemyState::HIT) {}
		if (eState == EnemyState::DEAD) {}

	}
	default:
		break;
	}



}

bool Enemy::Draw(Render* render)
{
	// animation state and animation frame
	actualAnimation->Update();


	SDL_Rect rec = actualAnimation->GetCurrentFrame();
	render->DrawTextureScaled(2, texture, position.x, position.y, &rec);
	render->DrawRectangleScaled(1,GetBounds(), { 255, 255, 255, 255 }, true);

	if (hasPath)
		ePath->DrawPath(render, newPath);



	return false;
}

void Enemy::OnCollision(Collider* c1, Collider* c2)
{
	if (c2 == hitbox)
	{
		Collider* c3 = c1;
		c1 = c2;
		c2 = c3;
	}

	//aqui se meter�n las comparaciones entre colliders. C1 siempre sera el collider del cpp en el que estas.

}

void Enemy::OnCollision(Collider* c1)
{

	//aqui se compara con otro collider, siendo c1 el collider del otro objeto.


}

void Enemy::UpdateAnim(EnemyState newState)
{
	switch (newState)
	{
	case EnemyState::IDLE:
		if (goingRight) actualAnimation = &idleAnimR;
		else actualAnimation = &idleAnimL;
		break;
	case EnemyState::WALK:
		if (goingRight) actualAnimation = &runRightAnim;
		else actualAnimation = &runLeftAnim;
		break;
	case EnemyState::HIT:
		if (goingRight) actualAnimation = &damageAnimR;
		else actualAnimation = &damageAnimL;
		break;
	case EnemyState::DEAD:
		if (goingRight) actualAnimation = &deadAnimR;
		else actualAnimation = &deadAnimL;
		break;
	default:
		break;
	}

	eState = newState;
}

void Enemy::SetAnim(int i)
{
	// Define Player animations
	idleAnimL.GenerateAnimation({ 0, 0 + (32 * i), 32, 32 }, 0, 3, 0, 0);
	idleAnimL.loop = true;
	idleAnimL.speed = 0.1f;

	idleAnimR.GenerateAnimation({ 320, 0 + (32 * i), 32, 32 }, 0, 3, 0, 0);
	idleAnimR.loop = true;
	idleAnimR.speed = 0.1f;

	runLeftAnim.GenerateAnimation({ 128, 0 + (32 * i), 32, 32 }, 0, 3, 0, 0);
	runLeftAnim.loop = true;
	runLeftAnim.speed = 0.1f;

	runRightAnim.GenerateAnimation({ 448, 0 + (32 * i), 32, 32 }, 0, 3, 0, 0);
	runRightAnim.loop = true;
	runRightAnim.speed = 0.1f;

	jumpLeftAnim.GenerateAnimation({ 0, 0 + (32 * (i + 1)), 32, 32 }, 0, 2, 0, 0);
	jumpLeftAnim.loop = true;
	jumpLeftAnim.speed = 0.1f;

	jumpRightAnim.GenerateAnimation({ 320, 0 + (32 * (i + 1)), 32, 32 }, 0, 2, 0, 0);
	jumpRightAnim.loop = true;
	jumpRightAnim.speed = 0.1f;

	fallRightAnim.GenerateAnimation({ 384,0 + (32 * (i + 1)), 32, 32 }, 0, 0, 0, 0);
	fallRightAnim.loop = false;

	fallLeftAnim.GenerateAnimation({ 64,0 + (32 * (i + 1)), 32, 32 }, 0, 0, 0, 0);
	fallLeftAnim.loop = false;

	attackAnimL.GenerateAnimation({ 128, 0 + (32 * (i + 1)), 32, 32 }, 0, 3, 0, 0);
	attackAnimL.loop = true;
	attackAnimL.speed = 0.07f;

	attackAnimR.GenerateAnimation({ 448, 0 + (32 * (i + 1)), 32, 32 }, 0, 3, 0, 0);
	attackAnimR.loop = true;
	attackAnimR.speed = 0.07f;

	damageAnimL.GenerateAnimation({ 256,0 + (32 * i),32,32 }, 0, 1, 0, 0);
	damageAnimL.loop = false;
	damageAnimL.speed = 0.1f;

	damageAnimR.GenerateAnimation({ 576, 0 + (32 * i),32,32 }, 0, 1, 0, 0);
	damageAnimR.loop = false;
	damageAnimR.speed = 0.1f;

	deadAnimL.GenerateAnimation({ 256, 0 + (32 * (i + 1)),32,32 }, 0, 0, 0, 0);
	deadAnimL.loop = false;

	deadAnimR.GenerateAnimation({ 576,0 + (32 * (i + 1)),32,32 }, 0, 0, 0, 0);
	deadAnimR.loop = false;

	actualAnimation = &attackAnimR;

}

void Enemy::SetTexture(SDL_Texture* tex)
{
	texture = tex;
}

void Enemy::UpdatePath(Map* map, Input* input, Player* player, float dt)
{
	if (hasPath)
	{
		if (eType == EnemyType::WALKING)
		{
			ePath->lastPath.Clear();

			iPoint d = { (int)player->position.x ,(int)player->position.y };
			d = map->WorldToMap(d.x, d.y);

			iPoint o = map->WorldToMap(GetBounds().x, GetBounds().y);
			ePath->CreatePath(o, d);

			newPath.Clear();
			for (int i = 0; i < ePath->lastPath.Count(); ++i)
			{
				newPath.PushBack(*ePath->lastPath.At(i));
				//LOG("%d, %d", newPath[i].x, newPath[i].x);

			}
			newPath.Flip();


			//LOGIC
			if (newPath.Count() > 9)
			{
				newPath.Clear();
				UpdateAnim(EnemyState::IDLE);
				UpdateLogic(dt);

			}
			else if (player->position.x > position.x )
			{
				goingRight = true;
				UpdateAnim(EnemyState::WALK);
				UpdateLogic(dt);
			}
			else if (player->position.x < position.x)
			{
				goingRight = false;
				UpdateAnim(EnemyState::WALK);
				UpdateLogic(dt);
			}
		}
	}

}
void Enemy::DrawPath()
{


}

Enemy::~Enemy()
{

}

SDL_Rect Enemy::GetBounds()
{

	return { (int)position.x , (int)position.y, (int)width , (int)height };
}

void Enemy::UpdateState(iPoint pos)
{
	if (this->position.y < pos.y)
		eState = EnemyState::FALL;
	if (this->position.x > pos.x)
	{
		eState = EnemyState::WALK;
		goingRight = false;
	}
	else
	{
		eState = EnemyState::WALK;
		goingRight = true;
	}
}

