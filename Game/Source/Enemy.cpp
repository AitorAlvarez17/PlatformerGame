#include "Enemy.h"

#define DEFAULT_PATH_LENGTH 50
#define PIXELS 32

Enemy::Enemy(fPoint origin, EnemyType type) : Entity(EntityType::ENEMY)
{
	// path = PathFinding::GetInstance()->CreatePath(iPoint(0, 0), iPoint(0, 0));
	position = origin;

	//set the width and the height to the requested value depending on the Enemy etc...

	width = 32;
	height = 32;

	//hitbox->rect.x = origin.x;
	//hitbox->rect.y = origin.y;
	//hitbox->rect.w = width;
	//hitbox->rect.h = height;

	this->eType = type;

	//SetAnim(0);
}

bool Enemy::Update(float dt)
{


	return true;
}

bool Enemy::Draw(Render* render)
{
	// animation state and animation frame
	actualAnimation->Update();
	//render->DrawRectangle(GetBounds(), { 255, 0, 0, 255 });

	SDL_Rect rec = actualAnimation->GetCurrentFrame();
	render->DrawTexturePlayer(texture, position.x, position.y, &rec, 0, 0, 0, 0);
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

	//aqui se meterán las comparaciones entre colliders. C1 siempre sera el collider del cpp en el que estas.

}

void Enemy::OnCollision(Collider* c1)
{

	//aqui se compara con otro collider, siendo c1 el collider del otro objeto.


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
	runLeftAnim.speed = 0.3f;

	runRightAnim.GenerateAnimation({ 448, 0 + (32 * i), 32, 32 }, 0, 3, 0, 0);
	runRightAnim.loop = true;
	runRightAnim.speed = 0.3f;

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

void Enemy::FixedUpdate(Input* input, float dt)
{
	//Start Idle
	UpdateAnim(eState, EnemyState::IDLE);
	switch (eType)
	{
	case EnemyType::WALKING:
	{
		if (eState == EnemyState::IDLE) {}
		if (eState == EnemyState::WALK) {}
		if (eState == EnemyState::HIT) {}
		if (eState == EnemyState::DEAD) {}
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

void Enemy::UpdateAnim(EnemyState previousState, EnemyState newState)
{
	switch (eState)
	{
	case EnemyState::IDLE:
		
		break;
	case EnemyState::WALK:
		if (goingRight) actualAnimation = &runRightAnim;
		else actualAnimation = &runLeftAnim;
		break;
	case EnemyState::HIT:
		break;
	case EnemyState::DEAD:
		break;
	default:
		break;
	}

}

void Enemy::SetTexture(SDL_Texture* tex)
{
	texture = tex;
}

void Enemy::CreatePath(Map* map, iPoint pos)
{

	iPoint o = map->MapToWorld((int)position.x, (int)position.y);
	iPoint d = map->MapToWorld((int)pos.x, (int)pos.y);

	ePath->lastPath.Clear();
	ePath->GetInstance()->CreatePath(o, d);
	newPath = ePath->GetInstance()->GetLastPath();


}

Enemy::~Enemy()
{

}

SDL_Rect Enemy::GetBounds()
{

	return { (int)position.x , (int)position.y, (int)width + PIXELS , (int)height + PIXELS };
}



