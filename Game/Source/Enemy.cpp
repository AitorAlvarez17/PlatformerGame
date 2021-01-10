#include "Enemy.h"

#include "Log.h"

#define DEFAULT_PATH_LENGTH 50
#define PIXELS 32

Enemy::Enemy(iPoint origin, EnemyType type, int life, int anim, Map* eMap, Player* ePlayer, AudioManager* manager) : Entity(EntityType::ENEMY)
{
	player = ePlayer;
	map = eMap;
	aud = manager;
	position = origin;
	lifes = life;
	spawnPos.y = origin.y;
	this->eType = type;
	//set the width and the height to the requested value depending on the Enemy etc...

	width = 64;
	height = 64;


	//Set the Animation 0, 2, 4, 6... only pair numbers
	SetAnim(anim);


	ePath = ePath->GetInstance();
}

bool Enemy::Update(float dt)
{
	if (lifes == 0)
	{
		actualAnimation = &deadAnimL;
		pendingToDelete = true;
		aud->PlayFx(2, 0);
	}

	//Path Limits
	if (eType == EnemyType::WALKING)
	{
		if (player->position.y > 2240)
		{
			return true;
		}
		if (spawnPos.y > 1344 && player->position.y < 1344)
		{
			pendingToDelete = true;
			return true;
		}
		if (spawnPos.y > 1344 && player->position.x > 3000)
		{
			position = spawnPos;
		}
		else { UpdatePath(map, player, dt); }
	}

	if (eType == EnemyType::FLYING)
	{
		if (player->position.y > 2240)
		{
			return true;
		}
		if (spawnPos.y > 1344 && player->position.y < 1344)
		{
			pendingToDelete = true;
			return true;
		}
		if (spawnPos.y > 1344 && player->position.x > 3000)
		{
			position.x -= 1 * dt;
		}
		else { UpdatePath(map, player, dt); }
	}


	hitbox->rect = { position.x,position.y,width,height };

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
		break;
	}
	case EnemyType::FLYING:
	{
		if (eState == EnemyState::IDLE)
		{
			UpdateAnim(EnemyState::IDLE);
		}
		if (eState == EnemyState::WALK)
		{
			
		}
		if (eState == EnemyState::HIT) {}
		if (eState == EnemyState::DEAD) {}
		break;
	}
	default:
		break;
	}


}

void Enemy::Draw(Render* render)
{
	// animation state and animation frame
	actualAnimation->Update();

	SDL_Rect rec = actualAnimation->GetCurrentFrame();

	if (eType == EnemyType::WALKING) render->DrawTextureScaled(2, texture, position.x, position.y, &rec);
	if (eType == EnemyType::FLYING) render->DrawTextureScaled(2, texture, position.x, position.y, &rec);


	if (hasPath > 0)
		ePath->DrawPath(render, newPath);

}

void Enemy::OnCollision(Collider* c1, Collider* c2)
{
	if (c2 == hitbox)
	{
		Collider* c3 = c1;
		c1 = c2;
		c2 = c3;
	}

	//aqui se meterán las comparaciones entre colliders. C1 siempre sera el collider del cpp en el que estas.

}

void Enemy::OnCollision(Collider* c1)
{
	if (c1->type == Collider::Type::FIREBALL)
	{
		lifes--;
	}
	//aqui se compara con otro collider, siendo c1 el collider del otro objeto.


}

void Enemy::UpdateAnim(EnemyState newState)
{
	if (eType == EnemyType::WALKING)
	{
		switch (newState)
		{
		case EnemyState::IDLE:
		{
			if (goingRight) actualAnimation = &idleAnimR;
			else actualAnimation = &idleAnimL;
			break;
		}
		case EnemyState::WALK:
		{
			if (goingRight) actualAnimation = &runRightAnim;
			else actualAnimation = &runLeftAnim;
			break;
		}
		case EnemyState::HIT:
		{
			if (goingRight) actualAnimation = &damageAnimR;
			else actualAnimation = &damageAnimL;
			break;
		}
		case EnemyState::DEAD:
		{
			if (goingRight) actualAnimation = &deadAnimR;
			else actualAnimation = &deadAnimL;
			break;
		}
		default:
			break;
		}
	}
	if (eType == EnemyType::FLYING)
	{
		switch (newState)
		{
		case EnemyState::IDLE:
		{
			actualAnimation = &idleAnimL;
			break;
		}
		case EnemyState::WALK:
		{
			if (goingRight) actualAnimation = &runRightAnim;
			else actualAnimation = &runLeftAnim;
			break;
		}
		case EnemyState::JUMP:
			break;
		case EnemyState::FALL:
			break;
		case EnemyState::HIT:
			break;
		case EnemyState::DEAD:
			break;
		default:
			break;
		}

	}
	eState = newState;
}

void Enemy::SetAnim(int i)
{
	switch (eType)
	{
	case EnemyType::WALKING:
	{
		// Define Enemy animations
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

		actualAnimation = &idleAnimL;
		break;
	}
	case EnemyType::FLYING:
	{
		idleAnimL.GenerateAnimation({ 32, 0, 32, 32 }, 0, 2, 0, 0);
		idleAnimL.loop = true;
		idleAnimL.speed = 0.05f;

		runLeftAnim.GenerateAnimation({ 32, 96 , 32, 32 }, 0, 2, 0, 0);
		runLeftAnim.loop = true;
		runLeftAnim.speed = 0.1f;

		runRightAnim.GenerateAnimation({ 32, 32, 32, 32 }, 0, 2, 0, 0);
		runRightAnim.loop = true;
		runRightAnim.speed = 0.1f;

		actualAnimation = &idleAnimL;

		break;
	}

	case EnemyType::UKNOWN:
		break;
	default:
		break;
	}


}

void Enemy::SetTexture(SDL_Texture* tex)
{
	texture = tex;
}

bool Enemy::UpdatePath(Map* map, Player* player, float dt)
{

	ePath->lastPath.Clear();

	iPoint d = { (int)player->position.x ,(int)player->position.y };
	d = map->WorldToMap(d.x, d.y);

	iPoint o = map->WorldToMap(GetBounds().x, GetBounds().y - 64);
	ePath->CreatePath(o, d);

	newPath.Clear();
	for (int i = 0; i < ePath->lastPath.Count(); ++i)
	{
		newPath.PushBack(*ePath->lastPath.At(i));

	}
	newPath.Flip();

	switch (eType)
	{
	case EnemyType::WALKING:
	{
		//LOGIC
		if (newPath.Count() >= 9)
		{
			newPath.Clear();
			ePath->lastPath.Clear();
			UpdateAnim(EnemyState::IDLE);
			return true;

		}
		else if (player->position.x > position.x)
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
		break;
	}
	case EnemyType::FLYING:
	{
		//LOGIC
		int c = newPath.Count() - 1;
		if (c > 14)
		{
			newPath.Clear();
			ePath->lastPath.Clear();
			UpdateAnim(EnemyState::IDLE);
			return true;
		}
		if (c < 14)
		{
			iPoint pos;
			iPoint nextPos;
			for (int i = 1; i < c; i++)
			{
				pos.x = newPath[i].x;
				pos.y = newPath[i].y;
				nextPos.x = newPath[i + 1].x;
				nextPos.y = newPath[i + 1].y;

				if (pos.x < nextPos.x)
				{
					position.x -= 1 * dt;
				}
				else if (pos.x > nextPos.x)
				{
					position.x += 60 * dt;
				}
				else if (pos.y < nextPos.y)
				{
					position.y -= 60 * dt;
				}
				else if (pos.y > nextPos.y)
				{
					position.y += 60 * dt;
				}
			}

		}
		break;
	}

	case EnemyType::UKNOWN:
		break;
	default:
		break;
	}
	return true;

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

